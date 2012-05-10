/*
Author : cédric liaudet
URL    : http://code.google.com/p/gmwwise/

=================================================================================
This library is free software; you can redistribute it and/or modify 
it under the terms of the GNU Lesser General Public License as published
by the Free Software Foundation; either version 2.1 of the License, or (at your option) any later version. 
This library is distributed in the hope that it will be useful, but without any warranty; 
without even the implied warranty of merchantability or fitness for a particular purpose. 
See the GNU Lesser General Public License for more details.
=================================================================================
*/
#include "GMWEngine.h"
#include "GMWBank.h"
#include "wwise/SoundInputMgr.h"
#include "wwise/AkFilePackageLowLevelIOBlocking.h"

namespace AK
{
    void * __cdecl AllocHook( size_t in_size )
    {
        return malloc( in_size );
    }
    void __cdecl FreeHook( void * in_ptr )
    {
        free( in_ptr );
    }
    void * __cdecl VirtualAllocHook(
        void * in_pMemAddress,
        size_t in_size,
        DWORD in_dwAllocationType,
        DWORD in_dwProtect
        )
    {
        return VirtualAlloc( in_pMemAddress, in_size, in_dwAllocationType, in_dwProtect );
    }
    void __cdecl VirtualFreeHook( 
        void * in_pMemAddress,
        size_t in_size,
        DWORD in_dwFreeType
        )
    {
        VirtualFree( in_pMemAddress, in_size, in_dwFreeType );
    }
}

CAkFilePackageLowLevelIOBlocking g_lowLevelIO;

#ifndef AK_OPTIMIZED
    AkMemPoolId g_poolComm = AK_INVALID_POOL_ID;    
#   define COMM_POOL_SIZE          (256 * 1024)
#   define COMM_POOL_BLOCK_SIZE    (48)
#endif

extern "C"
{ 
	//----------------------------------------------------------------
    // Initialization of Wwise. --------------------------------------
	double GMWInit(void)
    {
		AkMemSettings memSettings;
		memSettings.uMaxNumPools = 20;

		AKRESULT result = AK::MemoryMgr::Init(&memSettings);
        if(result != AK_Success)
		{
			GMW_EXCEPTION("unable to initialize the memory manager of wwise.");

            return EC_MEMORY;
		}

        AkStreamMgrSettings stmSettings;
        AK::StreamMgr::GetDefaultSettings(stmSettings);
        if(!AK::StreamMgr::Create( stmSettings ) )
        {
            GMW_EXCEPTION("Could not create the Streaming Manager");

            return EC_STREAM_MGR;
        }

        AkDeviceSettings deviceSettings;
        AK::StreamMgr::GetDefaultDeviceSettings( deviceSettings );
        if(g_lowLevelIO.Init(deviceSettings) != AK_Success)
		{
			GMW_EXCEPTION("Could not create the streaming device and Low-Level I/O system.");

            return EC_IO;
		}

        AkInitSettings initSettings;
        AkPlatformInitSettings platformInitSettings;
        AK::SoundEngine::GetDefaultInitSettings( initSettings );
        AK::SoundEngine::GetDefaultPlatformInitSettings( platformInitSettings );
        if(AK::SoundEngine::Init(&initSettings, &platformInitSettings) != AK_Success)
        {
            GMW_EXCEPTION("Could not initialize the Sound Engine.");

            return EC_SOUND_ENGINE;
        }

        AkMusicSettings musicInit;
        AK::MusicEngine::GetDefaultInitSettings( musicInit );
        if(AK::MusicEngine::Init(&musicInit) != AK_Success)
        {
            GMW_EXCEPTION("Could not initialize the Music Engine.");

            return EC_MUSIC_ENGINE;
        }

#ifndef AK_OPTIMIZED
        // Initialize communication.
        AkCommSettings settingsComm;
        AK::Comm::GetDefaultInitSettings( settingsComm );
        if ( AK::Comm::Init( settingsComm ) != AK_Success )
        {
            AKASSERT( !"Cannot initialize music communication" );
            return EC_COM;
        }
#endif
		SoundInputMgr::Instance().Initialize();

        return EC_NONE;
    }

	//----------------------------------------------------------------
	// FShutdown Wwise and free all resources. -----------------------
    double GMWShutdown(void)
    {
		SoundInputMgr::Instance().Term();

#ifndef AK_OPTIMIZED
        AK::Comm::Term();	   
#endif // AK_OPTIMIZED		
		GMWClearBanks();		

		AK::SoundEngine::UnregisterAllGameObj();

		AK::MusicEngine::Term();

		AK::SoundEngine::Term();
		
		if(AK::IAkStreamMgr::Get())
		{   
			AK::IAkStreamMgr::Get()->Destroy();
		}

		AK::MemoryMgr::Term();

		return EC_NONE;
    }

	//----------------------------------------------------------------
	// Update the sound engine. --------------------------------------
    double GMWProcessAudio(void)
    {
        AK::SoundEngine::RenderAudio();

		return EC_NONE;
    }

	//----------------------------------------------------------------
	//  Set state of the specified group. ----------------------------
	double GMWSetState(double _dStateGroup, double _dState)
	{
		if(_dStateGroup < 0)
		{
			GMW_EXCEPTION("Bad state group ID : ID must be higher or equal to 0");

			return EC_BAD_ARGS;
		}

		if(_dState < 0)
		{
			GMW_EXCEPTION("Bad state ID : ID must be higher or equal to 0");

			return EC_BAD_ARGS;
		}

		AK::SoundEngine::SetState(static_cast<AkStateGroupID>(_dStateGroup), static_cast<AkStateID>(_dState));

		return EC_NONE;
	}

    //----------------------------------------------------------------
    // Register a wwise plugin. --------------------------------------
    GMW_API double STDCALL GMWRegisterPlugin(double _dType)
    {
        int nType = (int)_dType;
        if(nType < 0)
        {
            char pcMessage[256];
            sprintf(pcMessage, "Bad type ID (%d): ID must be higher or equal to 0", nType);
            GMW_EXCEPTION(pcMessage);

            return EC_BAD_ARGS;
        }

        AKRESULT nResult = AK_Success;
        switch(nType)
        {
            // Sine
        case 0:
            nResult = AK::SoundEngine::RegisterPlugin(AkPluginTypeSource, AKCOMPANYID_AUDIOKINETIC, AKSOURCEID_SINE, CreateSineSource, CreateSineSourceParams);
            break;

            // Tone Generator
        case 1:
            nResult = AK::SoundEngine::RegisterPlugin(AkPluginTypeSource, AKCOMPANYID_AUDIOKINETIC, AKSOURCEID_TONE, CreateToneSource, CreateToneSourceParams);
            break;

            // Silence
        case 2:
            nResult = AK::SoundEngine::RegisterPlugin(AkPluginTypeSource, AKCOMPANYID_AUDIOKINETIC, AKSOURCEID_SILENCE, CreateSilenceSource, CreateSilenceSourceParams);
            break;
            
            // Audio Input
        case 3:
            nResult = AK::SoundEngine::RegisterPlugin(AkPluginTypeSource, AKCOMPANYID_AUDIOKINETIC, AKSOURCEID_AUDIOINPUT, CreateAudioInputSource, CreateAudioInputSourceParams);			
            break;

//             // MP3 Input
//         case 4:
//             AK::SoundEngine::RegisterPlugin(AkPluginTypeSource, AKCOMPANYID_AUDIOKINETIC, AKSOURCEID_MP3, CreateMP3Source, CreateMP3SourceParams);
//             break;        

            // Delay
        case 4:
            nResult = AK::SoundEngine::RegisterPlugin(AkPluginTypeEffect, AKCOMPANYID_AUDIOKINETIC, AKEFFECTID_DELAY, CreateDelayFX, CreateDelayFXParams);
            break;

            // Parametric EQ
        case 5:
            nResult = AK::SoundEngine::RegisterPlugin(AkPluginTypeEffect, AKCOMPANYID_AUDIOKINETIC, AKEFFECTID_PARAMETRICEQ, CreateParametricEQFX, CreateParametricEQFXParams);
            break;

            // Matrix Reverb
        case 6:
            nResult = AK::SoundEngine::RegisterPlugin(AkPluginTypeEffect, AKCOMPANYID_AUDIOKINETIC, AKEFFECTID_MATRIXREVERB, CreateMatrixReverbFX, CreateMatrixReverbFXParams);
            break;

            // Compressor
        case 7:
            AK::SoundEngine::RegisterPlugin(AkPluginTypeEffect, AKCOMPANYID_AUDIOKINETIC, AKEFFECTID_COMPRESSOR, CreateCompressorFX, CreateCompressorFXParams);
            break;

            // Expander
        case 8:
            nResult = AK::SoundEngine::RegisterPlugin(AkPluginTypeEffect, AKCOMPANYID_AUDIOKINETIC, AKEFFECTID_EXPANDER, CreateExpanderFX, CreateExpanderFXParams);
            break;

            // Peak Limiter
        case 9:
            nResult = AK::SoundEngine::RegisterPlugin(AkPluginTypeEffect, AKCOMPANYID_AUDIOKINETIC, AKEFFECTID_PEAKLIMITER, CreatePeakLimiterFX, CreatePeakLimiterFXParams);
            break;

            // Roomverb.
        case 10:
            nResult = AK::SoundEngine::RegisterPlugin(AkPluginTypeEffect, AKCOMPANYID_AUDIOKINETIC, AKEFFECTID_ROOMVERB, CreateRoomVerbFX, CreateRoomVerbFXParams);
            break;

			// Pitch Shifter.
		case 11:
			nResult = AK::SoundEngine::RegisterPlugin(AkPluginTypeEffect, AKCOMPANYID_AUDIOKINETIC, AKEFFECTID_PITCHSHIFTER, CreatePitchShifterFX, CreatePitchShifterFXParams);
			break;

			// Meter
		case 12:
			nResult = AK::SoundEngine::RegisterPlugin(AkPluginTypeEffect, AKCOMPANYID_AUDIOKINETIC, AKEFFECTID_METER, CreateMeterFX, CreateMeterFXParams);
			break;

        default:
            GMW_EXCEPTION("Unimplemented");
        }

        if(nResult != AK_Success)
        {
            GMW_EXCEPTION("Unable to register plugin.");
        }

        return EC_NONE;
    }

    //----------------------------------------------------------------
    // Register a wwise codec. ---------------------------------------
    GMW_API double STDCALL GMWRegisterCodec(double _dType)
    {
        if(_dType != 0)
        {
            GMW_EXCEPTION("Bad type ID : ID must be higher or equal to 0 and lower or equal to 0 (currently, only vorbis codec is supported)");

            return EC_BAD_ARGS;
        }

        AKRESULT nResult;
        switch((int)_dType)
        {
        // Vorbis codec.
        case 0:
            nResult = AK::SoundEngine::RegisterCodec(AKCOMPANYID_AUDIOKINETIC, AKCODECID_VORBIS, CreateVorbisFilePlugin, CreateVorbisBankPlugin);
            break;

        default:
            GMW_EXCEPTION("Unimplemented");
        }

        if(nResult != AK_Success)
        {
            GMW_EXCEPTION("Unable to register codec.");
        }

        return EC_NONE;
    }
}
