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

#include "wwise/AkFilePackage.h"

//-----------------------------------------------------------------------------
// Name: CAkFilePackage 
// Desc: This class represents a file package. It holds a system file handle
// and a look-up table (CAkFilePackageLUT). It manages memory for the LUT and
// for itself. However, management of the file handle is left for users of this
// class: the handle would typically be created before calling Create(), and closed
// before calling Destroy() (accessed through getter GetHandle()).
//-----------------------------------------------------------------------------

// Creates a memory pool to contain the header of the file package. Returns its address.
CAkFilePackage * CAkFilePackage::Create( 
	const AkFileHandle &in_hFile,			// Platform-independent handle of file package.
	AkLpCtstr			
#ifndef AK_OPTIMIZED
		in_pszPackageName
#endif
		,	// Name of the file package (for memory monitoring).
	AkUInt32			in_uHeaderSize,		// Size reserved for file package header.
	AkUInt32			in_uBlockAlign,		// Alignment of memory block.
	AkUInt8 *&			out_pHeaderBuffer	// Returned address of memory for header.
	)
{
	AKASSERT( in_uHeaderSize > 0 );
	
	// Create memory pool and copy header.
	// The pool must be big enough to hold both the buffer for the LUT's header
	// and a CAkFilePackage object.
	AkUInt32 uMemSize = in_uHeaderSize + sizeof( CAkFilePackage );
	AkMemPoolId poolID = AK::MemoryMgr::CreatePool( NULL, uMemSize, uMemSize, AkMalloc | AkFixedSizeBlocksMode, in_uBlockAlign );
	if ( poolID == AK_INVALID_POOL_ID )
		return NULL;
	AK_SETPOOLNAME( poolID, in_pszPackageName );

	AkUInt8 * pToRelease = (AkUInt8*)AK::MemoryMgr::GetBlock( poolID );
	
	// Construct a CAkFilePackage at the end of this memory region.
	CAkFilePackage * pFilePackage = AkPlacementNew( pToRelease + in_uHeaderSize ) CAkFilePackage( in_hFile, poolID, pToRelease );
	assert( pFilePackage );	// Must succeed.

	out_pHeaderBuffer = pToRelease;

	return pFilePackage;
}

// Destroy file package and free memory / destroy pool.
void CAkFilePackage::Destroy()
{
	// Cache memory pointer and pool ID because memory pool is destroyed _after_ deleting this.
	AkMemPoolId	poolID	= m_poolID;
	void * pToRelease	= m_pToRelease;

	// Call destructor.
	this->~CAkFilePackage();

	// Free memory.
	ClearMemory( poolID, pToRelease );
}

void CAkFilePackage::ClearMemory(
	AkMemPoolId in_poolID,			// Pool to destroy.
	void *		in_pMemToRelease	// Memory block to free before destroying pool.
	)
{
	if ( in_poolID != AK_INVALID_POOL_ID )
	{
		if ( in_pMemToRelease )
		{
			AK::MemoryMgr::ReleaseBlock( in_poolID, in_pMemToRelease );
		}
		AKVERIFY( AK::MemoryMgr::DestroyPool( in_poolID ) == AK_Success );
	}
}
