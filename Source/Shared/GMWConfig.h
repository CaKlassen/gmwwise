#ifndef _GMW_CONFIG_
#define _GMW_CONFIG_

#include <cstdlib>
#include <string>
#include <sstream>

#if defined(_WIN32)

#define NOGDI
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#define GMW_API __declspec(dllexport)

#if _MSC_VER <= 1400
#   define STDCALL __stdcall
#else
#   define STDCALL
#endif

#elif defined(__APPLE__)

#define GMW_API __attribute__((visibility("default")))
#define STDCALL

#elif defined(__unix__)

#define GMW_API
#define STDCALL

#endif

#define GMW_VERSION_STRING "1.6.0"

#include <AK/SoundEngine/Common/AkSoundEngine.h>
#include <AK/IBytes.h>
#include <AK/SoundEngine/Common/AkMemoryMgr.h>
#include <AK/SoundEngine/Common/AkModule.h>
#include <AK/SoundEngine/Common/IAkStreamMgr.h>
#include <AK/Tools/Common/AkPlatformFuncs.h>
#include <AK/MusicEngine/Common/AkMusicEngine.h>
#include <AK/SoundEngine/Common/AkStreamMgrModule.h>
#include <AK/SoundEngine/Common/AkQueryParameters.h>

#ifndef AK_OPTIMIZED
#   include <AK/Comm/AkCommunication.h>
#endif

static double errorCode;

///<summary>Returns the most recent error code</summary>
///<returns>The most recent error code</returns>
GMW_API double STDCALL GMWGetError();

#endif // _GMW_CONFIG_
