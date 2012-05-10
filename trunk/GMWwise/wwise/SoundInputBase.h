//////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006 Audiokinetic Inc. / All Rights Reserved
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include <AK/SoundEngine/Common/AkTypes.h>

// Forward definition
struct AkAudioFormat;
class AkAudioBuffer;

class SoundInputBase
{
public:
	
	virtual bool InputOn( unsigned int in_DevNumber = 0 )  = 0;		// Start input recording
	virtual bool InputOff() = 0;									// Stop input recording

	// For callback purpose.
	virtual void Execute( AkAudioBuffer* io_pBufferOut ) = 0;
	virtual void GetFormatCallback( AkAudioFormat& io_AudioFormat ) = 0;

	void SetPlayingID( AkPlayingID in_playingID );
	AkPlayingID GetPlayingID();

protected:
	SoundInputBase();
    virtual ~SoundInputBase();

private:
	AkPlayingID m_playingID;
};
