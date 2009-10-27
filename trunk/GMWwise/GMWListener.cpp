#include "GMWListener.h"

extern "C"
{
	//----------------------------------------------------------------
	// Definie la position du listener. ------------------------------
	double GMWSetListenerPosition(double pos_x, double pos_y, double o_x, double o_y)
	{
		AkListenerPosition listenerPosition;
		listenerPosition.Position.X = static_cast<float>(pos_x);
		listenerPosition.Position.Z = static_cast<float>(pos_y);
		listenerPosition.OrientationFront.X = static_cast<float>(o_x);
		listenerPosition.OrientationFront.Z = static_cast<float>(o_y);
		listenerPosition.Position.Y = listenerPosition.OrientationFront.Y = 0;

		AK::SoundEngine::SetListenerPosition(listenerPosition);

		return EC_NONE;
	}

   double GMWSetActiveListeners(double gameObjectID, double listenerID)
   {
       AK::SoundEngine::SetActiveListeners(static_cast<AkGameObjectID>(gameObjectID), static_cast<AkUInt32>(listenerID));

       return EC_NONE;
   }
}
