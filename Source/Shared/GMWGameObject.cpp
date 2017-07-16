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

		return 0;
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
				auto result = AK::SoundEngine::UnregisterGameObj(static_cast<AkGameObjectID>((*go_it)));
				if (result != AK_Success)
				{
					errorCode = result;
					return -1;
				}
			}
		}

		return 0;
	}

	// Registers a game object
	double GMWRegisterGameObj(double _dGameObjectID, double _dGroupID, char * _dGameObjectName)
	{
		auto result = AK::SoundEngine::RegisterGameObj(static_cast<AkGameObjectID>(_dGameObjectID), (const char*)_dGameObjectName);
		if(result != AK_Success)
		{
			errorCode = result;
			return -1;
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

		return 0;
	}

	//Unregisters a game object
	double GMWUnregisterGameObj(double _dGameObjectID, double _dGroupID)
	{
		auto result = AK::SoundEngine::UnregisterGameObj(static_cast<AkGameObjectID>(_dGameObjectID));
		if(result != AK_Success)
		{
			errorCode = result;
			return -1;
		}

		groupsOfGameObjs::iterator it = groups.find(_dGroupID);
		if(it == groups.end())
		{
			errorCode = AK_InvalidID;
			return -1;
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

		return 0;
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

		auto result = AK::SoundEngine::SetPosition(static_cast<AkGameObjectID>(_dGameObjectID), soundPos);
		if (result != AK_Success)
		{
			errorCode = result;
			return -1;
		}

		return 0;
	}

	// Posts an event from a game object
    double GMWPostEvent(double  _dEventID,  double  _dGameObjectID)
    {
		AkPlayingID id = AK::SoundEngine::PostEvent(static_cast<AkUniqueID>(_dEventID), static_cast<AkGameObjectID>(_dGameObjectID));
		if(id == AK_INVALID_PLAYING_ID)
		{
			errorCode = AK_Fail;
			return -1;
		}

		return id;
    }

	// Posts a trigger from a game object
	double GMWPostTrigger(double _dTriggerID, double _dGameObjectID)
	{
		auto result = AK::SoundEngine::PostTrigger(static_cast<AkTriggerID>(_dTriggerID), static_cast<AkGameObjectID>(_dGameObjectID));
		if (result != AK_Success)
		{
			errorCode = result;
			return -1;
		}

		return 0;
	}

	// Stops all events associated with a specific game object, or stops all sounds if no game object is specified
	double GMWStopAll(double _dGameObjectID)
	{
		AK::SoundEngine::StopAll(static_cast<AkGameObjectID>(_dGameObjectID));

		return 0;
	}

	// Sets an RTPC value for a game object
    double GMWSetRTPCValue(double _dRtpcID, double _dRtpcValue, double _dGameObjectID)
    {
        auto result = AK::SoundEngine::SetRTPCValue(static_cast<AkRtpcID>(_dRtpcID), static_cast<AkRtpcValue>(_dRtpcValue), static_cast<AkGameObjectID>(_dGameObjectID));
		if (result != AK_Success)
		{
			errorCode = result;
			return -1;
		}

        return 0;
    }

	// Sets a global RTPC value
	double GMWSetGlobalRTPCValue(double rtpcID, double rtpcValue)
	{
		auto result = AK::SoundEngine::SetRTPCValue(static_cast<AkRtpcID>(rtpcID), static_cast<AkRtpcValue>(rtpcValue));
		if (result != AK_Success)
		{
			errorCode = result;
			return -1;
		}

        return 0;
	}

	// Retrieves an RTPC value for a game object
	double GMWGetRTPCValue(double _dRtpcID, double _dGameObjectID)
	{
		AkRtpcValue value;
		AK::SoundEngine::Query::RTPCValue_type type = AK::SoundEngine::Query::RTPCValue_GameObject;

		AK::SoundEngine::Query::GetRTPCValue(static_cast<AkRtpcID>(_dRtpcID), static_cast<AkGameObjectID>(_dGameObjectID), static_cast<AkPlayingID>(0), value, type);

		return value;
	}

	// Sets the state of a switch group
	double GMWSetSwitch(double _dSwitchGroup, double _dSwitchID, double _dGameObjectID)
	{
		auto result = AK::SoundEngine::SetSwitch(static_cast<AkSwitchGroupID>(_dSwitchGroup), static_cast<AkSwitchStateID>(_dSwitchID), static_cast<AkGameObjectID>(_dGameObjectID));
		if (result != AK_Success)
		{
			errorCode = result;
			return -1;
		}

		return 0;
	}
}
