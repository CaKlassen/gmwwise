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
	double GMWSet2DListenerPosition(double pos_x, double pos_y, double o_x, double o_y);

	// Definie la position du listener.
	// pos_x Position du listener sur l'axe des X.
	// pos_y Position du listener sur l'axe des Y.
	// pos_z Position du listener sur l'axe des Z.
	// o_x Orientation du listener sur l'axe des X.
	// o_y Orientation du listener sur l'axe des Y.
	// o_z Orientation du listener sur l'axe des Z.
	// Renvoie toujours 0.
	double GMWSet3DListenerPosition(double pos_x, double pos_y, double pos_z, double o_x, double o_y, double o_z);

	// Definie les listeners actifs pour un "game object" donne.
	// gameObjectID Identifiant du "game object".
	// listener Bitmask pour activer/desactiver.
	// Renvoie toujours 0.
	//
	// exemple : 5 -> 0101 -> seulement le listener 1 et 3 sont actif 
	// avec le gameObjectID specifie.
	double GMWSetActiveListeners(double gameObjectID, double listenerBitmask);
}

#endif // _GMW_LISTENER_
