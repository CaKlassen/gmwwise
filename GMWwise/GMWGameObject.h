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
#ifndef _GMW_GAME_OBJECT_
#define _GMW_GAME_OBJECT_

#include "GMWConfig.h"

extern "C"
{
	/// @brief Register a group of game object.
	/// 
	/// @param _dGroupID ID of the group.
	/// 
	/// @return 0.
	GMW_API double STDCALL GMWRegisterGroupGameObj(double _dGroupID);

	/// @brief Remove a group of game object.
	/// 
	/// @param _dGroupID ID of the group to remove.
	/// 
	/// @return 0.	
	GMW_API double STDCALL GMWUnregisterGroupGameObj(double _dGroupID);

	/// @brief Register a game object.
	/// 
	/// @param _dGameObjectID ID of the game object to register.
	/// @param _dGroupID ID of the group.
	/// 
	/// @return 0 or an error code.
	GMW_API double STDCALL GMWRegisterGameObj(double _dGameObjectID, double _dGroupID);

	/// @brief Remove a game object.
	///
	/// @param _dGameObjectID ID of the game object to remove.
	/// @param _dGroupID ID of the group.
	/// 
	/// @return 0 or an error code.
	GMW_API double STDCALL GMWUnregisterGameObj(double _dGameObjectID, double _dGroupID);

	/// @brief Set the position of the specified game object.
	///
	/// @param _dGameObjectID ID of the game object.
	/// @param _dPos_x Position on the x-axis.
	/// @param _dPos_y Position on the y-axis.
    /// @param _dDir_x Orientation on the x-axis.
    /// @param _dDir_y Orientation on the y-axis.
	/// 
	/// @return 0.
	GMW_API double STDCALL GMWSet2DPosition(double _dGameObjectID, double _dPos_x, double _dPos_y, double _dDir_x, double _dDir_y);

	/// @brief Set the position of the specified game object.
	///
	/// @param _dGameObjectID ID of the game object.
	/// @param _dPos_x Position on the x-axis.
	/// @param _dPos_y Position on the y-axis.
	/// @param _dPos_z Position on the z-axis.
	/// @param _dDir_x Orientation on the x-axis.
	/// @param _dDir_y Orientation on the y-axis.
	/// @param _dDir_z Orientation on the z-axis.
	/// 
	/// @return 0.
	GMW_API double STDCALL GMWSet3DPosition(double _dGameObjectID, double _dPos_x, double _dPos_y, double _dPos_z, double _dDir_x, double _dDir_y, double _dDir_z);

	// Envoie d'un evenements dans la pile d'evenements de wwise.
	// eventID  L'identifiant unique de l'evenement. 
	// gameObjectID Identifiant du "game object" associe a l'evenement.
	// Renvoie l'identifiant de l'evenement sinon un code d'erreur.
    GMW_API double STDCALL GMWPostEvent(double  eventID,  double  gameObjectID);

	// Envoie d'une trigger dans la pile d'evenements.
	// triggerID Identifiant unique du trigger.
	// gameObjectID Identifiant du "game object".
	// Renvoie 0 ou un code d'erreur.
	GMW_API double STDCALL GMWPostTrigger(double triggerID, double gameObjectID);

	// Stop tout les evenements associe au "game object".
	// gameObjectID Identifiant du "game object".
	// Renvoie toujours 0.
	// * si aucun "game object" specifie alors tout les evenements sont stoppe.
	GMW_API double GMWStopAll(double gameObjectID = AK_INVALID_GAME_OBJECT);

	// Definie la valeur d'un parametre de jeu.
	// rtpcID Identifiant du parametre.
	// rtpcValue Nouvelle valeur du parametre.
	// gameObjectID Identifiant du "game object" auquel le parametre est attache.
	// Renvoie toujours 0.
    GMW_API double STDCALL GMWSetRTPCValue(double rtpcID, double rtpcValue, double gameObjectID);

	// Definie l'etat du groupe switch.
	// switchGroup Identifiant du groupe switch.
	// switchID Identifiant du nouveau switch.
	// gameObjectID Identifiant du "game object" auquel le switch est attache.
	// Renvoie 0 ou un code d'erreur.
	GMW_API double STDCALL GMWSetSwitch(double switchGroup, double switchID, double gameObjectID);
}

#endif // _GMW_GAME_OBJECT_
