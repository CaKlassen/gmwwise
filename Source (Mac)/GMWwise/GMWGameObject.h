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
	double GMWRegisterGroupGameObj(double _dGroupID);

	/// @brief Remove a group of game object.
	/// 
	/// @param _dGroupID ID of the group to remove.
	/// 
	/// @return 0.	
	double GMWUnregisterGroupGameObj(double _dGroupID);

	/// @brief Register a game object.
	/// 
	/// @param _dGameObjectID ID of the game object to register.
	/// @param _dGameObjectName Name of the game object to register
	/// @param _dGroupID ID of the group.
	/// 
	/// @return 0 or an error code.
	double GMWRegisterGameObj(double _dGameObjectID, double _dGroupID, char * _dGameObjectName);

	/// @brief Remove a game object.
	///
	/// @param _dGameObjectID ID of the game object to remove.
	/// @param _dGroupID ID of the group.
	/// 
	/// @return 0 or an error code.
	double GMWUnregisterGameObj(double _dGameObjectID, double _dGroupID);

	/// @brief Set the position of the specified game object.
	///
	/// @param _dGameObjectID ID of the game object.
	/// @param _dPos_x Position on the x-axis.
	/// @param _dPos_y Position on the y-axis.
    /// @param _dDir_x Orientation on the x-axis.
    /// @param _dDir_y Orientation on the y-axis.
	/// 
	/// @return 0.
	double GMWSet2DPosition(double _dGameObjectID, double _dPos_x, double _dPos_y, double _dDir_x, double _dDir_y);

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
	double GMWSet3DPosition(double _dGameObjectID, double _dPos_x, double _dPos_y, double _dPos_z, double _dDir_x, double _dDir_y, double _dDir_z);

	/// @brief Post an event to the sound engine by ID.
	///
	/// @param _dEventID  Unique ID of the event.
	/// @param _dGameObjectID Associated game object ID.
	/// 
	/// @return The playing ID of the event launched or an error code.
    double GMWPostEvent(double  _dEventID,  double  _dGameObjectID);

	/// @brief Post the specified trigger by ID.
	/// 
	/// @param _dTriggerID ID of the trigger.
	/// @param _dGameObjectID Associated game object ID .
	///
	/// @return 0 or an error code.
	double GMWPostTrigger(double _dTriggerID, double _dGameObjectID);

	/// @brief Stop the current content playing associated to the specified game object ID. If no game object is specified, all sounds will be stopped.
	///
	/// @param _dGameObjectID (Optional)Specify a game object to stop only playback associated to the provided game object ID. 
	///
	/// @return 0.
	double GMWStopAll(double _dGameObjectID = AK_INVALID_GAME_OBJECT);

	/// @brief Set the value of the real-time parameter control by ID.
	///
	/// @param _dRtpcID ID of the game parameter.
	/// @param _dRtpcValue Value to set.
	/// @param _dGameObjectID Associated game object ID.
	///
	/// @return 0.
    double GMWSetRTPCValue(double _dRtpcID, double _dRtpcValue, double _dGameObjectID);
	
	/// @brief Set the value of the global real-time parameter control by ID.
	///
	/// @param _dRtpcID ID of the game parameter.
	/// @param _dRtpcValue Value to set.
	///
	/// @return 0.
	double GMWSetGlobalRTPCValue(double rtpcID, double rtpcValue);

	/// @brief Retrieves RTPC value.
	/// 
	/// @param _dRtpcID ID of the RTPC.
	/// @param _dGameObjectID Associated game object ID.
	/// 
	/// @return The RTPC value.
	double GMWGetRTPCValue(double _dRtpcID, double _dGameObjectID);

	/// @brief Set the state of a switch group by ID.
	///
	/// @param _dSwitchGroup ID of the switch group.
	/// @param _dSwitchID ID of the switch group.
	/// @param _dGameObjectID Associated game object ID.
	///
	/// @return 0 or an error code.
	double GMWSetSwitch(double _dSwitchGroup, double _dSwitchID, double _dGameObjectID);
}

#endif // _GMW_GAME_OBJECT_
