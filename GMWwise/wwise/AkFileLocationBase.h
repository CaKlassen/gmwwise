//////////////////////////////////////////////////////////////////////
//
// AkFileLocationBase.h
//
// Basic file location resolving: Uses simple path concatenation logic.
// Exposes basic path functions for convenience.
// For more details on resolving file location, refer to section "File Location" inside
// "Going Further > Overriding Managers > Streaming / Stream Manager > Low-Level I/O"
// of the SDK documentation.
//
// Copyright (c) 2006-2008 Audiokinetic Inc. / All Rights Reserved
//
//////////////////////////////////////////////////////////////////////

#ifndef _AK_FILE_LOCATION_BASE_H_
#define _AK_FILE_LOCATION_BASE_H_

struct AkFileSystemFlags;

#include "GMWConfig.h"
#include <AK/SoundEngine/Common/AkTypes.h>

class CAkFileLocationBase
{
public:
	CAkFileLocationBase();
	virtual ~CAkFileLocationBase();

	//
	// Global path functions.
	// ------------------------------------------------------

	// Base path is prepended to all file names.
	// Audio source path is appended to base path whenever uCompanyID is AK and uCodecID specifies an audio source.
	// Bank path is appended to base path whenever uCompanyID is AK and uCodecID specifies a sound bank.
	// Language specific dir name is appended to path whenever "bIsLanguageSpecific" is true.
	AKRESULT SetBasePath(
		AkLpCtstr   in_pszBasePath
		);
	AKRESULT SetBankPath(
		AkLpCtstr   in_pszBankPath
		);
	AKRESULT SetAudioSrcPath(
		AkLpCtstr   in_pszAudioSrcPath
		);
	AKRESULT SetLangSpecificDirName(
		AkLpCtstr   in_pszDirName
		);

	//
	// Path resolving services.
	// ------------------------------------------------------

	// String overload.
	// Returns AK_Success if input flags are supported and the resulting path is not too long.
	// Returns AK_Fail otherwise.
	AKRESULT GetFullFilePath(
		AkLpCtstr			in_pszFileName,		// File name.
		AkFileSystemFlags * in_pFlags,			// Special flags. Can be NULL.
		AkTChar *			out_pszFullFilePath // Full file path.
		);

	// ID overload.
	// The name of the file will be formatted as ID.ext. This is meant to be used with options
	// "Use SoundBank Names" unchecked, and/or "Copy Streamed Files" in the SoundBank Settings.
	// For more details, refer to the SoundBank Settings in Wwise Help, and to section "Identifying Banks" inside
	// "Sound Engine Integration Walkthrough > Integrate Wwise Elements into Your Game > Integrating Banks >
	// Integration Details - Banks > General Information" of the SDK documentation.
	// Returns AK_Success if input flags are supported and the resulting path is not too long.
	// Returns AK_Fail otherwise.
	AKRESULT GetFullFilePath(
		AkFileID			in_fileID,			// File ID.
		AkFileSystemFlags *	in_pFlags,			// Special flags.
		AkTChar *			out_pszFullFilePath	// Full file path.
		);

protected:

	// Internal user paths.
	AkTChar			m_szBasePath[AK_MAX_PATH];
	AkTChar			m_szBankPath[AK_MAX_PATH];
	AkTChar			m_szAudioSrcPath[AK_MAX_PATH];
	AkTChar			m_szLangSpecificDirName[AK_MAX_PATH];

};

#endif //_AK_FILE_LOCATION_BASE_H_
