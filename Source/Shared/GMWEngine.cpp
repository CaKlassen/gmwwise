#include "GMWEngine.h"
#include "GMWBank.h"

#if defined(__APPLE__)
#include <sys/mman.h>
#endif

#include "AkFilePackageLowLevelIOBlocking.h"
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
#if defined(_WIN32)
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
#elif defined(__APPLE__)
	void * AllocHook(size_t in_size)
	{
		return malloc(in_size);
	}
	void FreeHook(void * in_ptr)
	{
		free(in_ptr);
	}
#endif
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
		setlocale(LC_ALL, "");

		AkMemSettings memSettings;
		memSettings.uMaxNumPools = 20;

		AKRESULT result = AK::MemoryMgr::Init(&memSettings);
        if(result != AK_Success)
		{
			errorCode = result;
            return -1;
		}

        AkStreamMgrSettings stmSettings;
        AK::StreamMgr::GetDefaultSettings(stmSettings);
        if(!AK::StreamMgr::Create( stmSettings ) )
        {
			errorCode = AK_Fail;
            return -1;
        }

        AkDeviceSettings deviceSettings;
        AK::StreamMgr::GetDefaultDeviceSettings( deviceSettings );
        if((result = g_lowLevelIO.Init(deviceSettings)) != AK_Success)
		{
			errorCode = result;
            return -1;
		}

        AkInitSettings initSettings;
        AkPlatformInitSettings platformInitSettings;
        AK::SoundEngine::GetDefaultInitSettings( initSettings );
		initSettings.uDefaultPoolSize = 2 * 1024 * 1024;
        AK::SoundEngine::GetDefaultPlatformInitSettings( platformInitSettings );
		platformInitSettings.uLEngineDefaultPoolSize = 1 * 1024 * 1024;
        if((result = AK::SoundEngine::Init(&initSettings, &platformInitSettings)) != AK_Success)
        {
			errorCode = result;
            return -1;
        }

        AkMusicSettings musicInit;
        AK::MusicEngine::GetDefaultInitSettings( musicInit );
        if((result = AK::MusicEngine::Init(&musicInit)) != AK_Success)
        {
			errorCode = result;
            return -1;
        }

#ifndef AK_OPTIMIZED
        // Initialize communication.
        AkCommSettings settingsComm;
        AK::Comm::GetDefaultInitSettings( settingsComm );
        if ((result = AK::Comm::Init( settingsComm )) != AK_Success )
        {
			errorCode = result;
            return -1;
        }
#endif

        return 0;
    }

	// Shut down the Wwise engine
    double GMWShutdown(void)
    {
#ifndef AK_OPTIMIZED
        AK::Comm::Term();	   
#endif // AK_OPTIMIZED	
		auto result = AK::SoundEngine::UnregisterAllGameObj();
		if (result != AK_Success)
		{
			errorCode = result;
			return -1;
		}

		GMWClearBanks();	

		AK::MusicEngine::Term();

		AK::SoundEngine::Term();
		
		g_lowLevelIO.Term();

		if(AK::IAkStreamMgr::Get())
		{   
			AK::IAkStreamMgr::Get()->Destroy();
		}

		AK::MemoryMgr::Term();

		return 0;
    }

	// Processes a frame of audio
    double GMWProcessAudio(void)
    {
        auto result = AK::SoundEngine::RenderAudio();
		if (!result)
		{
			errorCode = result;
			return -1;
		}

		return 0;
    }

	// Sets the state of a specific state group
	double GMWSetState(double _dStateGroup, double _dState)
	{
		auto result = AK::SoundEngine::SetState(static_cast<AkStateGroupID>(_dStateGroup), static_cast<AkStateID>(_dState));
		if (result != AK_Success)
		{
			errorCode = result;
			return -1;
		}

		return 0;
	}
}
