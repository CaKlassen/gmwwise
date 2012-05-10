//////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006 Audiokinetic Inc. / All Rights Reserved
//
//////////////////////////////////////////////////////////////////////
#include "SoundInputMgr.h"
#include "SoundInput.h"

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
// SoundInputMgr implementation
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
SoundInputMgrBase& SoundInputMgr::Instance()
{
	static SoundInputMgr Singleton;
	return Singleton;
}

bool SoundInputMgr::Initialize()
{
	return SoundInputMgrBase::Initialize();
}

void SoundInputMgr::Term()
{
	SoundInputMgrBase::Term();
}
