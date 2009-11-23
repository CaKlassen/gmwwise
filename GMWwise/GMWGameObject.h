#ifndef _GMW_GAME_OBJECT_
#define _GMW_GAME_OBJECT_

#include "GMWConfig.h"

extern "C"
{
	// Enregistrement d'un groupe de "game object".
	// groupID Identifiant du groupe  de "game object".
	// Renvoie toujours 0.
	GMW_API double GMWRegisterGroupGameObj(double groupID);

	// Suppression d'un groupe de "game object".
	// groupID Identifiant du groupe de "game object".
	// Renvoie toujours 0.
	GMW_API double GMWUnregisterGroupGameObj(double groupID);

	// Enregistrement d'un "game object".
	// gameObjectID Identifiant du "game object".
	// groupID Identifiant du groupe de "game object".
	// Renvoie 0 sinon une code d'erreur.
	GMW_API double GMWRegisterGameObj(double gameObjectID, double groupID);

	// Suppression d'une "game object".
	// gameObjectID Identifiant du "game object".
	// groupID Identifiant du groupe de "game object".
	// Renvoie 0 sinon un code d'erreur.
	GMW_API double GMWUnregisterGameObj(double gameObjectID, double groupID);

	// Definie la position du "game object".
	// gameObjectID Identifiant du "game object".
	// pos_x Position sur l'axe des X.
	// pos_y Position sur l'axe des Y.
    // dir_x Direction sur l'axe des X.
    // dir_y Direction sur l'axe des Y.
	// Renvoie toujours 0.
	GMW_API double GMWSet2DPosition(double gameObjectID, double pos_x, double pos_y, double dir_x, double dir_y);

	// Definie la position du "game object".
	// gameObjectID Identifiant du "game object".
	// pos_x Position sur l'axe des X.
	// pos_y Position sur l'axe des Y.
	// pos_z Position sur l'axe des Z.
    // dir_x Direction sur l'axe des X.
    // dir_y Direction sur l'axe des Y.
	// dir_z Direction sur l'axe des Z.
	// Renvoie toujours 0.
	GMW_API double GMWSet3DPosition(double gameObjectID, double pos_x, double pos_y, double pos_z, double dir_x, double dir_y, double dir_z);

	// Envoie d'un evenements dans la pile d'evenements de wwise.
	// eventID  L'identifiant unique de l'evenement. 
	// gameObjectID Identifiant du "game object" associe a l'evenement.
	// Renvoie l'identifiant de l'evenement sinon un code d'erreur.
    GMW_API double GMWPostEvent(double  eventID,  double  gameObjectID);

	// Envoie d'une trigger dans la pile d'evenements.
	// triggerID Identifiant unique du trigger.
	// gameObjectID Identifiant du "game object".
	// Renvoie 0 ou un code d'erreur.
	GMW_API double GMWPostTrigger(double triggerID, double gameObjectID);

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
    GMW_API double GMWSetRTPCValue(double rtpcID, double rtpcValue, double gameObjectID);

	// Definie l'etat du groupe switch.
	// switchGroup Identifiant du groupe switch.
	// switchID Identifiant du nouveau switch.
	// gameObjectID Identifiant du "game object" auquel le switch est attache.
	// Renvoie 0 ou un code d'erreur.
	GMW_API double GMWSetSwitch(double switchGroup, double switchID, double gameObjectID);
}

#endif // _GMW_GAME_OBJECT_
