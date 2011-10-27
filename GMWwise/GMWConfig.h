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
#ifndef _GMW_CONFIG_
#define _GMW_CONFIG_

#define NOGDI
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <cstdlib>
#include <string>
#include <sstream>

#define GMW_API __declspec(dllexport)

#if _MSC_VER <= 1400
#   define STDCALL __stdcall
#else
#   define STDCALL
#endif

#define GMW_VERSION_STRING "1.1"

#define GMW_EXCEPTION(msg) MessageBox(NULL, msg, "GMWwise Exception (version 1.1)", MB_OK | MB_ICONSTOP)

#include <AK/SoundEngine/Common/AkSoundEngine.h>
#include <AK/IBytes.h>
#include <AK/SoundEngine/Common/AkMemoryMgr.h>
#include <AK/SoundENgine/Common/AkModule.h>
#include <AK/SoundEngine/Common/IAkStreamMgr.h>
#include <AK/Tools/Common/AkPlatformFuncs.h>
#include <AK/MusicEngine/Common/AkMusicEngine.h>
#include <AK/SoundEngine/Common/AkStreamMgrModule.h>

#include <AK/Plugin/AkAudioInputSourceFactory.h>
#include <AK/Plugin/AkCompressorFXFactory.h>
#include <AK/Plugin/AkConvolutionReverbFXFactory.h>
#include <AK/Plugin/AkDelayFXFactory.h>
#include <AK/Plugin/AkExpanderFXFactory.h>
#include <AK/Plugin/AkFlangerFXFactory.h>
#include <AK/Plugin/AkGuitarDistortionFXFactory.h>
#include <AK/Plugin/AkMatrixReverbFXFactory.h>
#include <AK/Plugin/AkMeterFXFactory.h>
#include <AK/Plugin/AkMotionGeneratorFactory.h>
#include <AK/Plugin/AkMP3SourceFactory.h>
#include <AK/Plugin/AkParametricEQFXFactory.h>
#include <AK/Plugin/AkPeakLimiterFXFactory.h>
#include <AK/Plugin/AkRoomVerbFXFactory.h>
#include <AK/Plugin/AkRumbleFactory.h>
#include <AK/Plugin/AkSilenceSourceFactory.h>
#include <AK/Plugin/AkSineSourceFactory.h>
#include <AK/Plugin/AkSoundSeedImpactFXFactory.h>
#include <AK/Plugin/AkSoundSeedWooshFactory.h>
#include <AK/Plugin/AkToneSourceFactory.h>
#include <AK/Plugin/AkTremoloFXFactory.h>
#include <AK/Plugin/AkVorbisFactory.h>

#ifndef AK_OPTIMIZED
#   include <AK/Comm/AkCommunication.h>
#endif

enum ExceptionCode
{
	EC_BAD_ARGS = -1,
	EC_NONE = 0,
	EC_MEMORY,
	EC_IO,
	EC_STREAM_MGR,
	EC_SOUND_ENGINE,
	EC_MUSIC_ENGINE,
	EC_BANK,
#ifndef AK_OPTIMIZED
    EC_COM,
#endif
};

#endif // _GMW_CONFIG_
