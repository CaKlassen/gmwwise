//////////////////////////////////////////////////////////////////////
//
// AkFilePackageLUT.h
//
// This class parses the header of file packages that were created with the
// AkFilePackager utility app (located in ($WWISESDK)/samples/FilePackager/),
// and looks-up files at run-time.
//
// The header of these file packages contains look-up tables that describe the
// internal offset of each file it references, their block size (required alignment),
// and their language. Each combination of AkFileID and Language ID is unique.
//
// The language was created dynamically when the package was created. The header
// also contains a map of language names (strings) to their ID, so that the proper
// language-specific version of files can be resolved. The language name that is stored
// matches the name of the directory that is created by the Wwise Bank Manager,
// except for the trailing slash.
//
// Copyright (c) 2007-2008 Audiokinetic Inc. / All Rights Reserved
//
//////////////////////////////////////////////////////////////////////

#ifndef _AK_FILE_PACKAGE_LUT_H_
#define _AK_FILE_PACKAGE_LUT_H_

#include "GMWConfig.h"
#include <AK/SoundEngine/Common/IAkStreamMgr.h>
#include <AK/Tools/Common/AkAssert.h>

// AK file packager definitions.
#define AKPK_CURRENT_VERSION		(1)

#define AKPK_HEADER_CHUNK_DEF_SIZE	(8)	// The header chunk definition is 8 bytes wide.

#define AKPK_FILE_FORMAT_TAG	\
		AkmmioFOURCC('A','K','P','K')

//-----------------------------------------------------------------------------
// Name: class CAkFilePackageLUT.
// Desc: Keeps pointers to various parts of the header. Offers look-up services
// for file look-up and soundbank ID retrieval.
//-----------------------------------------------------------------------------
class CAkFilePackageLUT
{
public:

	static const AkUInt16 AK_INVALID_LANGUAGE_ID = 0;
	struct AkFileEntry
    {
        AkFileID	fileID;		// File identifier.
		AkUInt32	uBlockSize;	// Size of one block, required alignment (in bytes).
		AkInt64		iFileSize;  // File size in bytes.
        AkUInt32	uStartBlock;// Start block, expressed in terms of uBlockSize.
        AkUInt32	uLanguageID;// Language ID. AK_INVALID_LANGUAGE_ID if not language-specific.
    };

    CAkFilePackageLUT();
    virtual ~CAkFilePackageLUT();

	// Create a new LUT from a packaged file header.
	// The LUT sets pointers to appropriate location inside header data (in_pData).
	AKRESULT Setup(
		AkUInt8 *			in_pData,			// Header data.
		AkUInt32			in_uHeaderSize		// Size of file package header.
		);

	// Find a file entry by ID.
	const AkFileEntry * LookupFile(
		AkFileID			in_uID,				// File ID.
		AkFileSystemFlags * in_pFlags			// Special flags. Do not pass NULL.
		);

	// Set current language.
	// Returns AK_InvalidLanguage if a package is loaded but the language string cannot be found.
	// Returns AK_Success otherwise.
	AKRESULT SetCurLanguage(
		AkLpCtstr			in_pszLanguage		// Language string.
		);

	// Find a soundbank ID by its name.
	// Returns AK_INVALID_FILE_ID if no soundbank LUT is loaded.
	AkFileID GetSoundBankID(
		AkLpCtstr			in_pszBankName		// Soundbank name.
		);

protected:
	static void RemoveFileExtension( AkTChar* in_pstring );
	static void _MakeLower( AkTChar* in_pString );

	//
	// File LUTs.
	//
	class FileLUT
	{
	public:
		const AkFileEntry *	FileEntries() const { return (AkFileEntry*)((AkUInt32*)this + 1); }
		bool HasFiles() const { return ( m_uNumFiles > 0 ); }
		AkUInt32 NumFiles() const { return m_uNumFiles; }
	private:
		FileLUT();	// Do not create this object, just cast raw data.
		AkUInt32		m_uNumFiles;
	};

	// Helper: Find a file entry by ID.
	const AkFileEntry * LookupFile(
		AkFileID			in_uID,					// File ID.
		const FileLUT *		in_pLut,				// LUT to search.
		bool				in_bIsLanguageSpecific	// True: match language ID.
		);

private:

	AkUInt16			m_curLangID;	// Current language.


	//
	// Maps format.
	//
	class StringMap
	{
	public:
		// Returns AK_INVALID_UNIQUE_ID if ID is not found.
		AkUInt32 GetID( AkLpCtstr in_pszString );
	private:
		struct StringEntry
		{
			AkUInt32	uOffset;	// Byte offset of the string in the packaged strings section,
									// from beginning of the string map.
			AkUInt32	uID;		// ID.
		};
		StringMap();	// Do not create this object, just cast raw data to use GetID().
		AkUInt32	m_uNumStrings;
	};

	// Languages map.
	StringMap *			m_pLangMap;

	// SoundBanks LUT.
    FileLUT *			m_pSoundBanks;

	// StreamedFiles LUT.
    FileLUT	*			m_pStmFiles;
};

#endif //_AK_FILE_PACKAGE_LUT_H_
