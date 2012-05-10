//////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006 Audiokinetic Inc. / All Rights Reserved
//
//////////////////////////////////////////////////////////////////////
#include <AK/Plugin/AkAudioInputSourceFactory.h>
#include <math.h>

#include "SoundInput.h"
#include "SoundInputMgr.h"

// The sample rate
#define AUDIO_INPUT_SAMPLE_RATE 48000

#define BUFFER_STATUS_NOT_READY 0
#define BUFFER_STATUS_READY 1

// Writes data from output into given buffer
void CALLBACK AudioCallback(HWAVEIN hwi, UINT uMsg, DWORD_PTR dwInstance, DWORD_PTR dwParam1, DWORD_PTR dwParam2);

//---------------------------------------------------------------------------
SoundInput::SoundInput()
	: m_CurrentInputBufferIndex(0)
	, m_RemainingSize(0)
	, m_bStopRefillThread(false)
	, m_bSuccessfullyInitOnceAndMustSleepOnExit( false )
{
	AKPLATFORM::AkClearEvent( m_eventRefill );
	AKPLATFORM::AkClearThread(&m_RefillThread);
	m_WaveHeader[0].lpData	= NULL;
	m_WaveInHandle			= NULL;
}

//---------------------------------------------------------------------------
SoundInput::~SoundInput() 
{
    InputOff();

	// Avoid deadlock in waveIn
	if( m_bSuccessfullyInitOnceAndMustSleepOnExit )
		Sleep( 100 );
}

//---------------------------------------------------------------------------
bool SoundInput::InputOn( unsigned int in_DevNumber )
{
	//Reset some members.
	m_WaveInHandle			= NULL;

	(void)in_DevNumber;// Remove warning while not supporting multiple microphones.

	// In this sample we use MIXERLINE_COMPONENTTYPE_SRC_MICROPHONE to read
	// audio data from the microphone and feed it to the Audio Input plug-in.
	// Other MIXERLINE_COMPONENTTYPE_SRC_* component types exist for other
	// types of input -- See MIXERLINE documentation in MSDN for more information.
	if (SetInputDevice(MIXERLINE_COMPONENTTYPE_SRC_MICROPHONE) == FALSE)
	{
		return false;
	}

	MMRESULT err;	               

	// Clear out both of our WAVEHDRs. At the very least, waveInPrepareHeader() expects the dwFlags field to be cleared
	ZeroMemory(&m_WaveHeader, sizeof(m_WaveHeader));

	// Initialize the WAVEFORMATEX for 16-bit, 48KHz, mono. That's what we want to record 
	m_WaveFormat.wFormatTag      = WAVE_FORMAT_PCM;
	m_WaveFormat.nChannels       = 1;
	m_WaveFormat.nSamplesPerSec  = AUDIO_INPUT_SAMPLE_RATE;
	m_WaveFormat.wBitsPerSample  = 16;
	m_WaveFormat.nBlockAlign     = m_WaveFormat.nChannels * (m_WaveFormat.wBitsPerSample/8);
	m_WaveFormat.nAvgBytesPerSec = m_WaveFormat.nSamplesPerSec * m_WaveFormat.nBlockAlign;
	m_WaveFormat.cbSize          = 0;

	// Open the default WAVE In Device, specifying my callback. Note that if this device doesn't
	// support 16-bit, 48KHz, mono recording, then Windows will attempt to open another device
	// that does. So don't make any assumptions about the name of the device that opens. After
	// waveInOpen returns the handle, use waveInGetID to fetch its ID, and then waveInGetDevCaps
	// to retrieve the actual name	                         
	if ((err = waveInOpen(&m_WaveInHandle, 
						   WAVE_MAPPER, 
						   &m_WaveFormat, 
						   (DWORD_PTR)AudioCallback, 
						   (DWORD_PTR)this, 
						   CALLBACK_FUNCTION)) != 0)
	{
		goto err_cond;
	}

	// Initialize the remaining size.
    m_RemainingSize = GetFullBufferSize();

	// Allocate, prepare, and queue two buffers that the driver can use to record blocks of audio data.
	// (ie, We're using double-buffering. You can use more buffers if you'd like, and you should do that
	// if you suspect that you may lag the driver when you're writing a buffer to disk and are too slow
	// to requeue it with waveInAddBuffer. With more buffers, you can take your time requeueing
	// each).
	//
	// Just to make it easy, I'll use 1 call to VirtualAlloc to allocate both buffers, but you can
	// use 2 separate calls since the buffers do NOT need to be contiguous. You should do the latter if
	// using many, large buffers
	m_WaveHeader[0].dwBufferLength = GetFullBufferSize();
	if( m_WaveHeader[0].lpData == NULL )
	{
		m_WaveHeader[0].lpData = (char*)VirtualAlloc(0, m_WaveHeader[0].dwBufferLength * AUDIO_INPUT_NUM_BUFFERS, MEM_COMMIT, PAGE_READWRITE);
		if (!m_WaveHeader[0].lpData)
		{
			goto err_cond;
		}
	}

	// Prepare the WAVEHDR's 
	for ( int i = 0; i < AUDIO_INPUT_NUM_BUFFERS; ++i )
	{
		if ( i > 0 )
		{
			m_WaveHeader[i].dwBufferLength = GetFullBufferSize();
			m_WaveHeader[i].lpData = m_WaveHeader[i-1].lpData + GetFullBufferSize();
		}
		m_WaveHeader[i].dwUser = BUFFER_STATUS_NOT_READY;

		err = waveInPrepareHeader(m_WaveInHandle, &m_WaveHeader[i], sizeof(WAVEHDR));
		if (err)
			goto err_cond;

		err = waveInAddBuffer(m_WaveInHandle, &m_WaveHeader[i], sizeof(WAVEHDR));
		if (err)
			goto err_cond;
	}

	if ( m_WaveHeader[0].lpData )
	{
		// clear write buffer and set read pointer half-way into buffer (to allow for read
		// pointer to catch up)
		memset(m_WaveHeader[0].lpData, 0, GetFullBufferSize() * AUDIO_INPUT_NUM_BUFFERS);
	}

	if( StartRefillThread() != AK_Success )
	{
		goto err_cond;
	}

	// start getting input
	if ((waveInStart(m_WaveInHandle)))
	{
		goto err_cond;
	}

	if( !SoundInputMgr::Instance().RegisterDevice( this ) )
	{
		goto err_cond;
	}

	m_bSuccessfullyInitOnceAndMustSleepOnExit = true;
    return true;

err_cond:
	InputOff();
	return false;
}

//---------------------------------------------------------------------------
bool SoundInput::InputOff()
{
	StopRefillThread();
	SoundInputMgr::Instance().UnregisterDevice( this );

	// stop getting input
	waveInStop(m_WaveInHandle);
	waveInClose(m_WaveInHandle);
	m_WaveInHandle = NULL;

	m_CurrentInputBufferIndex = 0;
	m_RemainingSize = 0;

	// Free the recording buffers
	if( m_WaveHeader[0].lpData )
	{
 		VirtualFree (m_WaveHeader[0].lpData, (m_WaveHeader[0].dwBufferLength << 1), MEM_RELEASE); 
		m_WaveHeader[0].lpData = NULL;
	}

	return true;
}

//---------------------------------------------------------------------------
BOOL SoundInput::SetInputDevice (unsigned int inDev)
{
	HMIXER hMixer   = NULL;
	int    inDevIdx = -1;

	if (mixerOpen(&hMixer, 0, 0, NULL, MIXER_OBJECTF_MIXER) != MMSYSERR_NOERROR)
	{
		return FALSE;
	}

	// get dwLineID
	MIXERLINE mxl;
	mxl.cbStruct        = sizeof(MIXERLINE);
	mxl.dwComponentType = MIXERLINE_COMPONENTTYPE_DST_WAVEIN;

	if (mixerGetLineInfo((HMIXEROBJ)hMixer, &mxl, MIXER_OBJECTF_HMIXER | MIXER_GETLINEINFOF_COMPONENTTYPE) != MMSYSERR_NOERROR)
	{
		mixerClose (hMixer);
		return TRUE; // In vista, mixerGetLineInfo doesn't work but the rest still might.
	}

	// get dwControlID
	MIXERCONTROL      mxc;
	MIXERLINECONTROLS mxlc;
	DWORD             dwControlType = MIXERCONTROL_CONTROLTYPE_MIXER;

	mxlc.cbStruct      = sizeof(MIXERLINECONTROLS);
	mxlc.dwLineID      = mxl.dwLineID;
	mxlc.dwControlType = dwControlType;
	mxlc.cControls     = 0;
	mxlc.cbmxctrl      = sizeof(MIXERCONTROL);
	mxlc.pamxctrl      = &mxc;

	if (mixerGetLineControls((HMIXEROBJ)hMixer, &mxlc, MIXER_OBJECTF_HMIXER | MIXER_GETLINECONTROLSF_ONEBYTYPE) != MMSYSERR_NOERROR)
	{
		// no mixer, try MUX
		dwControlType      = MIXERCONTROL_CONTROLTYPE_MUX;
		mxlc.cbStruct      = sizeof(MIXERLINECONTROLS);
		mxlc.dwLineID      = mxl.dwLineID;
		mxlc.dwControlType = dwControlType;
		mxlc.cControls     = 0;
		mxlc.cbmxctrl      = sizeof(MIXERCONTROL);
		mxlc.pamxctrl      = &mxc;
		if (mixerGetLineControls((HMIXEROBJ)hMixer, &mxlc, MIXER_OBJECTF_HMIXER | MIXER_GETLINECONTROLSF_ONEBYTYPE) != MMSYSERR_NOERROR)
		{
			mixerClose (hMixer);
			return FALSE;
		}
	}

	if (mxc.cMultipleItems <= 0)
	{
		mixerClose (hMixer);
		return FALSE;
	}

	// get the index of the inDevice from available controls
	MIXERCONTROLDETAILS_LISTTEXT*  pmxcdSelectText = new MIXERCONTROLDETAILS_LISTTEXT[mxc.cMultipleItems];

	if (pmxcdSelectText != NULL)
	{
		MIXERCONTROLDETAILS mxcd;

		mxcd.cbStruct       = sizeof(MIXERCONTROLDETAILS);
		mxcd.dwControlID    = mxc.dwControlID;
		mxcd.cChannels      = 1;
		mxcd.cMultipleItems = mxc.cMultipleItems;
		mxcd.cbDetails      = sizeof(MIXERCONTROLDETAILS_LISTTEXT);
		mxcd.paDetails      = pmxcdSelectText;

		if (mixerGetControlDetails ((HMIXEROBJ)hMixer, &mxcd, MIXER_OBJECTF_HMIXER | MIXER_GETCONTROLDETAILSF_LISTTEXT) == MMSYSERR_NOERROR)
		{
			// determine which controls the inputDevice source line
			DWORD dwi;
			for (dwi = 0; dwi < mxc.cMultipleItems; dwi++)
			{
				// get the line information
				MIXERLINE mxl;
				mxl.cbStruct = sizeof(MIXERLINE);
				mxl.dwLineID = pmxcdSelectText[dwi].dwParam1;
				if (mixerGetLineInfo ((HMIXEROBJ)hMixer, &mxl, MIXER_OBJECTF_HMIXER | MIXER_GETLINEINFOF_LINEID) == MMSYSERR_NOERROR && mxl.dwComponentType == inDev)
				{
					// found, dwi is the index.
					inDevIdx = dwi;
					// break;
				}
			}
		}

		delete []pmxcdSelectText;
	}

	if (inDevIdx < 0)
	{
		mixerClose (hMixer);
		return FALSE;
	}

	// get all the values first
	MIXERCONTROLDETAILS_BOOLEAN* pmxcdSelectValue = new MIXERCONTROLDETAILS_BOOLEAN[mxc.cMultipleItems];

	if (pmxcdSelectValue != NULL)
	{
		MIXERCONTROLDETAILS mxcd;
		mxcd.cbStruct       = sizeof(MIXERCONTROLDETAILS);
		mxcd.dwControlID    = mxc.dwControlID;
		mxcd.cChannels      = 1;
		mxcd.cMultipleItems = mxc.cMultipleItems;
		mxcd.cbDetails      = sizeof(MIXERCONTROLDETAILS_BOOLEAN);
		mxcd.paDetails      = pmxcdSelectValue;
		if (mixerGetControlDetails((HMIXEROBJ)hMixer, &mxcd, MIXER_OBJECTF_HMIXER | MIXER_GETCONTROLDETAILSF_VALUE) == MMSYSERR_NOERROR)
		{
			// ASSERT(m_dwControlType == MIXERCONTROL_CONTROLTYPE_MIXER || m_dwControlType == MIXERCONTROL_CONTROLTYPE_MUX);

			// MUX restricts the line selection to one source line at a time.
			if (dwControlType == MIXERCONTROL_CONTROLTYPE_MUX)
			{
				ZeroMemory(pmxcdSelectValue, mxc.cMultipleItems * sizeof(MIXERCONTROLDETAILS_BOOLEAN));
			}

			// Turn on this input device
			pmxcdSelectValue[inDevIdx].fValue = 0x1;

			mxcd.cbStruct       = sizeof(MIXERCONTROLDETAILS);
			mxcd.dwControlID    = mxc.dwControlID;
			mxcd.cChannels      = 1;
			mxcd.cMultipleItems = mxc.cMultipleItems;
			mxcd.cbDetails      = sizeof(MIXERCONTROLDETAILS_BOOLEAN);
			mxcd.paDetails      = pmxcdSelectValue;
			if (mixerSetControlDetails ((HMIXEROBJ)hMixer, &mxcd, MIXER_OBJECTF_HMIXER | MIXER_SETCONTROLDETAILSF_VALUE) != MMSYSERR_NOERROR)
			{
				delete []pmxcdSelectValue;
				mixerClose (hMixer);
				return FALSE;
			}
		}

		delete []pmxcdSelectValue;
	}

	mixerClose (hMixer);
	return TRUE;
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

void CALLBACK AudioCallback(HWAVEIN /*hwi*/, UINT uMsg, DWORD_PTR, DWORD_PTR dwParam1, DWORD_PTR /*dwParam2*/)
{				
	switch( uMsg )
	{
	case WIM_DATA:
		{
			WAVEHDR *hdr = (WAVEHDR*)dwParam1;
			hdr->dwUser = BUFFER_STATUS_READY;
		}
		break;

	case WIM_CLOSE:
		// Notification meaning that the WaveInput was closed.
		// Could be 
		// - A disconnected device
		// - An error in the driver 
		// - Normal closing.
		//
		// No use for this at the moment.
		// If you add something here, make sure you don’t call anything on the system directly from the callback.
		break;

	default:
		break;
	}
}

void SoundInput::GetFormatCallback(
        AkAudioFormat&  io_AudioFormat  // Already filled format, modify it if required.
	    )
{
    io_AudioFormat.SetAll(
            48000,// Sample rate
            AK_SPEAKER_SETUP_MONO,
            16,						// Bits per samples
            2,						// 2 bytes per samples
            AK_INT,					// feeding integers(signed)
            AK_INTERLEAVED
            );
}

void SoundInput::SendBufferRequest( DWORD in_bufferIndex )
{
	m_WaveHeader[in_bufferIndex].dwUser = BUFFER_STATUS_NOT_READY;
	m_WaveHeader[in_bufferIndex].dwBufferLength = GetFullBufferSize();

	// Option 1: Send the request right away.
	/*
	ExecuteBufferRequest( in_bufferIndex );
	*/

	// Option 2: Send the request to be executed by another thread, allowing the blocking function to not be called in this thread.
	m_refillLock.Lock();
	m_refillQueue.push( in_bufferIndex );
	m_refillLock.Unlock();
	AKPLATFORM::AkSignalEvent( m_eventRefill );
}

void SoundInput::ExecuteBufferRequest( DWORD in_bufferIndex )
{
	MMRESULT result = waveInPrepareHeader(m_WaveInHandle, &(m_WaveHeader[in_bufferIndex]), sizeof(WAVEHDR));
	if( MMSYSERR_NOERROR == result )
	{
		result = waveInAddBuffer(m_WaveInHandle, &(m_WaveHeader[in_bufferIndex]), sizeof(WAVEHDR));
	}
}

//---------------------------------------------------------------------------
AkUInt16 SoundInput::GetFullBufferSize()
{
    return AUDIO_INPUT_BUFFER_SIZE * sizeof(short);
}

void SoundInput::MoveCurrentIndex()
{
	SendBufferRequest(m_CurrentInputBufferIndex);
    ++m_CurrentInputBufferIndex;
    m_CurrentInputBufferIndex = m_CurrentInputBufferIndex % AUDIO_INPUT_NUM_BUFFERS;
    m_RemainingSize = GetFullBufferSize();
}

void SoundInput::Execute(
        AkAudioBuffer*	io_pBufferOut  // Buffer to fill
	    )
{
    if( m_WaveHeader[0].lpData == NULL )
    {
        io_pBufferOut->eState = AK_Fail;
        io_pBufferOut->uValidFrames = 0;

		return;
    }

	AkUInt32 uMaxFrames = io_pBufferOut->MaxFrames();

    AkInt8 * AK_RESTRICT pBufOut = (AkInt8*)( io_pBufferOut->GetChannel(0) );

    /////////////////////////////////////////
	DWORD previousBufferIndex = (m_CurrentInputBufferIndex+AUDIO_INPUT_NUM_BUFFERS-1)%AUDIO_INPUT_NUM_BUFFERS;
	#pragma warning( push )
	#pragma warning( disable : 4127 )
	if ( AUDIO_INPUT_NUM_BUFFERS > 2 && m_WaveHeader[previousBufferIndex].dwUser == BUFFER_STATUS_READY )
    #pragma warning( pop )
	{
		// The microphone recording stopped because we did not play in time.
		// It will glitch randomly because we will be on the edge of being late.
		// Reset synchronisation by skipping some buffers.


		for(DWORD i = 0; i < NUM_TARGET_FREE_BUFFERS; ++i )
		{
			MoveCurrentIndex();
		}
    }
    /////////////////////////////////////////

    while( io_pBufferOut->uValidFrames != uMaxFrames )
    {
		WAVEHDR& rCurrentWavHdr = m_WaveHeader[m_CurrentInputBufferIndex];
		if ( rCurrentWavHdr.dwUser == BUFFER_STATUS_READY )
        {
            AkUInt16 l_transferSize = min( 
                m_RemainingSize, 
                (AkUInt16)( (uMaxFrames-io_pBufferOut->uValidFrames) * sizeof( AkInt16 ) )
                );

            memcpy(pBufOut, 
				rCurrentWavHdr.lpData + (GetFullBufferSize() - m_RemainingSize), 
                l_transferSize );

            pBufOut += l_transferSize;

            m_RemainingSize -= l_transferSize;
            io_pBufferOut->uValidFrames += (l_transferSize / sizeof( AkInt16 ));

            if( m_RemainingSize == 0 )
            {
                MoveCurrentIndex();
            }	
        }
        else
        {
           break;
        }
    }
}

AK_DECLARE_THREAD_ROUTINE( SoundInput::RefillThreadFunc )
{
	SoundInput& rThis = *reinterpret_cast<SoundInput*>(AK_THREAD_ROUTINE_PARAMETER);
	#pragma warning( push )
	#pragma warning( disable : 4127 )
	while(true)
	#pragma warning( pop )
	{
		AKPLATFORM::AkWaitForEvent( rThis.m_eventRefill );

		if ( rThis.m_bStopRefillThread )
			break;
		
		rThis.m_refillLock.Lock();
		while( !rThis.m_refillQueue.empty() )
		{
			DWORD index = rThis.m_refillQueue.front();
			rThis.m_refillQueue.pop();
			rThis.m_refillLock.Unlock();
			rThis.ExecuteBufferRequest( index );
			rThis.m_refillLock.Lock();
		}
		rThis.m_refillLock.Unlock();
	}

	AkExitThread(AK_RETURN_THREAD_OK);
}

//====================================================================================================
//====================================================================================================
AKRESULT SoundInput::StartRefillThread()
{
	if(AKPLATFORM::AkIsValidThread(&m_RefillThread))
	{
		return AK_Fail;
	}

	m_bStopRefillThread = false;

	if ( AKPLATFORM::AkCreateEvent( m_eventRefill ) != AK_Success )
	{
		return AK_Fail;
	}

	AkThreadProperties threadProps;
	AKPLATFORM::AkGetDefaultThreadProperties( threadProps );
	threadProps.nPriority = AK_THREAD_PRIORITY_ABOVE_NORMAL;

	AKPLATFORM::AkCreateThread(	RefillThreadFunc,	// Start address
					this,		 // Parameter
					threadProps, // Thread properties 
					&m_RefillThread,
					"AK::SoundInput" );	// Name
	if ( !AKPLATFORM::AkIsValidThread(&m_RefillThread) )
	{
		return AK_Fail;
	}
	return AK_Success;
}
//====================================================================================================
//====================================================================================================
void SoundInput::StopRefillThread()
{
	m_bStopRefillThread = true;
	if ( AKPLATFORM::AkIsValidThread( &m_RefillThread ) )
	{
		// stop the eventMgr thread
		AKPLATFORM::AkSignalEvent( m_eventRefill );
		AKPLATFORM::AkWaitForSingleThread( &m_RefillThread );

		AKPLATFORM::AkCloseThread( &m_RefillThread );
	}
	AKPLATFORM::AkDestroyEvent( m_eventRefill );
}