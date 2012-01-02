#ifndef _GMW_LISTENER_
#define _GMW_LISTENER_

#include "GMWConfig.h"

extern "C"
{
	// Definie la position du listener.
	// pos_x Position du listener sur l'axe des X.
	// pos_y Position du listener sur l'axe des Y.
	// o_x Orientation du listener sur l'axe des X.
	// o_y Orientation du listener sur l'axe des Y.
	// Renvoie toujours 0.
	GMW_API double STDCALL GMWSet2DListenerPosition(double pos_x, double pos_y, double o_x, double o_y);

	// Definie la position du listener.
	// pos_x Position du listener sur l'axe des X.
	// pos_y Position du listener sur l'axe des Y.
	// pos_z Position du listener sur l'axe des Z.
	// o_x Orientation du listener sur l'axe des X.
	// o_y Orientation du listener sur l'axe des Y.
	// o_z Orientation du listener sur l'axe des Z.
	// Renvoie toujours 0.
	GMW_API double STDCALL GMWSet3DListenerPosition(double pos_x, double pos_y, double pos_z, double o_x, double o_y, double o_z);

	// Definie les listeners actifs pour un "game object" donne.
	// gameObjectID Identifiant du "game object".
	// listener Bitmask pour activer/desactiver.
	// Renvoie toujours 0.
	//
	// exemple : 5 -> 0101 -> seulement le listener 1 et 3 sont actif 
	// avec le gameObjectID specifie.
    GMW_API double STDCALL GMWSetActiveListeners(double gameObjectID, double listenerBitmask);
}

#endif // _GMW_LISTENER_
