//////////////////////////////////////////////////////////////////////
// 
// AkFilePackage.h
//
// This class represents a file package that was created with the 
// AkFilePackager utility app (located in ($WWISESDK)/samples/FilePackager/). 
// It holds a system file handle and a look-up table (CAkFilePackageLUT).
//
// CAkFilePackage objects can be chained together using the ListFilePackages
// typedef defined below.
// 
// Copyright (c) 2007-2008 Audiokinetic Inc. / All Rights Reserved
//
//////////////////////////////////////////////////////////////////////

#ifndef _AK_FILE_PACKAGE_H_
#define _AK_FILE_PACKAGE_H_

#include "wwise/AkFilePackageLUT.h"
#include <AK/Tools/Common/AkObject.h>
#include <AK/Tools/Common/AkListBareLight.h>

//-----------------------------------------------------------------------------
// Name: Base class for items that can be chained in AkListBareLight lists.
//-----------------------------------------------------------------------------
template<class T>
class CAkListAware
{
public:
	CAkListAware()
		: pNextItem( NULL ) {}

	struct AkListNextItem
	{
		static AkForceInline T *& Get( T * in_pItem ) 
		{
			return in_pItem->pNextItem;
		}
	};

	T * pNextItem;
};

//-----------------------------------------------------------------------------
// Name: CAkFilePackage 
// Desc: This class represents a file package. It holds a system file handle
// and a look-up table (CAkFilePackageLUT). It manages memory for the LUT and
// for itself. However, management of the file handle is left for users of this
// class: the handle would typically be created before calling Create(), and closed
// before calling Destroy() (accessed through getter GetHandle()).
//-----------------------------------------------------------------------------
class CAkFilePackage : public CAkListAware<CAkFilePackage>
{
public:
	// Factory for package LUT.
	// Creates a memory pool to contain the header of the file package and this object. 
	// Returns its address.
	static CAkFilePackage * Create( 
		const AkFileHandle &in_hFile,			// Platform-independent handle of file package.
		const AkOSChar*			in_pszPackageName,	// Name of the file package (for memory monitoring).
		AkUInt32			in_uHeaderSize,		// Size reserved for file package header.
		AkUInt32			in_uBlockAlign,		// Alignment of memory block.
		AkUInt8 *&			out_pHeaderBuffer	// Returned address of memory for header.
		);

	// Destroy file package and free memory / destroy pool.
	void Destroy();

	// Getters.
	const AkFileHandle & GetHandle() { return m_hFile; }
	AkUInt32 ID() { return m_uPackageID; }

	// Members.
	// ------------------------------
	CAkFilePackageLUT	lut;		// Package look-up table.

protected:
	AkFileHandle		m_hFile;	// Platform-independent file handle.
	AkUInt32			m_uPackageID;
	// ------------------------------

protected:
	// Private constructors: users should use Create().
	CAkFilePackage();
	CAkFilePackage(CAkFilePackage&);
	CAkFilePackage( const AkFileHandle & in_hFile, AkMemPoolId in_poolID, void * in_pToRelease )
		: m_hFile( in_hFile ) 
		, m_poolID( in_poolID )
		, m_pToRelease( in_pToRelease )
	{
		static AkUInt32 s_uPackageID = 0;
		m_uPackageID = ++s_uPackageID;
	}
	virtual ~CAkFilePackage() {}
	
	// Helper.
	static void ClearMemory(
		AkMemPoolId in_poolID,			// Pool to destroy.
		void *		in_pMemToRelease	// Memory block to free before destroying pool.
		);

protected:
	// Memory management.
	AkMemPoolId			m_poolID;		// Memory pool for LUT.
	void *				m_pToRelease;	// LUT storage (only keep this pointer to release memory).
};

//-----------------------------------------------------------------------------
// Name: ListFilePackages
// Desc: AkListBareLight of CAkFilePackage items.
//-----------------------------------------------------------------------------
typedef AkListBareLight<CAkFilePackage,CAkListAware<CAkFilePackage>::AkListNextItem> ListFilePackages;

#endif //_AK_FILE_PACKAGE_H_
