//////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006 Audiokinetic Inc. / All Rights Reserved
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include "SoundInputBase.h"

#define MAX_NUM_SOUNDINPUT	4

// Forward definitions.
class SoundInput;
struct AkAudioFormat;
class AkAudioBuffer;


class SoundInputMgrBase
{
public:
	SoundInputMgrBase() {m_MicCount = 0;}
	struct RegisteredDevice
	{
		SoundInputBase* pInput;
		AkUInt32 idDevice;
	};

	virtual bool Initialize();
	virtual void Term();

	virtual AkUInt32 GetMicCount() {return m_MicCount;}
	virtual AkUInt32 GetMicDeviceID(AkUInt32 in_index) {return m_registeredDevices[in_index].idDevice;}

protected:
	virtual ~SoundInputMgrBase() {}

	// Callbacks that will be passed to Wwise.
	static void GetFormatCallback(
        AkPlayingID		/*in_playingID*/,   // Playing ID
        AkAudioFormat&  /*io_AudioFormat*/  // Already filled format, modify it if required.
	    );

	static void ExecuteCallback(
        AkPlayingID		in_playingID,  // Playing ID
        AkAudioBuffer*	io_pBufferOut  // Buffer to fill
	    );

	void Reset();
	SoundInputBase* GetInput( AkPlayingID in_playingID );

	RegisteredDevice m_registeredDevices[MAX_NUM_SOUNDINPUT];
	AkUInt32 m_MicCount;

private: // Only SoundInput are allowed to call Register and Unregister private functions
	friend class SoundInput;
	bool RegisterDevice( SoundInputBase* in_pSoundInput );
	void UnregisterDevice( SoundInputBase* in_pSoundInput );
};
