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

		groupsOfGameObjs::iterator it = groups.find(groupID);
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
	// Suppression d'une "game object". ------------------------------
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
