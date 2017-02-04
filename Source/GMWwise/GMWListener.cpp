/*
Author : cédric liaudet
URL    : http://code.google.com/p/gmwwise/

=================================================================================
This library is free software; you can redistribute it and/or modify 
it under the terms of the GNU Lesser General Public License as published
by the Free Software Foundation; either version 2.1 of the License, or (at your option) any later version. 
This library is distributed in the hope that it will be useful, but without any warranty; 
without even the implied warranty of merchantability or fitness for a particular purpose. 
See the GNU Lesser General Public License for more details.
=================================================================================
*/
#include "GMWListener.h"

extern "C"
{
	//----------------------------------------------------------------
	// Definie la position du listener. ------------------------------
	double GMWSet2DListenerPosition(double pos_x, double pos_y, double o_x, double o_y)
	{
		return GMWSet3DListenerPosition(pos_x, pos_y, 0.f, o_x, o_y, 0.f);
	}

	//----------------------------------------------------------------
	// Definie la position du listener. ------------------------------
	double GMWSet3DListenerPosition(double pos_x, double pos_y, double pos_z, double o_x, double o_y, double o_z)
	{
		AkListenerPosition listenerPosition;
		listenerPosition.SetPosition(pos_x, pos_y, pos_z);
		listenerPosition.SetOrientation(o_x, o_y, o_z, 0, 0, 0);

		AK::SoundEngine::SetListenerPosition(listenerPosition);

		return EC_NONE;
	}

   double GMWSetActiveListeners(double gameObjectID, double listenerID)
   {
       AK::SoundEngine::SetActiveListeners(static_cast<AkGameObjectID>(gameObjectID), static_cast<AkUInt32>(listenerID));

       return EC_NONE;
   }
}
