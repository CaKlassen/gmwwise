#include "GMWListener.h"

extern "C"
{
	// Sets the position of the listener in 2D space
	GMW_API double GMWSet2DListenerPosition(double pos_x, double pos_y, double o_x, double o_y)
	{
		return GMWSet3DListenerPosition(pos_x, pos_y, 0.f, o_x, o_y, 0.f);
	}

	// Sets the position of the listener in 3D space
	GMW_API double GMWSet3DListenerPosition(double pos_x, double pos_y, double pos_z, double o_x, double o_y, double o_z)
	{
		AkListenerPosition listenerPosition;
		listenerPosition.SetPosition(static_cast<float>(pos_x), static_cast<float>(pos_y), static_cast<float>(pos_z));
		listenerPosition.SetOrientation(static_cast<float>(o_x), static_cast<float>(o_y), static_cast<float>(o_z), 0, 0, 0);

		AK::SoundEngine::SetListenerPosition(listenerPosition);

		return EC_NONE;
	}

	// Sets the active listeners for a game object using a bitmask
	GMW_API double GMWSetActiveListeners(double gameObjectID, double listenerID)
	{
	   AK::SoundEngine::SetActiveListeners(static_cast<AkGameObjectID>(gameObjectID), static_cast<AkUInt32>(listenerID));

	   return EC_NONE;
	}
}
