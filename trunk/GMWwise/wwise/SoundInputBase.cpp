//////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006 Audiokinetic Inc. / All Rights Reserved
//
//////////////////////////////////////////////////////////////////////
#include "SoundInputBase.h"

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
// SoundInputBase implementation
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
SoundInputBase::SoundInputBase()
	:m_playingID(AK_INVALID_PLAYING_ID)
{
}

SoundInputBase::~SoundInputBase() 
{
}

void SoundInputBase::SetPlayingID( AkPlayingID in_playingID )
{
	m_playingID = in_playingID;
}

AkPlayingID SoundInputBase::GetPlayingID()
{
	return m_playingID;
}
