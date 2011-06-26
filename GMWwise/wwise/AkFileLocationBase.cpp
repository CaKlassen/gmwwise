//////////////////////////////////////////////////////////////////////
//
// AkFileLocationBase.cpp
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

#include "wwise/AkFileLocationBase.h"

#include <AK/SoundEngine/Common/IAkStreamMgr.h>
#include <AK/Plugin/AkVorbisFactory.h>	// For Vorbis CODEC_ID.
#include <AK/Tools/Common/AkPlatformFuncs.h>
#include <wchar.h>
#include <stdio.h>
#include <assert.h>


#define MAX_NUMBER_STRING_SIZE      (10)    // 4G
#define ID_TO_STRING_FORMAT_BANK    (L"%u.bnk")
#define ID_TO_STRING_FORMAT_WAV     (L"%u.wav")
#define ID_TO_STRING_FORMAT_XMA     (L"%u.xma")
#define ID_TO_STRING_FORMAT_VORBIS  (L"%u.ogg")
#define MAX_EXTENSION_SIZE          (4)     // .xxx
#define MAX_FILETITLE_SIZE          (MAX_NUMBER_STRING_SIZE+MAX_EXTENSION_SIZE+1)   // null-terminated


template< class TYPE > inline
const TYPE& AkTemplMax( const TYPE& in_left, const TYPE& in_right )
{
	return ( in_left < in_right ) ? in_right : in_left;
}


CAkFileLocationBase::CAkFileLocationBase()
{
	m_szBasePath[0] = NULL;
    m_szBankPath[0] = NULL;
    m_szAudioSrcPath[0] = NULL;
    m_szLangSpecificDirName[0] = NULL;
}

CAkFileLocationBase::~CAkFileLocationBase()
{
}

// String overload.
// Returns AK_Success if input flags are supported and the resulting path is not too long.
// Returns AK_Fail otherwise.
AKRESULT CAkFileLocationBase::GetFullFilePath(
	const AkOSChar*			in_pszFileName,		// File name.
	AkFileSystemFlags * in_pFlags,			// Special flags. Can be NULL.
	AkOSChar *			out_pszFullFilePath // Full file path.
	)
{
    if ( !in_pszFileName )
    {
        assert( !"Invalid file name" );
        return AK_InvalidParameter;
    }

    // Prepend string path (basic file system logic).

    // Compute file name with file system paths.
    size_t uiPathSize = wcslen( in_pszFileName );

    if ( uiPathSize >= AK_MAX_PATH )
	{
		assert( !"Input string too large" );
		return AK_InvalidParameter;
	}

	AKPLATFORM::SafeStrCpy( out_pszFullFilePath, m_szBasePath, AK_MAX_PATH );

    if ( in_pFlags )
    {
        // Add bank path if file is an AK sound bank.
        if ( in_pFlags->uCompanyID == AKCOMPANYID_AUDIOKINETIC &&
             in_pFlags->uCodecID == AKCODECID_BANK )
		{
			uiPathSize += wcslen( m_szBankPath );
			if ( uiPathSize >= AK_MAX_PATH )
			{
				assert( !"Path is too large" );
				return AK_Fail;
			}
			AKPLATFORM::SafeStrCat( out_pszFullFilePath, m_szBankPath, AK_MAX_PATH );
		}

		// Note. Stream files do not use this overload.

		// Add language directory name if needed.
		if ( in_pFlags->bIsLanguageSpecific )
		{
			uiPathSize += wcslen( m_szLangSpecificDirName );
			if ( uiPathSize >= AK_MAX_PATH )
			{
				assert( !"Path is too large" );
				return AK_Fail;
			}
			AKPLATFORM::SafeStrCat( out_pszFullFilePath, m_szLangSpecificDirName, AK_MAX_PATH );
		}
	}

    // Append file title.
	uiPathSize += wcslen( out_pszFullFilePath );
	if ( uiPathSize >= AK_MAX_PATH )
	{
		assert( !"File name string too large" );
		return AK_Fail;
	}
	AKPLATFORM::SafeStrCat( out_pszFullFilePath, in_pszFileName, AK_MAX_PATH );
	return AK_Success;
}

// ID overload.
// The name of the file will be formatted as ID.ext. This is meant to be used with options
// "Use SoundBank Names" unchecked, and/or "Copy Streamed Files" in the SoundBank Settings.
// For more details, refer to the SoundBank Settings in Wwise Help, and to section "Identifying Banks" inside
// "Sound Engine Integration Walkthrough > Integrate Wwise Elements into Your Game > Integrating Banks >
// Integration Details - Banks > General Information" of the SDK documentation.
// Returns AK_Success if input flags are supported and the resulting path is not too long.
// Returns AK_Fail otherwise.
AKRESULT CAkFileLocationBase::GetFullFilePath(
	AkFileID			in_fileID,			// File ID.
	AkFileSystemFlags *	in_pFlags,			// Special flags.
	AkOSChar *			out_pszFullFilePath	// Full file path.
	)
{
    // If the file descriptor could not be found, or if the script-based FS does not exist,
    // map file ID to file descriptor (string based) for Audiokinetic IDs.

	if ( !in_pFlags ||
         in_pFlags->uCompanyID != AKCOMPANYID_AUDIOKINETIC )
	{
		assert( !"Unhandled file type" );
		return AK_Fail;
	}

	// Compute file name with file system paths.
	size_t uiPathSize = wcslen( m_szBasePath );

	// Copy base path.
	AKPLATFORM::SafeStrCpy( out_pszFullFilePath, m_szBasePath, AK_MAX_PATH );
	// Concatenate path for AK banks or streamed audio files (everything except banks).
	if ( in_pFlags->uCodecID == AKCODECID_BANK )
	{
		uiPathSize += wcslen( m_szBankPath );
		if ( uiPathSize >= AK_MAX_PATH )
		{
			assert( !"Path is too large" );
			return AK_Fail;
		}
		AKPLATFORM::SafeStrCat( out_pszFullFilePath, m_szBankPath, AK_MAX_PATH );
	}
	else
	{
		uiPathSize += wcslen( m_szAudioSrcPath );
		if ( uiPathSize >= AK_MAX_PATH )
		{
			assert( !"Path is too large" );
			return AK_Fail;
		}
		AKPLATFORM::SafeStrCat( out_pszFullFilePath, m_szAudioSrcPath, AK_MAX_PATH );
	}

	// Add language directory name if needed.
	if ( in_pFlags->bIsLanguageSpecific )
	{
		uiPathSize += wcslen( m_szLangSpecificDirName );
		if ( uiPathSize >= AK_MAX_PATH )
		{
			assert( !"Path is too large" );
			return AK_Fail;
		}
		AKPLATFORM::SafeStrCat( out_pszFullFilePath, m_szLangSpecificDirName, AK_MAX_PATH );
	}

	// Append file title.
	if ( ( uiPathSize + MAX_FILETITLE_SIZE ) <= AK_MAX_PATH )
	{
		AkOSChar * pszTitle = out_pszFullFilePath + uiPathSize;
		size_t uNumCharsLeft = AK_MAX_PATH - uiPathSize;
		if ( in_pFlags->uCodecID == AKCODECID_BANK )
			swprintf( pszTitle, uNumCharsLeft, ID_TO_STRING_FORMAT_BANK, in_fileID );
		else if ( in_pFlags->uCodecID == AKCODECID_XMA )
			swprintf( pszTitle, uNumCharsLeft, ID_TO_STRING_FORMAT_XMA, in_fileID );
		else if ( in_pFlags->uCodecID == AKCODECID_VORBIS )
			swprintf( pszTitle, uNumCharsLeft, ID_TO_STRING_FORMAT_VORBIS, in_fileID );
		else
			swprintf( pszTitle, uNumCharsLeft, ID_TO_STRING_FORMAT_WAV, in_fileID );
	}
	else
	{
		assert( !"String buffer too small" );
		return AK_Fail;
	}

	return AK_Success;
}

AKRESULT CAkFileLocationBase::SetBasePath(
    const AkOSChar*   in_pszBasePath
    )
{
	if ( wcslen( in_pszBasePath ) + AkTemplMax( wcslen( m_szBankPath ), wcslen( m_szAudioSrcPath ) ) + wcslen( m_szLangSpecificDirName ) >= AK_MAX_PATH )
	{
		return AK_InvalidParameter;
	}
	AKPLATFORM::SafeStrCpy( m_szBasePath, in_pszBasePath, AK_MAX_PATH );
	return AK_Success;
}

AKRESULT CAkFileLocationBase::SetBankPath(
    const AkOSChar*   in_pszBankPath
    )
{
    if ( wcslen( m_szBasePath ) + AkTemplMax( wcslen( in_pszBankPath ), wcslen( m_szAudioSrcPath ) ) + wcslen( m_szLangSpecificDirName ) >= AK_MAX_PATH )
	{
		return AK_InvalidParameter;
	}
	AKPLATFORM::SafeStrCpy( m_szBankPath, in_pszBankPath, AK_MAX_PATH );
	return AK_Success;
}

AKRESULT CAkFileLocationBase::SetAudioSrcPath(
    const AkOSChar*   in_pszAudioSrcPath
    )
{
    if ( wcslen( m_szBasePath ) + AkTemplMax( wcslen( m_szBankPath ), wcslen( in_pszAudioSrcPath ) ) + wcslen( m_szLangSpecificDirName ) >= AK_MAX_PATH )
	{
		return AK_InvalidParameter;
	}
	AKPLATFORM::SafeStrCpy( m_szAudioSrcPath, in_pszAudioSrcPath, AK_MAX_PATH );
	return AK_Success;
}

AKRESULT CAkFileLocationBase::SetLangSpecificDirName(
    const AkOSChar*   in_pszDirName
    )
{
    if ( wcslen( m_szBasePath ) + AkTemplMax( wcslen( m_szBankPath ), wcslen( m_szAudioSrcPath ) ) + wcslen( in_pszDirName ) >= AK_MAX_PATH )
	{
		return AK_InvalidParameter;
	}
	AKPLATFORM::SafeStrCpy( m_szLangSpecificDirName, in_pszDirName, AK_MAX_PATH );
	return AK_Success;
}

