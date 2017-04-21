#ifndef _GMW_GAME_OBJECT_
#define _GMW_GAME_OBJECT_

#include "GMWConfig.h"

extern "C"
{
	///<summary>Registers a group of game objects</summary>
	///<param name="_dGroupID">the ID of the group</param>
	///<returns>0</returns>
	GMW_API double STDCALL GMWRegisterGroupGameObj(double _dGroupID);
	
	///<summary>Removes a group of game objects</summary>
	///<param name="_dGroupID">the ID of the group</param>
	///<returns>0</returns>
	GMW_API double STDCALL GMWUnregisterGroupGameObj(double _dGroupID);
	
	///<summary>Registers a game object</summary>
	///<param name="_dGameObjectID">the ID of the game object</param>
	///<param name="_dGroupID">the ID of the group to add to</param>
	///<param name="_dGameObjectName">the name of the game object</param>
	///<returns>0 or an error code</returns>
	GMW_API double STDCALL GMWRegisterGameObj(double _dGameObjectID, double _dGroupID, char * _dGameObjectName);
	
	///<summary>Unregisters a game object</summary>
	///<param name="_dGameObjectID">the game object ID</param>
	///<param name="_dGroupID">the group ID to remove from</param>
	///<returns>0 or an error code</returns>
	GMW_API double STDCALL GMWUnregisterGameObj(double _dGameObjectID, double _dGroupID);
	
	///<summary>Sets the 2D position of a specified game object</summary>
	///<param name="_dGameObjectID">the ID of the game object</param>
	///<param name="_dPos_x">the x position</param>
	///<param name="_dPos_y">the y position</param>
	///<param name="_dDir_x">the x orientation</param>
	///<param name="_dDir_y">the y orientation</param>
	///<returns>0</returns>
	GMW_API double STDCALL GMWSet2DPosition(double _dGameObjectID, double _dPos_x, double _dPos_y, double _dDir_x, double _dDir_y);
	
	///<summary>Sets the 3D position of a specified game object</summary>
	///<param name="_dGameObjectID">the ID of the game object</param>
	///<param name="_dPos_x">the x position</param>
	///<param name="_dPos_y">the y position</param>
	///<param name="_dPos_z">the z position</param>
	///<param name="_dDir_x">the x orientation</param>
	///<param name="_dDir_y">the y orientation</param>
	///<param name="_dDir_z">the z orientation</param>
	///<returns>0</returns>
	GMW_API double STDCALL GMWSet3DPosition(double _dGameObjectID, double _dPos_x, double _dPos_y, double _dPos_z, double _dDir_x, double _dDir_y, double _dDir_z);
	
	///<summary>Posts an event</summary>
	///<param name="_dEventID">the event ID</param>
	///<param name="_dGameObjectID">the ID of the game object to post from</param>
	///<returns>The playing ID of the posted event, or an error code</returns>
	GMW_API double STDCALL GMWPostEvent(double  _dEventID,  double  _dGameObjectID);
	
	///<summary>Posts a trigger</summary>
	///<param name="_dTriggerID">the trigger ID</param>
	///<param name="_dGameObjectID">the ID of the game object to post from</param>
	///<returns>0 or an error code</returns>
	GMW_API double STDCALL GMWPostTrigger(double _dTriggerID, double _dGameObjectID);
	
	///<summary>Stops all playing content associated with a specific game object. If no game object is specified, all sounds will be stopped</summary>
	///<param name="_dGameObjectID">the ID of the game object, or nothing</param>
	///<returns>0</returns>
	GMW_API double GMWStopAll(double _dGameObjectID = AK_INVALID_GAME_OBJECT);
	
	///<summary>Sets an RTPC value for a specific game object</summary>
	///<param name="_dRtpcID">the RTPC ID</param>
	///<param name="_dRtpcValue">the RTPC value</param>
	///<param name="_dGameObjectID">the ID of the game object to change the RTPC for</param>
	///<returns>0</returns>
	GMW_API double STDCALL GMWSetRTPCValue(double _dRtpcID, double _dRtpcValue, double _dGameObjectID);
	
	///<summary>Sets a global RTPC value</summary>
	///<param name="rtpcID">the RTPC ID</param>
	///<param name="rtpcValue">the RTPC value</param>
	///<returns>0</returns>
	GMW_API double STDCALL GMWSetGlobalRTPCValue(double rtpcID, double rtpcValue);
	
	///<summary>Retrieves an RTPC value</summary>
	///<param name="_dRtpcID">the RTPC ID</param>
	///<param name="_dGameObjectID">the game object to retrieve the RTPC value from</param>
	///<returns>the RTPC value</returns>
	GMW_API double STDCALL GMWGetRTPCValue(double _dRtpcID, double _dGameObjectID);
	
	///<summary>Sets the state of a switch group</summary>
	///<param name="_dSwitchGroup">the ID of the switch group</param>
	///<param name="_dSwitchID">the ID of the switch</param>
	///<param name="_dGameObjectID">the ID of the game object to set the switch state for</param>
	///<returns>0 or an error code</returns>
	GMW_API double STDCALL GMWSetSwitch(double _dSwitchGroup, double _dSwitchID, double _dGameObjectID);
}

#endif // _GMW_GAME_OBJECT_
