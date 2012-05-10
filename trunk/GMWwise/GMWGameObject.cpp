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
#include "GMWGameObject.h"
#include <map>
#include <list>

typedef std::map<double, std::list<AkGameObjectID> >  groupsOfGameObjs;

extern "C"
{
	static groupsOfGameObjs groups;

	//----------------------------------------------------------------
	// Register a group of game object. ------------------------------
	double GMWRegisterGroupGameObj(double _dGroupID)
	{
		groupsOfGameObjs::iterator it = groups.find(_dGroupID);
		if(it == groups.end())
		{
			groups.insert(groupsOfGameObjs::value_type(_dGroupID, std::list<AkGameObjectID>()));
		}

		return EC_NONE;
	}

	//----------------------------------------------------------------
	// Remove a group of game object. --------------------------------
	double GMWUnregisterGroupGameObj(double _dGroupID)
	{
		groupsOfGameObjs::iterator it = groups.find(_dGroupID);
		if(it != groups.end())
		{
			std::list<AkGameObjectID>::iterator go_it = it->second.begin(), go_it_end = it->second.end();
			for(; go_it != go_it_end; go_it++)
			{
				AK::SoundEngine::UnregisterGameObj(static_cast<AkGameObjectID>((*go_it)));
			}
		}

		return EC_NONE;
	}

	//----------------------------------------------------------------
	// Register a game object. ---------------------------------------
	double GMWRegisterGameObj(double _dGameObjectID, double _dGroupID)
	{
		if(AK::SoundEngine::RegisterGameObj(static_cast<AkGameObjectID>(_dGameObjectID)) != AK_Success)
		{
			std::stringstream sstr;
			sstr << "Unable to register this game object : " << _dGameObjectID;
			GMW_EXCEPTION(sstr.str().c_str());

			return EC_BAD_ARGS;
		}

		groupsOfGameObjs::iterator it = groups.find(_dGroupID);
		if(it == groups.end())
		{
			std::list<AkGameObjectID> gameObjs;
			gameObjs.push_back(static_cast<AkGameObjectID>(_dGameObjectID));

			groups.insert(groupsOfGameObjs::value_type(_dGroupID, gameObjs));
		}
		else
		{
			it->second.push_back(static_cast<AkGameObjectID>(_dGameObjectID));
		}

		return EC_NONE;
	}

	//----------------------------------------------------------------
	// Remove a game object. -----------------------------------------
	double GMWUnregisterGameObj(double _dGameObjectID, double _dGroupID)
	{
		if(AK::SoundEngine::UnregisterGameObj(static_cast<AkGameObjectID>(_dGameObjectID)) != AK_Success)
		{
			std::stringstream sstr;
			sstr << "Unable to unregister this game object : " << _dGameObjectID;
			GMW_EXCEPTION(sstr.str().c_str());

			return EC_BAD_ARGS;
		}

		groupsOfGameObjs::iterator it = groups.find(_dGroupID);
		if(it == groups.end())
		{
			std::stringstream sstr;
			sstr << "Bad group ID : unable to remove this game object " << _dGameObjectID
				 << " in this group " << _dGroupID;
			GMW_EXCEPTION(sstr.str().c_str());

			return EC_BAD_ARGS;
		}
		else
		{
			std::list<AkGameObjectID>::iterator go_it = it->second.begin(), go_it_end = it->second.end();
			for(; go_it != go_it_end; go_it++)
			{
				if((*go_it) == _dGameObjectID)
				{
					it->second.erase(go_it);
					break;
				}
			}
		}

		return EC_NONE;
	}

	//----------------------------------------------------------------
	// Set the position of the specified game object. ----------------
	double GMWSet2DPosition(double _dGameObjectID, double _dPos_x, double _dPos_y, double _dDir_x, double _dDir_y)
	{
		return GMWSet3DPosition(_dGameObjectID, _dPos_x, _dPos_y, 0.0, _dDir_x, _dDir_y, 0.0);
	}

	//----------------------------------------------------------------
	// Set the position of the specified game object. ----------------
	double GMWSet3DPosition(double _dGameObjectID, double _dPos_x, double _dPos_y, double _dPos_z, double _dDir_x, double _dDir_y, double _dDir_z)
	{
		AkSoundPosition soundPos;
		soundPos.Position.X = static_cast<float>(_dPos_x);
		soundPos.Position.Z = static_cast<float>(_dPos_y);
		soundPos.Position.Y = static_cast<float>(_dPos_z);
        soundPos.Orientation.X = static_cast<float>(_dDir_x);
        soundPos.Orientation.Z = static_cast<float>(_dDir_y);
		soundPos.Orientation.Y = static_cast<float>(_dDir_z);

		AK::SoundEngine::SetPosition(static_cast<AkGameObjectID>(_dGameObjectID), soundPos);

		return EC_NONE;
	}

	//----------------------------------------------------------------
	// Post an event to the sound engine by ID. ----------------------
    double GMWPostEvent(double  _dEventID,  double  _dGameObjectID)
    {
		if(_dEventID < 0)
		{
			GMW_EXCEPTION("Bad event ID : ID must be higher or equal to 0");

			return EC_BAD_ARGS;
		}
		else if(_dGameObjectID < 0)
		{
			GMW_EXCEPTION("Bad game object ID : ID must be higher or equal to 0");

			return EC_BAD_ARGS;
		}

		AkPlayingID id = AK::SoundEngine::PostEvent(static_cast<AkUniqueID>(_dEventID), static_cast<AkGameObjectID>(_dGameObjectID));
		if(id == AK_INVALID_PLAYING_ID)
		{
			std::stringstream sstr;
			sstr << "unable to post the specified event " << _dEventID 
				 << " for the specified game object "     << _dGameObjectID;
            GMW_EXCEPTION(sstr.str().c_str());

			return EC_BAD_ARGS;
		}

		return id;
    }

	//----------------------------------------------------------------
	// Post the specified trigger by ID. -----------------------------
	double GMWPostTrigger(double _dTriggerID, double _dGameObjectID)
	{
		if(_dTriggerID < 0)
		{
			GMW_EXCEPTION("Bad trigger ID : ID must be higher or equal to 0");

			return EC_BAD_ARGS;
		}
		else if(_dGameObjectID < 0)
		{
			GMW_EXCEPTION("Bad game object ID : ID must be higher or equal to 0");

			return EC_BAD_ARGS;
		}

		AK::SoundEngine::PostTrigger(static_cast<AkTriggerID>(_dTriggerID), static_cast<AkGameObjectID>(_dGameObjectID));

		return EC_NONE;
	}

	//----------------------------------------------------------------
	// Stop the current content playing associated to the specified 
	// game object ID. If no game object is specified, all sounds will 
	// be stopped ----------------------------------------------------
	double GMWStopAll(double _dGameObjectID)
	{
		AK::SoundEngine::StopAll(static_cast<AkGameObjectID>(_dGameObjectID));

		return EC_NONE;
	}

	//----------------------------------------------------------------
	// Set the value of the real-time parameter control by ID. -------
    double GMWSetRTPCValue(double _dRtpcID, double _dRtpcValue, double _dGameObjectID)
    {
        AK::SoundEngine::SetRTPCValue(static_cast<AkRtpcID>(_dRtpcID), static_cast<AkRtpcValue>(_dRtpcValue), static_cast<AkGameObjectID>(_dGameObjectID));

        return EC_NONE;
    }

	//----------------------------------------------------------------
	// Retrieves RTPC value. -----------------------------------------
	double GMWGetRTPCValue(double _dRtpcID, double _dGameObjectID)
	{
		AkRtpcValue value;
		AK::SoundEngine::Query::RTPCValue_type type = AK::SoundEngine::Query::RTPCValue_GameObject;
		AK::SoundEngine::Query::GetRTPCValue(static_cast<AkRtpcID>(_dRtpcID), static_cast<AkGameObjectID>(_dGameObjectID), value, type);

		return value;
	}

	//----------------------------------------------------------------
	// Set the state of a switch group by ID. ------------------------
	double GMWSetSwitch(double _dSwitchGroup, double _dSwitchID, double _dGameObjectID)
	{
		if(_dSwitchGroup < 0)
		{
			GMW_EXCEPTION("Bad switch group ID : ID must be higher or equal to 0");

			return EC_BAD_ARGS;
		}

		if(_dSwitchID < 0)
		{
			GMW_EXCEPTION("Bad switch ID : ID must be higher or equal to 0");

			return EC_BAD_ARGS;
		}

		AK::SoundEngine::SetSwitch(static_cast<AkSwitchGroupID>(_dSwitchGroup), static_cast<AkSwitchStateID>(_dSwitchID), static_cast<AkGameObjectID>(_dGameObjectID));

		return EC_NONE;
	}
}
