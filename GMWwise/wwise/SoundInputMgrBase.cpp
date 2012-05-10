//////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006 Audiokinetic Inc. / All Rights Reserved
//
//////////////////////////////////////////////////////////////////////
#include "SoundInputMgrBase.h"
#include "SoundInputMgr.h"
#include <AK/Plugin/AkAudioInputSourceFactory.h>

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
// SoundInputMgrBase implementation
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

bool SoundInputMgrBase::Initialize()
{
	// Reset members.
	Reset();
	// Set Wwise required Callbacks
#ifndef AK_3DS
	SetAudioInputCallbacks( ExecuteCallback, GetFormatCallback );
#endif

	// Cannot fail for now, return true.
    return true;
}

void SoundInputMgrBase::Term()
{
}

void SoundInputMgrBase::GetFormatCallback(
        AkPlayingID		in_playingID,   // Playing ID
        AkAudioFormat&  io_AudioFormat  // Already filled format, modify it if required.
	    )
{
	SoundInputBase* pInput = SoundInputMgr::Instance().GetInput( in_playingID ) ;
	if( pInput )
	{
		pInput->GetFormatCallback( io_AudioFormat );
	}
}

void SoundInputMgrBase::ExecuteCallback(
        AkPlayingID		in_playingID,  // Playing ID
        AkAudioBuffer*	io_pBufferOut  // Buffer to fill
	    )
{
    io_pBufferOut->uValidFrames = 0;

    SoundInputBase* pInput = SoundInputMgr::Instance().GetInput( in_playingID ) ;
    if( pInput == NULL )
    {
        io_pBufferOut->eState = AK_Fail;
		return;
    }

    // Execute will fill io_pBufferOut->uValidFrames with the correct value.
    pInput->Execute( io_pBufferOut );

    if( io_pBufferOut->uValidFrames > 0 )
        io_pBufferOut->eState = AK_DataReady;
    else
        io_pBufferOut->eState = AK_NoDataReady;
}

SoundInputBase* SoundInputMgrBase::GetInput( AkPlayingID in_playingID )
{
	for( int i = 0; i < MAX_NUM_SOUNDINPUT; ++i )
	{
		if( m_registeredDevices[i].pInput 
			&& m_registeredDevices[i].pInput->GetPlayingID() == in_playingID 
			)
		{
			return m_registeredDevices[i].pInput;
		}
	}
#ifdef AK_WIN
	// Default to find one, any...
	// A real game should not adopt this behavior, this should only be done for playback in Wwise.
	for( int i = 0; i < MAX_NUM_SOUNDINPUT; ++i )
	{
		if( m_registeredDevices[i].pInput )
		{
			return m_registeredDevices[i].pInput;
		}
	}
#endif //WIN32
	return NULL;
}

void SoundInputMgrBase::Reset()
{
	memset( m_registeredDevices, 0, MAX_NUM_SOUNDINPUT * sizeof(RegisteredDevice) );
}

bool SoundInputMgrBase::RegisterDevice( SoundInputBase* in_pSoundInput )
{
	for( int i = 0; i < MAX_NUM_SOUNDINPUT; ++i )
	{
		if( m_registeredDevices[i].pInput == NULL )
		{
			m_registeredDevices[i].pInput = in_pSoundInput;
			return true;
		}
	}

	//printf("Cannot register more than MAX_NUM_SOUNDINPUT microphone devices simultaneously\n");
	return false;
}

void SoundInputMgrBase::UnregisterDevice( SoundInputBase* in_pSoundInput )
{
	for( int i = 0; i < MAX_NUM_SOUNDINPUT; ++i )
	{
		if( m_registeredDevices[i].pInput == in_pSoundInput )
		{
			m_registeredDevices[i].pInput = NULL;
			break;
		}
	}
}
