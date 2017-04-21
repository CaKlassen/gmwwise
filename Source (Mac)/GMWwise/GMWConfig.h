#ifndef _GMW_CONFIG_
#define _GMW_CONFIG_

#include <cstdlib>
#include <string>
#include <sstream>

#define GMW_API __attribute__((visibility("default")))

#define STDCALL

#define GMW_VERSION_STRING "1.5.0"

#include <AK/SoundEngine/Common/AkSoundEngine.h>
#include <AK/IBytes.h>
#include <AK/SoundEngine/Common/AkMemoryMgr.h>
#include <AK/SoundENgine/Common/AkModule.h>
#include <AK/SoundEngine/Common/IAkStreamMgr.h>
#include <AK/Tools/Common/AkPlatformFuncs.h>
#include <AK/MusicEngine/Common/AkMusicEngine.h>
#include <AK/SoundEngine/Common/AkStreamMgrModule.h>
#include <AK/SoundEngine/Common/AkQueryParameters.h>

#ifndef AK_OPTIMIZED
#   include <AK/Comm/AkCommunication.h>
#endif

typedef unsigned long DWORD;
typedef unsigned short WORD;
typedef unsigned int UNINT32;

/// @enum List of error code.
enum ExceptionCode
{
	EC_BAD_ARGS = -1,		///< Bad arguments
	EC_NONE = 0,			///< No error
	EC_MEMORY,				///<
	EC_IO,					///< I/O error
	EC_STREAM_MGR,			///<
	EC_SOUND_ENGINE,		///<
	EC_MUSIC_ENGINE,		///<
	EC_BANK,				///<
	EC_RTPC,
#ifndef AK_OPTIMIZED
    EC_COM,					///<
#endif
};

#endif // _GMW_CONFIG_
