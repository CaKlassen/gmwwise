#include "GMWEngine.h"
#include "GMWBank.h"
#include "wwise/AkFilePackageLowLevelIOBlocking.h"
#include <AK/Plugin/AkSineSourceFactory.h>
#include <AK/Plugin/AkToneSourceFactory.h>
#include <AK/Plugin/AkSilenceSourceFactory.h>
#include <AK/Plugin/AkAudioInputPlugin.h>
#include <AK/Plugin/AkDelayFXFactory.h>
#include <AK/Plugin/AkParametricEQFXFactory.h>
#include <AK/Plugin/AkMatrixReverbFXFactory.h>
#include <AK/Plugin/AkCompressorFXFactory.h>
#include <AK/Plugin/AkExpanderFXFactory.h>
#include <AK/Plugin/AkPeakLimiterFXFactory.h>
#include <AK/Plugin/AkRoomVerbFXFactory.h>
#include <AK/Plugin/AkPitchShifterFXFactory.h>
#include <AK/Plugin/AkMeterFXFactory.h>
#include <AK/Plugin/AkVorbisDecoderFactory.h>
#include <AK/Plugin/AkConvolutionReverbFXFactory.h>
#include <AK/Plugin/AkFlangerFXFactory.h>
#include <AK/Plugin/AkGuitarDistortionFXFactory.h>
#include <AK/Plugin/AkMotionGeneratorFactory.h>
#include <AK/Plugin/AkRumbleFactory.h>
#include <AK/Plugin/AkSoundSeedImpactFXFactory.h>
#include <AK/Plugin/AkSoundSeedWindFactory.h>
#include <AK/Plugin/AkSoundSeedWooshFactory.h>
#include <AK/Plugin/AkTremoloFXFactory.h>
#include <AK/Plugin/AkSynthOneFactory.h>
#include <AK/Plugin/AkTimeStretchFXFactory.h>
#include <AK/Plugin/AkStereoDelayFXFactory.h>
#include <AK/Plugin/AkHarmonizerFXFactory.h>
#include <AK/Plugin/AkGainFXFactory.h>


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
	// Initializes the Wwise engine
	double GMWInit(void)
    {
		AkMemSettings memSettings;
		memSettings.uMaxNumPools = 20;

		AKRESULT result = AK::MemoryMgr::Init(&memSettings);
        if(result != AK_Success)
		{
			GMW_EXCEPTION("Unable to initialize the Memory Manager.");

            return EC_MEMORY;
		}

        AkStreamMgrSettings stmSettings;
        AK::StreamMgr::GetDefaultSettings(stmSettings);
        if(!AK::StreamMgr::Create( stmSettings ) )
        {
            GMW_EXCEPTION("Cannot create the Streaming Manager");

            return EC_STREAM_MGR;
        }

        AkDeviceSettings deviceSettings;
        AK::StreamMgr::GetDefaultDeviceSettings( deviceSettings );
        if(g_lowLevelIO.Init(deviceSettings) != AK_Success)
		{
			GMW_EXCEPTION("Cannot create the Streaming Device and Low-Level I/O system.");

            return EC_IO;
		}

        AkInitSettings initSettings;
        AkPlatformInitSettings platformInitSettings;
        AK::SoundEngine::GetDefaultInitSettings( initSettings );
        AK::SoundEngine::GetDefaultPlatformInitSettings( platformInitSettings );
        if(AK::SoundEngine::Init(&initSettings, &platformInitSettings) != AK_Success)
        {
            GMW_EXCEPTION("Unable to initialize the Sound Engine.");

            return EC_SOUND_ENGINE;
        }

        AkMusicSettings musicInit;
        AK::MusicEngine::GetDefaultInitSettings( musicInit );
        if(AK::MusicEngine::Init(&musicInit) != AK_Success)
        {
            GMW_EXCEPTION("Unable to initialize the Music Engine.");

            return EC_MUSIC_ENGINE;
        }

#ifndef AK_OPTIMIZED
        // Initialize communication.
        AkCommSettings settingsComm;
        AK::Comm::GetDefaultInitSettings( settingsComm );
        if ( AK::Comm::Init( settingsComm ) != AK_Success )
        {
            AKASSERT( !"Unable to initialize Profiling" );
            return EC_COM;
        }
#endif

        return EC_NONE;
    }

	// Shut down the Wwise engine
    double GMWShutdown(void)
    {
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

	// Processes a frame of audio
    double GMWProcessAudio(void)
    {
        AK::SoundEngine::RenderAudio();

		return EC_NONE;
    }

	// Sets the state of a specific state group
	double GMWSetState(double _dStateGroup, double _dState)
	{
		if(_dStateGroup < 0)
		{
			GMW_EXCEPTION("Bad state group ID: ID must be higher or equal to 0");

			return EC_BAD_ARGS;
		}

		if(_dState < 0)
		{
			GMW_EXCEPTION("Bad state ID: ID must be higher or equal to 0");

			return EC_BAD_ARGS;
		}

		AK::SoundEngine::SetState(static_cast<AkStateGroupID>(_dStateGroup), static_cast<AkStateID>(_dState));

		return EC_NONE;
	}
}
