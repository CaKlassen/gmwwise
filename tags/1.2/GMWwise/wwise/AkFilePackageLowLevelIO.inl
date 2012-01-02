//////////////////////////////////////////////////////////////////////
//
// AkFilePackageLowLevelIO.inl
//
// CAkFilePackageLowLevelIO extends a Low-Level I/O device by providing 
// the ability to reference files that are part of a file package.
// 
// It can extend either blocking or deferred I/O hooks (both inheriting from
// AK::StreamMgr::IAkLowLevelIOHook), since its base class is templated. 
// In either case, the base class must also implement 
// AK::StreamMgr::IAkFileLocationResolver. This interface defines both overloads
// for Open(), and this is where the package's look-up table is searched.
// If no match is found, then it falls back on the base implementation.
// 
// Clients of devices that use this class' functionnality simply need to call
// LoadFilePackage(), which loads and parses file packages that were created with 
// the AkFilePackager utility app (located in ($WWISESDK)/samples/FilePackager/). 
// The header of these file packages contains look-up tables that describe the 
// internal offset of each file it references, their block size (required alignment), 
// and their language. Each combination of AkFileID and Language ID is unique.
//
// LoadFilePackage() returns a package ID that can be used to unload it. Any number
// of packages can be loaded simultaneously. When Open() is called, the last package 
// loaded is searched first, then the previous one, and so on.
//
// The language ID was created dynamically when the package was created. The header 
// also contains a map of language names (strings) to their ID, so that the proper 
// language-specific version of files can be resolved. The language name that is stored
// matches the name of the directory that is created by the Wwise Bank Manager,
// except for the trailing slash.
//
// The map of soundbank names is optionally stored in the header. When this is the case, 
// users can also load banks through the string overload of LoadBank().
//
// Copyright (c) 2006-2008 Audiokinetic Inc. / All Rights Reserved
//
//////////////////////////////////////////////////////////////////////

#include "wwise/AkFilePackageLowLevelIO.h"
#include "wwise/AkFileHelpers.h"
#include <AK/Tools/Common/AkPlatformFuncs.h>

template <class T_LLIOHOOK_FILELOC>
CAkFilePackageLowLevelIO<T_LLIOHOOK_FILELOC>::CAkFilePackageLowLevelIO()
{	
}

template <class T_LLIOHOOK_FILELOC>
CAkFilePackageLowLevelIO<T_LLIOHOOK_FILELOC>::~CAkFilePackageLowLevelIO()
{
}

// Initialize/terminate.
template <class T_LLIOHOOK_FILELOC>
void CAkFilePackageLowLevelIO<T_LLIOHOOK_FILELOC>::Term()
{
    T_LLIOHOOK_FILELOC::Term();
	UnloadAllFilePackages();
	m_packages.Term();
}

// Override Open (string): Search file in each LUTx first. If it cannot be found, use base class services.
// If the file is found in the LUTs, open is always synchronous.
template <class T_LLIOHOOK_FILELOC>
AKRESULT CAkFilePackageLowLevelIO<T_LLIOHOOK_FILELOC>::Open( 
    const AkOSChar*       in_pszFileName,     // File name.
    AkOpenMode      in_eOpenMode,       // Open mode.
    AkFileSystemFlags * in_pFlags,      // Special flags. Can pass NULL.
	bool &			io_bSyncOpen,		// If true, the file must be opened synchronously. Otherwise it is left at the File Location Resolver's discretion. Return false if Open needs to be deferred.
    AkFileDesc &    out_fileDesc        // Returned file descriptor.
    )
{
    // If the file is an AK sound bank, try to find the identifier in the lookup table first.
    if ( in_eOpenMode == AK_OpenModeRead 
		&& in_pFlags 
		&& in_pFlags->uCompanyID == AKCOMPANYID_AUDIOKINETIC 
		&& in_pFlags->uCodecID == AKCODECID_BANK )
	{
		// Search file in each package.
		ListFilePackages::Iterator it = m_packages.Begin();
		while ( it != m_packages.End() )
		{
			AkFileID fileID = (*it)->lut.GetSoundBankID( in_pszFileName );
			if ( fileID != AK_INVALID_FILE_ID )
			{
				// Found the ID in the lut. 
				if ( FindPackagedFile( *it, fileID, in_pFlags, out_fileDesc ) == AK_Success )
				{
					io_bSyncOpen = true;	// File is opened, now.
					return AK_Success;
				}
			}
			++it;
		}
    }

    // It is not a soundbank, or it is not in the file package LUT. Use default implementation.
    return T_LLIOHOOK_FILELOC::Open( 
		in_pszFileName,
		in_eOpenMode,
		in_pFlags,
		io_bSyncOpen,
		out_fileDesc);
}

// Override Open (ID): Search file in each LUT first. If it cannot be found, use base class services.
// If the file is found in the LUTs, open is always synchronous.
template <class T_LLIOHOOK_FILELOC>
AKRESULT CAkFilePackageLowLevelIO<T_LLIOHOOK_FILELOC>::Open( 
    AkFileID        in_fileID,          // File ID.
    AkOpenMode      in_eOpenMode,       // Open mode.
    AkFileSystemFlags * in_pFlags,      // Special flags. Can pass NULL.
	bool &			io_bSyncOpen,		// If true, the file must be opened synchronously. Otherwise it is left at the File Location Resolver's discretion. Return false if Open needs to be deferred.
    AkFileDesc &    out_fileDesc        // Returned file descriptor.
    )
{
    // Try to find the identifier in the lookup table first.
    if ( in_eOpenMode == AK_OpenModeRead 
		&& in_pFlags 
		&& in_pFlags->uCompanyID == AKCOMPANYID_AUDIOKINETIC )
	{
		// Search file in each package.
		ListFilePackages::Iterator it = m_packages.Begin();
		while ( it != m_packages.End() )
		{
			if ( FindPackagedFile( *it, in_fileID, in_pFlags, out_fileDesc ) == AK_Success )
			{
				// File found. Return now.
				io_bSyncOpen = true;	// File is opened, now.
				return AK_Success;
			}
			++it;
		}
	}

    // If it the fileID is not in the LUT, perform standard path concatenation logic.
    return T_LLIOHOOK_FILELOC::Open( 
		in_fileID,
		in_eOpenMode,
		in_pFlags,
		io_bSyncOpen,
		out_fileDesc);
}

// Override Close: Do not close handle if file descriptor is part of the current packaged file.
template <class T_LLIOHOOK_FILELOC>
AKRESULT CAkFilePackageLowLevelIO<T_LLIOHOOK_FILELOC>::Close(
    AkFileDesc & in_fileDesc      // File descriptor.
    )
{
	// Do not close handle if it is that of the file package (closed only in ResetFS()).
    if ( !IsInPackage( in_fileDesc ) )
        return T_LLIOHOOK_FILELOC::Close( in_fileDesc );
    
	return AK_Success;
}

// Override GetBlockSize: Get the block size of the LUT if a file package is loaded.
template <class T_LLIOHOOK_FILELOC>
AkUInt32 CAkFilePackageLowLevelIO<T_LLIOHOOK_FILELOC>::GetBlockSize(
    AkFileDesc &  in_fileDesc     // File descriptor.
    )
{
	if ( IsInPackage( in_fileDesc ) )
	{
		// This file is part of a package. At Open(), we used the 
		// AkFileDesc.uCustomParamSize field to store the block size.
		return in_fileDesc.uCustomParamSize;
	}
	return T_LLIOHOOK_FILELOC::GetBlockSize( in_fileDesc );
}

// Override base class' SetLangSpecificDirName() (if defined): Need to set current language based 
// on the language directoy name on all packages currently loaded.
// Returns AK_InvalidLanguage if the language does not exist in the file package (if it is loaded).
template <class T_LLIOHOOK_FILELOC>
AKRESULT CAkFilePackageLowLevelIO<T_LLIOHOOK_FILELOC>::SetLangSpecificDirName(
    const AkOSChar*   in_pszDirName
    )
{
    AKRESULT eResult = T_LLIOHOOK_FILELOC::SetLangSpecificDirName( in_pszDirName );
    if ( eResult == AK_Success )
    {
        // If a package is loaded, use the language directory name to set up the
        // current language ID for correct language specific file mapping.
		// Do this for all packages loaded.
		ListFilePackages::Iterator it = m_packages.Begin();
		while ( it != m_packages.End() )
		{
			AKRESULT eSetLangRes = SetLanguageLUT( *it );
			if ( eSetLangRes != AK_Success )
				eResult = eSetLangRes;
			++it;
		}

    }
    return eResult;
}

// Searches the LUT to find the file data associated with the FileID.
// Returns AK_Success if the file is found.
template <class T_LLIOHOOK_FILELOC>
AKRESULT CAkFilePackageLowLevelIO<T_LLIOHOOK_FILELOC>::FindPackagedFile( 
	CAkFilePackage *	in_pPackage,	// Package to search into.
    AkFileID			in_fileID,		// File ID.
    AkFileSystemFlags * in_pFlags,		// Special flags. Can pass NULL.
    AkFileDesc &		out_fileDesc	// Returned file descriptor.
    )
{
	AKASSERT( in_pPackage && in_pFlags );
	const CAkFilePackageLUT::AkFileEntry * pEntry = in_pPackage->lut.LookupFile( in_fileID, in_pFlags );

	if ( pEntry )
	{
		// Fill file descriptor.
        out_fileDesc.deviceID   = T_LLIOHOOK_FILELOC::m_deviceID;
        out_fileDesc.hFile      = in_pPackage->GetHandle();
        out_fileDesc.iFileSize	= pEntry->iFileSize;
        out_fileDesc.uSector	= pEntry->uStartBlock;
		out_fileDesc.pCustomParam = NULL;
		// NOTE: We use the uCustomParamSize to store the block size.
		// We will determine whether this file was opened from a package by comparing 
		// uCustomParamSize with 0 (see IsInPackage()).
        out_fileDesc.uCustomParamSize = pEntry->uBlockSize;
        return AK_Success;
    }
    return AK_FileNotFound;
}

// File package loading:
// Opens a package file, parses its header, fills LUT.
// Overrides of Open() will search files in loaded LUTs first, then use default Low-Level I/O 
// services if they cannot be found.
// Any number of packages can be loaded at a time. Each LUT is searched until a match is found.
// Returns AK_Success if successful, AK_InvalidLanguage if the language was already set 
// (with SetLangSpecificDirName()) but does not exist in the LUT, AK_Fail for any other reason.
// Also returns a package ID which can be used to unload it (see UnloadFilePackage()).
template <class T_LLIOHOOK_FILELOC>
AKRESULT CAkFilePackageLowLevelIO<T_LLIOHOOK_FILELOC>::LoadFilePackage(
    const AkOSChar*   in_pszFilePackageName,	// File package name. Location is resolved using base class' Open().
	AkUInt32 &	out_uPackageID			// Returned package ID.
    )
{
	// Open package file.

	// Use Low-Level IO basic services (path concatenation) to find full file path,
    // but not to open and read packaged file: need to read blocking and buffered.
    AkOSChar szFullFilePath[AK_MAX_PATH];
	AKRESULT eRes = T_LLIOHOOK_FILELOC::GetFullFilePath(
        in_pszFilePackageName,
        NULL,
        szFullFilePath );  
    if ( eRes != AK_Success )
        return eRes;

	// Low-level raw open to perform blocking reads.
	AkFileHandle hPackageFile;
	eRes = CAkFileHelpers::OpenBlocking( szFullFilePath, hPackageFile );
    if ( eRes != AK_Success )
        return eRes;

	// Read header chunk definition.
	struct AkFilePackageHeader
	{
		AkUInt32 uFileFormatTag;
		AkUInt32 uHeaderSize;
	};

	AkUInt8 * pBufferForHeader;
	AkUInt32 uSizeToRead;
	bool bAligned = ( sizeof(AkFilePackageHeader) % CAkFileHelpers::s_uRequiredBlockSize ) > 0;
	if ( bAligned )
	{
		// Header size is not a multiple of the required block size. Allocate an aligned buffer on the stack.
		pBufferForHeader = (AkUInt8*)AkAlloca( 2 * CAkFileHelpers::s_uRequiredBlockSize );
		pBufferForHeader += ( CAkFileHelpers::s_uRequiredBlockSize - *(AkUInt32*)pBufferForHeader % CAkFileHelpers::s_uRequiredBlockSize );
		uSizeToRead = CAkFileHelpers::s_uRequiredBlockSize;
	}
	else
	{
		// Header size is a multiple of the required block size. 
		pBufferForHeader = (AkUInt8*)AkAlloca( sizeof(AkFilePackageHeader) );
		uSizeToRead = sizeof(AkFilePackageHeader);
	}

	AkUInt32 uSizeRead;
	eRes = CAkFileHelpers::ReadBlocking( hPackageFile, pBufferForHeader, 0, uSizeToRead, uSizeRead );
	if ( eRes != AK_Success
		|| uSizeRead < sizeof(AkFilePackageHeader) )
	{
		AKASSERT( !"Could not read package, or package is invalid" );
		CAkFileHelpers::CloseFile( hPackageFile );
        return AK_Fail;
	}

	const AkFilePackageHeader & uFileHeader = *(AkFilePackageHeader*)pBufferForHeader;

	if ( uFileHeader.uFileFormatTag != AKPK_FILE_FORMAT_TAG 
		|| 0 == uFileHeader.uHeaderSize )
	{
		AKASSERT( !"Invalid file package header" );
		CAkFileHelpers::CloseFile( hPackageFile );
        return AK_Fail;
	}

	// Open the file package using our parent's low-level I/O implementation.
	// The handle and block size are kept by the CAkFilePackage object.
	// However, the handle is managed by class T_LLIOHOOK_FILELOC.
	AkFileDesc fileDesc;
	bool bSyncOpen = true;
	eRes = T_LLIOHOOK_FILELOC::Open( 
		in_pszFilePackageName, 
		AK_OpenModeRead,
		NULL,
		bSyncOpen,
		fileDesc );
	AKASSERT( bSyncOpen || !"Illegal to reset bSyncOpen in Low-Level IO" );
	if ( eRes != AK_Success )
	{
		CAkFileHelpers::CloseFile( hPackageFile );
		return eRes;
	}


	// Create file package.
	// NOTE: The header size written in the file package excludes the AKPK_HEADER_CHUNK_DEF_SIZE.
	// CAkFilePackage::Create() takes the size that will be reserved for the header. It has to
	// contain the header and header chunk, and be a multiple of the I/O block size for parsing
	// because we will use it as the I/O buffer for reading.
	AkUInt32 uReservedHeaderSize = ( ( uFileHeader.uHeaderSize + AKPK_HEADER_CHUNK_DEF_SIZE + CAkFileHelpers::s_uRequiredBlockSize - 1 ) / CAkFileHelpers::s_uRequiredBlockSize ) * CAkFileHelpers::s_uRequiredBlockSize;
	// IMPORTANT: do not use hPackageFile, which is used only to read the header with minimal I/O constraints.
	AkUInt8 * pFilePackageHeader;
	CAkFilePackage * pPackage = CAkFilePackage::Create( 
		fileDesc.hFile,			// File handle of the package. 
		in_pszFilePackageName,
		uReservedHeaderSize,
		T_LLIOHOOK_FILELOC::GetBlockSize( fileDesc ),
		pFilePackageHeader );
	if ( !pPackage || !pFilePackageHeader )
	{
		AKASSERT( !"Could not create file package" );
		CAkFileHelpers::CloseFile( hPackageFile );
        return AK_Fail;
	}

	AkUInt32 uHeaderSize = uFileHeader.uHeaderSize;
	AkUInt32 uHeaderReadOffset = AKPK_HEADER_CHUNK_DEF_SIZE;

	// If we had already read more than sizeof(AkFilePackageHeader), copy the rest now.
	if ( uSizeRead > sizeof(AkFilePackageHeader) )
	{
		pBufferForHeader += sizeof(AkFilePackageHeader);
		AkUInt32 uSizeToCopy = uSizeRead - sizeof(AkFilePackageHeader);
		AKPLATFORM::AkMemCpy( pFilePackageHeader+AKPK_HEADER_CHUNK_DEF_SIZE, pBufferForHeader, uSizeToCopy );
		// Adjust header size and read offset.
		assert( uHeaderSize >= uSizeToCopy );
		uHeaderSize -= uSizeToCopy;
		uHeaderReadOffset += uSizeToCopy;
		// Round it up to required block size. It should be equal to the size that was reserved (minus what was already read).
		uHeaderSize = ( ( uHeaderSize + CAkFileHelpers::s_uRequiredBlockSize - 1 ) / CAkFileHelpers::s_uRequiredBlockSize ) * CAkFileHelpers::s_uRequiredBlockSize;
		assert( uHeaderSize == uReservedHeaderSize - uSizeRead );
	}

	// Stream in remaining of the header.
	if ( uHeaderSize > 0 )
	{
		assert( uHeaderReadOffset % CAkFileHelpers::s_uRequiredBlockSize == 0 );
		if ( CAkFileHelpers::ReadBlocking( hPackageFile, pFilePackageHeader+uHeaderReadOffset, uSizeRead, uHeaderSize, uSizeRead ) != AK_Success
			|| uSizeRead < uHeaderSize )
		{
			AKASSERT( !"Could not read file package" );
			CAkFileHelpers::CloseFile( hPackageFile );
			T_LLIOHOOK_FILELOC::Close( fileDesc );
			pPackage->Destroy();
			return AK_Fail;
		}
	}

	// Close package file handle used for parsing.
	CAkFileHelpers::CloseFile( hPackageFile );

	// Parse LUT.
	eRes = pPackage->lut.Setup( pFilePackageHeader, uFileHeader.uHeaderSize + AKPK_HEADER_CHUNK_DEF_SIZE );
	if ( eRes != AK_Success )
	{
		T_LLIOHOOK_FILELOC::Close( fileDesc );
		pPackage->Destroy();
		return eRes;
	}

	// Add to packages list.
	m_packages.AddFirst( pPackage );

	// Return package ID.
	out_uPackageID = pPackage->ID();
	
    // Use the current language path (if defined) to set the language ID, 
    // for language specific file mapping.
    return SetLanguageLUT( pPackage );
}

// Unload a file package.
template <class T_LLIOHOOK_FILELOC>
AKRESULT CAkFilePackageLowLevelIO<T_LLIOHOOK_FILELOC>::UnloadFilePackage( 
	AkUInt32	in_uPackageID			// Package ID.
	)
{
	ListFilePackages::IteratorEx it = m_packages.BeginEx();
	while ( it != m_packages.End() )
	{
		if ( (*it)->ID() == in_uPackageID )
		{
			CAkFilePackage * pPackage = (*it);
			it = m_packages.Erase( it );

			// Close package file handle.
			CAkFileHelpers::CloseFile( pPackage->GetHandle() );

			pPackage->Destroy();

			return AK_Success;
		}
		else
			++it;
	}

	assert( !"Invalid package ID" );
	return AK_Fail;
}

// Unload all file packages.
template <class T_LLIOHOOK_FILELOC>
void CAkFilePackageLowLevelIO<T_LLIOHOOK_FILELOC>::UnloadAllFilePackages()
{
	ListFilePackages::IteratorEx it = m_packages.BeginEx();
	while ( it != m_packages.End() )
	{
		CAkFilePackage * pPackage = (*it);
		it = m_packages.Erase( it );

		// Close package file handle.
		CAkFileHelpers::CloseFile( pPackage->GetHandle() );

		pPackage->Destroy();
	}
}

// This method uses the language-specific directory name (obtained from policy
// T_LLIOHOOK_FILELOC::m_szLangSpecificDirName) to compute a language name, 
// then sets the current language of the given package.
// Returns AK_Success if a LanguageID is found, or if no package is loaded,
// AK_InvalidLanguage if the LanguageID is not found in the package,
// AK_Fail for any other reason.
template <class T_LLIOHOOK_FILELOC>
AKRESULT CAkFilePackageLowLevelIO<T_LLIOHOOK_FILELOC>::SetLanguageLUT(
	CAkFilePackage *	in_pPackage		// File package item.
	)
{
	const size_t numChars = wcslen( T_LLIOHOOK_FILELOC::m_szLangSpecificDirName );

    if ( numChars > 0 )
    {
        // A language specific directory is specified. Use its name to find
		// the language ID, as stored in the package file header.

		// Remove trailing slash out of the language specific directory name.
		AkOSChar * szLanguage = (AkOSChar*)AkAlloca( numChars * sizeof(AkOSChar) );
		if ( !szLanguage )
			return AK_Fail;
		
		memcpy( szLanguage, T_LLIOHOOK_FILELOC::m_szLangSpecificDirName, numChars * sizeof(AkOSChar) );
		szLanguage[numChars-1] = 0;

		return in_pPackage->lut.SetCurLanguage( szLanguage );
	}
	return in_pPackage->lut.SetCurLanguage( NULL );
}

