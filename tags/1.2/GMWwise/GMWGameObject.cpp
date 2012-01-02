#include "GMWGameObject.h"
#include <map>
#include <list>

typedef std::map<double, std::list<AkGameObjectID> >  groupsOfGameObjs;

extern "C"
{
	static groupsOfGameObjs groups;

	//----------------------------------------------------------------
	// Enregistrement d'un groupe de "game object". ------------------
	double GMWRegisterGroupGameObj(double groupID)
	{
		groupsOfGameObjs::iterator it = groups.find(groupID);
		if(it == groups.end())
		{
			groups.insert(groupsOfGameObjs::value_type(groupID, std::list<AkGameObjectID>()));
		}

		return EC_NONE;
	}

	//----------------------------------------------------------------
	// Suppression d'un groupe de "game object". ---------------------
	double GMWUnregisterGroupGameObj(double groupID)
	{
		groupsOfGameObjs::iterator it = groups.find(groupID);
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
	// Enregistrement d'un "game object". ----------------------------
	double GMWRegisterGameObj(double gameObjectID, double groupID)
	{
		if(AK::SoundEngine::RegisterGameObj(static_cast<AkGameObjectID>(gameObjectID)) != AK_Success)
		{
			std::stringstream sstr;
			sstr << "Unable to register this game object : " << gameObjectID;
			GMW_EXCEPTION(sstr.str().c_str());

			return EC_BAD_ARGS;
		}

		groupsOfGameObjs::iterator it = groups.find(groupID);
		if(it == groups.end())
		{
			std::list<AkGameObjectID> gameObjs;
			gameObjs.push_back(static_cast<AkGameObjectID>(gameObjectID));

			groups.insert(groupsOfGameObjs::value_type(groupID, gameObjs));
		}
		else
		{
			it->second.push_back(static_cast<AkGameObjectID>(gameObjectID));
		}

		return EC_NONE;
	}

	//----------------------------------------------------------------
	// Suppression d'une "game object". ------------------------------
	double GMWUnregisterGameObj(double gameObjectID, double groupID)
	{
		if(AK::SoundEngine::UnregisterGameObj(static_cast<AkGameObjectID>(gameObjectID)) != AK_Success)
		{
			std::stringstream sstr;
			sstr << "Unable to unregister this game object : " << gameObjectID;
			GMW_EXCEPTION(sstr.str().c_str());

			return EC_BAD_ARGS;
		}

		groupsOfGameObjs::iterator it = groups.find(groupID);
		if(it == groups.end())
		{
			std::stringstream sstr;
			sstr << "Bad group ID : unable to remove this game object " << gameObjectID
				 << " in this group " << groupID;
			GMW_EXCEPTION(sstr.str().c_str());

			return EC_BAD_ARGS;
		}
		else
		{
			std::list<AkGameObjectID>::iterator go_it = it->second.begin(), go_it_end = it->second.end();
			for(; go_it != go_it_end; go_it++)
			{
				if((*go_it) == gameObjectID)
				{
					it->second.erase(go_it);
					break;
				}
			}
		}

		return EC_NONE;
	}

	//----------------------------------------------------------------
	// Definie la position du "game object". -------------------------
	double GMWSet2DPosition(double gameObjectID, double pos_x, double pos_y, double dir_x, double dir_y)
	{
		return GMWSet3DPosition(gameObjectID, pos_x, pos_y, 0.f, dir_x, dir_y, 0.f);
	}

	//----------------------------------------------------------------
	// Definie la position du "game object". -------------------------
	double GMWSet3DPosition(double gameObjectID, double pos_x, double pos_y, double pos_z, double dir_x, double dir_y, double dir_z)
	{
		AkSoundPosition soundPos;
		soundPos.Position.X = static_cast<float>(pos_x);
		soundPos.Position.Z = static_cast<float>(pos_y);
		soundPos.Position.Y = static_cast<float>(pos_z);
        soundPos.Orientation.X = static_cast<float>(dir_x);
        soundPos.Orientation.Z = static_cast<float>(dir_y);
		soundPos.Orientation.Y = static_cast<float>(dir_z);

		AK::SoundEngine::SetPosition(static_cast<AkGameObjectID>(gameObjectID), soundPos);

		return EC_NONE;
	}

	//----------------------------------------------------------------
	// Envoie d'un evenements dans la pile d'evenements de wwise. ----
    double GMWPostEvent(double  eventID,  double  gameObjectID)
    {
		if(eventID < 0)
		{
			GMW_EXCEPTION("Bad event ID : ID must be higher or equal to 0");

			return EC_BAD_ARGS;
		}
		else if(gameObjectID < 0)
		{
			GMW_EXCEPTION("Bad game object ID : ID must be higher or equal to 0");

			return EC_BAD_ARGS;
		}

		AkPlayingID id = AK::SoundEngine::PostEvent(static_cast<AkUniqueID>(eventID), static_cast<AkGameObjectID>(gameObjectID));
		if(id == AK_INVALID_PLAYING_ID)
		{
			std::stringstream sstr;
			sstr << "unable to post the specified event " << eventID 
				 << " for the specified game object "     << gameObjectID;
            GMW_EXCEPTION(sstr.str().c_str());

			return EC_BAD_ARGS;
		}

		return id;
    }

	//----------------------------------------------------------------
	// Envoie d'une trigger dans la pile d'evenements. ---------------
	double GMWPostTrigger(double triggerID, double gameObjectID)
	{
		if(triggerID < 0)
		{
			GMW_EXCEPTION("Bad trigger ID : ID must be higher or equal to 0");

			return EC_BAD_ARGS;
		}
		else if(gameObjectID < 0)
		{
			GMW_EXCEPTION("Bad game object ID : ID must be higher or equal to 0");

			return EC_BAD_ARGS;
		}

		AK::SoundEngine::PostTrigger(static_cast<AkTriggerID>(triggerID), static_cast<AkGameObjectID>(gameObjectID));

		return EC_NONE;
	}

	//----------------------------------------------------------------
	// Stop tout les evenements associe au "game object". ------------
	double GMWStopAll(double gameObjectID)
	{
		AK::SoundEngine::StopAll(static_cast<AkGameObjectID>(gameObjectID));

		return EC_NONE;
	}

	//----------------------------------------------------------------
	// Definie la valeur d'un parametre de jeu. ----------------------
    double GMWSetRTPCValue(double rtpcID, double rtpcValue, double gameObjectID)
    {
        AK::SoundEngine::SetRTPCValue(static_cast<AkRtpcID>(rtpcID), static_cast<AkRtpcValue>(rtpcValue), static_cast<AkGameObjectID>(gameObjectID));

        return EC_NONE;
    }

	//----------------------------------------------------------------
	// Definie l'etat du groupe switch. ------------------------------
	double GMWSetSwitch(double switchGroup, double switchID, double gameObjectID)
	{
		if(switchGroup < 0)
		{
			GMW_EXCEPTION("Bad switch group ID : ID must be higher or equal to 0");

			return EC_BAD_ARGS;
		}

		if(switchID < 0)
		{
			GMW_EXCEPTION("Bad switch ID : ID must be higher or equal to 0");

			return EC_BAD_ARGS;
		}

		AK::SoundEngine::SetSwitch(static_cast<AkSwitchGroupID>(switchGroup), static_cast<AkSwitchStateID>(switchID), static_cast<AkGameObjectID>(gameObjectID));

		return EC_NONE;
	}
}
