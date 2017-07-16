#include "GMWGameObject.h"
#include <map>
#include <list>

typedef std::map<double, std::list<AkGameObjectID> >  groupsOfGameObjs;

extern "C"
{
	static groupsOfGameObjs groups;

	// Registers a group of game objects
	double GMWRegisterGroupGameObj(double _dGroupID)
	{
		groupsOfGameObjs::iterator it = groups.find(_dGroupID);
		if(it == groups.end())
		{
			groups.insert(groupsOfGameObjs::value_type(_dGroupID, std::list<AkGameObjectID>()));
		}

		return EC_NONE;
	}

	// Unregisters a group of game objects
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

	// Registers a game object
	double GMWRegisterGameObj(double _dGameObjectID, double _dGroupID, char * _dGameObjectName)
	{
		if(AK::SoundEngine::RegisterGameObj(static_cast<AkGameObjectID>(_dGameObjectID), (const char*) _dGameObjectName) != AK_Success)
		{
			std::stringstream sstr;
			sstr << "Unable to register game object " << _dGameObjectID;
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

	//Unregisters a game object
	double GMWUnregisterGameObj(double _dGameObjectID, double _dGroupID)
	{
		if(AK::SoundEngine::UnregisterGameObj(static_cast<AkGameObjectID>(_dGameObjectID)) != AK_Success)
		{
			std::stringstream sstr;
			sstr << "Unable to unregister game object " << _dGameObjectID;
			GMW_EXCEPTION(sstr.str().c_str());

			return EC_BAD_ARGS;
		}

		groupsOfGameObjs::iterator it = groups.find(_dGroupID);
		if(it == groups.end())
		{
			std::stringstream sstr;
			sstr << "Bad group ID: unable to remove game object " << _dGameObjectID
				 << " from group " << _dGroupID;
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

	// Sets the 2D position of a game object
	double GMWSet2DPosition(double _dGameObjectID, double _dPos_x, double _dPos_y, double _dDir_x, double _dDir_y)
	{
		return GMWSet3DPosition(_dGameObjectID, _dPos_x, _dPos_y, 0.0, _dDir_x, _dDir_y, 0.0);
	}

	// Sets the 3D position of a game object
	double GMWSet3DPosition(double _dGameObjectID, double _dPos_x, double _dPos_y, double _dPos_z, double _dDir_x, double _dDir_y, double _dDir_z)
	{
		AkSoundPosition soundPos;
		soundPos.SetPosition(static_cast<float>(_dPos_x), static_cast<float>(_dPos_y), static_cast<float>(_dPos_z));
		soundPos.SetOrientation(static_cast<float>(_dDir_x), static_cast<float>(_dDir_y), static_cast<float>(_dDir_z), 0, 0, 0);

		AK::SoundEngine::SetPosition(static_cast<AkGameObjectID>(_dGameObjectID), soundPos);

		return EC_NONE;
	}

	// Posts an event from a game object
    double GMWPostEvent(double  _dEventID,  double  _dGameObjectID)
    {
		if(_dEventID < 0)
		{
			GMW_EXCEPTION("Bad event ID: ID must be higher or equal to 0");

			return EC_BAD_ARGS;
		}
		else if(_dGameObjectID < 0)
		{
			GMW_EXCEPTION("Bad game object ID: ID must be higher or equal to 0");

			return EC_BAD_ARGS;
		}

		AkPlayingID id = AK::SoundEngine::PostEvent(static_cast<AkUniqueID>(_dEventID), static_cast<AkGameObjectID>(_dGameObjectID));
		if(id == AK_INVALID_PLAYING_ID)
		{
			std::stringstream sstr;
			sstr << "unable to post event " << _dEventID 
				 << " for game object "     << _dGameObjectID;
            GMW_EXCEPTION(sstr.str().c_str());

			return EC_BAD_ARGS;
		}

		return id;
    }

	// Posts a trigger from a game object
	double GMWPostTrigger(double _dTriggerID, double _dGameObjectID)
	{
		if(_dTriggerID < 0)
		{
			GMW_EXCEPTION("Bad trigger ID: ID must be higher or equal to 0");

			return EC_BAD_ARGS;
		}
		else if(_dGameObjectID < 0)
		{
			GMW_EXCEPTION("Bad game object ID: ID must be higher or equal to 0");

			return EC_BAD_ARGS;
		}

		AK::SoundEngine::PostTrigger(static_cast<AkTriggerID>(_dTriggerID), static_cast<AkGameObjectID>(_dGameObjectID));

		return EC_NONE;
	}

	// Stops all events associated with a specific game object, or stops all sounds if no game object is specified
	double GMWStopAll(double _dGameObjectID)
	{
		AK::SoundEngine::StopAll(static_cast<AkGameObjectID>(_dGameObjectID));

		return EC_NONE;
	}

	// Sets an RTPC value for a game object
    double GMWSetRTPCValue(double _dRtpcID, double _dRtpcValue, double _dGameObjectID)
    {
        AK::SoundEngine::SetRTPCValue(static_cast<AkRtpcID>(_dRtpcID), static_cast<AkRtpcValue>(_dRtpcValue), static_cast<AkGameObjectID>(_dGameObjectID));

        return EC_NONE;
    }

	// Sets a global RTPC value
	double GMWSetGlobalRTPCValue(double rtpcID, double rtpcValue)
	{
		AK::SoundEngine::SetRTPCValue(static_cast<AkRtpcID>(rtpcID), static_cast<AkRtpcValue>(rtpcValue));
		
        return EC_NONE;
	}

	// Retrieves an RTPC value for a game object
	double GMWGetRTPCValue(double _dRtpcID, double _dGameObjectID)
	{
		AkRtpcValue value;
		AK::SoundEngine::Query::RTPCValue_type type = AK::SoundEngine::Query::RTPCValue_GameObject;

		AKRESULT result = AK::SoundEngine::Query::GetRTPCValue(static_cast<AkRtpcID>(_dRtpcID), static_cast<AkGameObjectID>(_dGameObjectID), static_cast<AkPlayingID>(0), value, type);
		if(result ==  AK_IDNotFound)
		{
			GMW_EXCEPTION("The game object was not registered or the RTPC name could not be found");
			return EC_BAD_ARGS;
		}
		else if(result == AK_Fail)
		{
			GMW_EXCEPTION("The RTPC value could not be obtained");
			return EC_RTPC;
		}

		return value;
	}

	// Sets the state of a switch group
	double GMWSetSwitch(double _dSwitchGroup, double _dSwitchID, double _dGameObjectID)
	{
		if(_dSwitchGroup < 0)
		{
			GMW_EXCEPTION("Bad switch group ID: ID must be higher or equal to 0");

			return EC_BAD_ARGS;
		}

		if(_dSwitchID < 0)
		{
			GMW_EXCEPTION("Bad switch ID: ID must be higher or equal to 0");

			return EC_BAD_ARGS;
		}

		AK::SoundEngine::SetSwitch(static_cast<AkSwitchGroupID>(_dSwitchGroup), static_cast<AkSwitchStateID>(_dSwitchID), static_cast<AkGameObjectID>(_dGameObjectID));

		return EC_NONE;
	}
}
