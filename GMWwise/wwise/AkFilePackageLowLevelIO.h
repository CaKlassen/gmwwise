//////////////////////////////////////////////////////////////////////
//
// AkFilePackageLowLevelIO.h
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

#ifndef _AK_FILE_PACKAGE_LOW_LEVEL_IO_H_
#define _AK_FILE_PACKAGE_LOW_LEVEL_IO_H_

#include "wwise/AkFilePackage.h"


//-----------------------------------------------------------------------------
// Name: class CAkFilePackageLowLevelIO.
// Desc: Extends default Low-level IO implementation with packaged file support.
//		 Base class must implement both AK::StreamMgr::IAkLowLevelIOHook and 
//		 AK::StreamMgr::IAkFileLocationResolver interfaces.
//		 It should also define the following methods and attributes:
//			- void Term()
//			- AKRESULT SetLangSpecificDirName( AkLpCtstr in_pszDirName )
//			- m_szLangSpecificDirName: the current language, plus a slash (or backslash).
// Note: This class uses AkFileDesc::uCustomParamSize to store the block size 
//		 of files opened from a package, and relies on the fact that it is 0 
//		 when they are not part of the package.
//-----------------------------------------------------------------------------
template <class T_LLIOHOOK_FILELOC>
class CAkFilePackageLowLevelIO : public T_LLIOHOOK_FILELOC
{
public:

    CAkFilePackageLowLevelIO();
    virtual ~CAkFilePackageLowLevelIO();

	// File package loading:
    // Opens a package file, parses its header, fills LUT.
    // Overrides of Open() will search files in loaded LUTs first, then use default Low-Level I/O 
	// services if they cannot be found.
	// Any number of packages can be loaded at a time. Each LUT is searched until a match is found.
	// Returns AK_Success if successful, AK_InvalidLanguage if the language was already set 
	// (with SetLangSpecificDirName()) but does not exist in the LUT, AK_Fail for any other reason.
	// Also returns a package ID which can be used to unload it (see UnloadFilePackage()).
    AKRESULT LoadFilePackage(
        AkLpCtstr   in_pszFilePackageName,	// File package name. Location is resolved using base class' Open().
		AkUInt32 &	out_uPackageID			// Returned package ID.
        );
	
	// Unload a file package.
	AKRESULT UnloadFilePackage( 
		AkUInt32	in_uPackageID			// Returned package ID.
		);

	// Unload all file packages.
    void UnloadAllFilePackages();


	//
	// Overriden base class policies.
	// ---------------------------------------------------------------

    // Clean up.
    void Term();

    // Override base class' SetLangSpecificDirName() (if defined): Need to set current language based 
	// on the language directoy name on all packages currently loaded.
	// Returns AK_InvalidLanguage if the language does not exist in the file package (if it is loaded).
    AKRESULT SetLangSpecificDirName(
        AkLpCtstr   in_pszDirName			// Language name with a trailing (back/)slash.
        );
	

protected:

	//
	// IAkFileLocationAware interface overriden methods.
	// ---------------------------------------------------------------

	// Override Open (string): Search file in each LUT first. If it cannot be found, use base class services.
	// If the file is found in the LUTs, open is always synchronous.
	// Applies to AK soundbanks only.
    virtual AKRESULT Open( 
        AkLpCtstr       in_pszFileName,     // File name.
        AkOpenMode      in_eOpenMode,       // Open mode.
        AkFileSystemFlags * in_pFlags,      // Special flags. Can pass NULL.
		bool &			io_bSyncOpen,		// If true, the file must be opened synchronously. Otherwise it is left at the File Location Resolver's discretion. Return false if Open needs to be deferred.
        AkFileDesc &    out_fileDesc        // Returned file descriptor.
        );

    // Override Open (ID): Search file in each LUT first. If it cannot be found, use base class services.
    // If the file is found in the LUTs, open is always synchronous.
	virtual AKRESULT Open( 
        AkFileID        in_fileID,          // File ID.
        AkOpenMode      in_eOpenMode,       // Open mode.
        AkFileSystemFlags * in_pFlags,      // Special flags. Can pass NULL.
		bool &			io_bSyncOpen,		// If true, the file must be opened synchronously. Otherwise it is left at the File Location Resolver's discretion. Return false if Open needs to be deferred.
        AkFileDesc &    out_fileDesc        // Returned file descriptor.
        );

    //
	// IAkLowLevelIOHook interface overriden methods.
	// ---------------------------------------------------------------

	// Override Close: Do not close handle if file descriptor is part of the current packaged file.
    virtual AKRESULT Close(
        AkFileDesc &	in_fileDesc			// File descriptor.
        );

	// Override GetBlockSize: Get the block size of the LUT if a file package is loaded.
	virtual AkUInt32 GetBlockSize(
        AkFileDesc &	in_fileDesc			// File descriptor.
        );

protected:

	// File package handling methods.
    // ------------------------------------------

    // Searches the LUT to find the file data associated with the FileID.
    // Returns AK_Success if the file is found.
    AKRESULT FindPackagedFile( 
		CAkFilePackage *	in_pPackage,	// Package to search into.
		AkFileID			in_fileID,		// File ID.
		AkFileSystemFlags * in_pFlags,		// Special flags. Can pass NULL.
		AkFileDesc &		out_fileDesc	// Returned file descriptor.
		);

    // This method uses the language-specific directory name (obtained from policy
	// T_LLIOHOOK_FILELOC::m_szLangSpecificDirName) to compute a language name, 
	// then sets the current language of the given package.
	// Returns AK_Success if a LanguageID is found, or if no package is loaded,
	// AK_InvalidLanguage if the LanguageID is not found in the package,
	// AK_Fail for any other reason.
    AKRESULT SetLanguageLUT(
		CAkFilePackage *	in_pPackage		// File package item.
		);

	// Returns true if file described by in_fileDesc is in a package.
	inline bool IsInPackage( 
		const AkFileDesc & in_fileDesc		// File descriptor.
		)
	{
		return in_fileDesc.uCustomParamSize > 0;
	}

protected:
	// List of loaded packages.
	ListFilePackages	m_packages;
};

#include "AkFilePackageLowLevelIO.inl"

#endif //_AK_FILE_PACKAGE_LOW_LEVEL_IO_H_
