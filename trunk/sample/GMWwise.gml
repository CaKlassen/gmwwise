#define LoadGMWwise
////////////////////////////////////////////////////////
// Initialisation de la dll de GMWwise.
// A appeler une fois au debut de la creation du jeu.
////////////////////////////////////////////////////////
dll_name = 'GMWwise.dll';
if(global.GMW_PROFILE == true)
{
    dll_name = 'GMWwise_profile.dll';
}

if !file_exists(dll_name)
{
    show_message('File not found: '+dll_name+'#In directory : ' + working_directory);
}


// Base du moteur son.
global.dll_GMWInit=external_define(dll_name, "GMWInit", dll_cdecl, ty_real, 0);

global.dll_GMWShutdown=external_define(dll_name, "GMWShutdown", dll_cdecl, ty_real, 0);

global.dll_GMWProcessAudio=external_define(dll_name, "GMWProcessAudio", dll_cdecl, ty_real, 0);

global.dll_GMWSetState=external_define(dll_name, "GMWSetState", dll_cdecl, ty_real, 2, ty_real, ty_real);

global.dll_GMWRegisterPlugin=external_define(dll_name, "GMWRegisterPlugin", dll_cdecl, ty_real, 1, ty_real);

global.dll_GMWRegisterCodec=external_define(dll_name, "GMWRegisterCodec", dll_cdecl, ty_real, 1, ty_real);


// Bank
global.dll_GMWSetBasePath=external_define(dll_name, "GMWSetBasePath", dll_cdecl, ty_real, 1, ty_string);

global.dll_GMWSetLangSpecificDirName=external_define(dll_name, "GMWSetLangSpecificDirName", dll_cdecl, ty_real, 1, ty_string);

global.dll_GMWLoadBank=external_define(dll_name, "GMWLoadBank", dll_cdecl, ty_real, 1, ty_string);

global.dll_GMWUnloadBank=external_define(dll_name, "GMWUnloadBank", dll_cdecl, ty_real, 1, ty_real);


// Listener
global.dll_GMWSet2DListenerPosition=external_define(dll_name, "GMWSet2DListenerPosition", dll_cdecl, ty_real, 4, ty_real, ty_real, ty_real, ty_real);

global.dll_GMWSet3DListenerPosition=external_define(dll_name, "GMWSet3DListenerPosition", dll_cdecl, ty_real, 6, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real);

global.dll_GMWSetActiveListeners=external_define(dll_name, "GMWSetActiveListeners", dll_cdecl, ty_real, 2, ty_real, ty_real);


// Game object
global.dll_GMWRegisterGroupGameObj=external_define(dll_name, "GMWRegisterGroupGameObj", dll_cdecl, ty_real, 1, ty_real);

global.dll_GMWUnregisterGroupGameObj=external_define(dll_name, "GMWUnregisterGroupGameObj", dll_cdecl, ty_real, 1, ty_real);

global.dll_GMWRegisterGameObj=external_define(dll_name, "GMWRegisterGameObj", dll_cdecl, ty_real, 2, ty_real, ty_real);

global.dll_GMWUnregisterGameObj=external_define(dll_name, "GMWUnregisterGameObj", dll_cdecl, ty_real, 2, ty_real, ty_real);

global.dll_GMWSet2DPosition=external_define(dll_name, "GMWSet2DPosition", dll_cdecl, ty_real, 5, ty_real, ty_real, ty_real, ty_real, ty_real);

global.dll_GMWSet3DPosition=external_define(dll_name, "GMWSet3DPosition", dll_cdecl, ty_real, 7, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real);

global.dll_GMWPostEvent=external_define(dll_name, "GMWPostEvent", dll_cdecl, ty_real, 2, ty_real, ty_real);

global.dll_GMWStopAll=external_define(dll_name, "GMWStopAll", dll_cdecl, ty_real, 1, ty_real);

global.dll_GMWSetRTPCValue=external_define(dll_name, "GMWSetRTPCValue", dll_cdecl, ty_real, 3, ty_real, ty_real, ty_real);

global.dll_GMWGetRTPCValue=external_define(dll_name, "GMWGetRTPCValue", dll_cdecl, ty_real, 2, ty_real, ty_real);

global.dll_GMWPostTrigger=external_define(dll_name, "GMWPostTrigger", dll_cdecl, ty_real, 2, ty_real, ty_real);

global.dll_GMWSetSwitch=external_define(dll_name, "GMWSetSwitch", dll_cdecl, ty_real, 3, ty_real, ty_real, ty_real);

#define UnloadGMWwise
////////////////////////////////////////////////////////
// Liberation de la dll de GMWwise.
// A appeler une fois a la fin du jeu.
////////////////////////////////////////////////////////
external_free(working_directory + "\GMWwise.dll");
#define GMWInit
////////////////////////////////////////////////////////
// Initialisation de GMWwise
// A appeler a la creation du jeu
////////////////////////////////////////////////////////
external_call(global.dll_GMWInit);
#define GMWShutdown
////////////////////////////////////////////////////////
// Fermeture de GMWwise
// A appeler a la fin du jeu.
////////////////////////////////////////////////////////
external_call(global.dll_GMWShutdown);
#define GMWProcessAudio
////////////////////////////////////////////////////////
// Traitement de la pile d'evenemt.
// A appeler a chaque frame.
////////////////////////////////////////////////////////
external_call(global.dll_GMWProcessAudio);
#define GMWSetState
////////////////////////////////////////////////////////
// Definit l'etat d'un groupe d'etat - Ajout Martin Bussy-Pâris/Julien Renoux (oubli update)
// - argument0 stateGroup
// - argument1 state
////////////////////////////////////////////////////////
external_call(global.dll_GMWSetState, argument0, argument1);

#define GMWSetBasePath
////////////////////////////////////////////////////////
// Definie le chemin ou se trouve les banques sonores.
// - argument0 Chemin du dossier ou ce trouve les banques sonores.
// - Renvoie 0 sinon un code d'erreur.
////////////////////////////////////////////////////////
return external_call(global.dll_GMWSetBasePath, argument0);
#define GMWSetLangSpecificDirName
////////////////////////////////////////////////////////
// Definie le sous repertoire de langue.
// - argument0 Chemin du sous repertoire de langue.
// - Renvoie 0 sinon un code d'erreur.
////////////////////////////////////////////////////////
return external_call(global.dll_GMWSetLangSpecificDirName, argument0);
#define GMWLoadBank
////////////////////////////////////////////////////////
// Chargement de la banque.
// - argument0 Nom de la banque.
// - Renvoie l'identifiant de la banque sinon un code d'erreur.
////////////////////////////////////////////////////////
return external_call(global.dll_GMWLoadBank, argument0);
#define GMWUnloadBank
////////////////////////////////////////////////////////
// Fermeture de toute les banques -
// - argument0 Identifiant de la banque.
// - Renvoie 0 sinon un code d'erreur.
////////////////////////////////////////////////////////
return external_call(global.dll_GMWUnloadBank, argument0);

#define GMWSetActiveListeners
// Definie les listeners actifs pour un "game object" donne.
// gameObjectID Identifiant du "game object".
// listener Bitmask pour activer/desactiver.
// Renvoie toujours 0.
//
// exemple : 5 -> 0101 -> seulement le listener 1 et 3 sont actif
// avec le gameObjectID specifie.
// GMW_API double STDCALL GMWSetActiveListeners(double gameObjectID, double listenerBitmask);

// Normalement vous n'avez pas besoin d'y toucher pour un usage classique. 

external_call(global.dll_GMWSetActiveListeners, argument0, argument1);

#define GMWSet3DListenerPosition
////////////////////////////////////////////////////////
// Definie la position du listener grâce à 2 vecteurs
// - argument0 Position du listener sur l'axe des X.
// - argument1 Position du listener sur l'axe des Y.
// - argument2 Position du listener sur l'axe des Z.
// - argument3 Orientation du listener sur l'axe des X.
// - argument4 Orientation du listener sur l'axe des Y.
// - argument5 Orientation du listener sur l'axe des Z.
////////////////////////////////////////////////////////
external_call(global.dll_GMWSet3DListenerPosition, argument0, argument1, argument2, argument3, argument4, argument5);

#define GMWSet2DListenerPosition
////////////////////////////////////////////////////////
// Definie la position du listener grâce à 2 vecteurs
// - argument0 Position du listener sur l'axe des X.
// - argument1 Position du listener sur l'axe des Y.
// - argument2 Orientation du listener sur l'axe des X.
// - argument3 Orientation du listener sur l'axe des Y.
////////////////////////////////////////////////////////
external_call(global.dll_GMWSet2DListenerPosition, argument0, argument1, argument2, argument3);

#define GMWStopAll
////////////////////////////////////////////////////////
// Stop tout les evenements associe au "game object".
// Si argument0 vaut -1 tout les evenements sont stoppe.
// - argument0 Identifiant du "game object".
////////////////////////////////////////////////////////
external_call(global.dll_GMWStopAll, argument0);
#define GMWSet2DPosition
////////////////////////////////////////////////////////
// Definie la position du "game object" grâce à 2 vecteurs
// - argument0 Identifiant du "game object".
// - argument1 Position sur l'axe des X.
// - argument2 Position sur l'axe des Y.
// - argument3 Orientation sur l'axe des X.
// - argument4 Orientation sur l'axe des Y.
////////////////////////////////////////////////////////
external_call(global.dll_GMWSet2DPosition, argument0, argument1, argument2, argument3, argument4);

#define GMWSet3DPosition
////////////////////////////////////////////////////////
// Definie la position du "game object" grâce à 2 vecteurs
// - argument0 Identifiant du "game object".
// - argument1 Position sur l'axe des X.
// - argument2 Position sur l'axe des Y.
// - argument3 Position sur l'axe des Z.
// - argument4 Orientation sur l'axe des X.
// - argument5 Orientation sur l'axe des Y.
// - argument6 Orientation sur l'axe des Z.
////////////////////////////////////////////////////////
external_call(global.dll_GMWSet3DPosition, argument0, argument1, argument2, argument3, argument4, argument5, argument6);

#define GMWRegisterGroupGameObj
////////////////////////////////////////////////////////
// Enregistrement d'un groupe de "game object".
// - argument0 Identifiant du groupe  de "game object".
////////////////////////////////////////////////////////
external_call(global.dll_GMWRegisterGroupGameObj, argument0);
#define GMWUnregisterGroupGameObj
////////////////////////////////////////////////////////
// Suppression d'un groupe de "game object".
// - argument0 Identifiant du groupe de "game object".
////////////////////////////////////////////////////////
external_call(global.dll_GMWUnregisterGroupGameObj, argument0);
#define GMWRegisterGameObj
////////////////////////////////////////////////////////
// Enregistrement d'un "game object".
// - argument0 Identifiant du "game object".
// - argument1 Identifiant du groupe de "game object".
// - Renvoie 0 sinon une code d'erreur.
////////////////////////////////////////////////////////
return external_call(global.dll_GMWRegisterGameObj, argument0, argument1);
#define GMWUnregisterGameObj
////////////////////////////////////////////////////////
// Suppression d'une "game object".
// - argument0 Identifiant du "game object".
// - argument1 Identifiant du groupe de "game object".
// - Renvoie 0 sinon un code d'erreur.
////////////////////////////////////////////////////////
return external_call(global.dll_GMWUnregisterGameObj, argument0, argument1);
#define GMWPostEvent
////////////////////////////////////////////////////////
// Envoie d'un evenements dans la pile d'evenements de wwise.
// - argument0 L'identifiant unique de l'evenement. 
// - argument1 Identifiant du "game object" associe a l'evenement.
// - Renvoie l'identifiant de l'evenement sinon un code d'erreur.
////////////////////////////////////////////////////////
return external_call(global.dll_GMWPostEvent, argument0, argument1);
#define GMWPostTrigger
////////////////////////////////////////////////////////
// PostTrigger - Ajout Martin Bussy-Pâris/Julien Renoux (oubli update)
// - argument0 triggerID
// - argument1 gameObjectID
////////////////////////////////////////////////////////
external_call(global.dll_GMWPostTrigger, argument0, argument1);

#define GMWSetSwitch
////////////////////////////////////////////////////////
// PostTrigger - Ajout Martin Bussy-Pâris/Julien Renoux (oubli update)
// - argument0 triggerID
// - argument1 gameObjectID
// - argument2 gameObjectID
////////////////////////////////////////////////////////
external_call(global.dll_GMWSetSwitch, argument0, argument1, argument2);

#define GMWSetRTPCValue
////////////////////////////////////////////////////////
// Set the value of the real-time parameter control by ID.
// - argument0 _dRtpcID ID of the game parameter.
// - argument1 _dRtpcValue Value to set.
// - argument2 _dGameObjectID Associated game object ID.
////////////////////////////////////////////////////////
external_call(global.dll_GMWSetRTPCValue, argument0, argument1, argument2);

#define GMWGetRTPCValue
////////////////////////////////////////////////////////
// Retrieves RTPC value.
// - argument0 _dRtpcID ID of the RTPC.
// - argument1 _dGameObjectID Associated game object ID.
////////////////////////////////////////////////////////
external_call(global.dll_GMWGetRTPCValue, argument0, argument1, argument2);

#define GMWRegisterPlugin
////////////////////////////////////////////////////////
//  Register a wwise plugin.
// - argument0 _dType Type of plugin.
// - return 0 or an error code.
//
//		Plugin list:
//			0 Sine
//			1 Tone Generator
//			2 Silence
//			3 Audio Input
//			4 Delay
//			5 Parametric EQ
//			6 Matrix Reverb
//			7 Compressor
//			8 Expander
//			9 Peak Limiter
//			10 Roomverb.
//			11 Pitch Shifter
//			12 Meter
////////////////////////////////////////////////////////
external_call(global.dll_GMWRegisterPlugin, argument0);

#define GMWRegisterCodec
////////////////////////////////////////////////////////
// Enregistrement d'un codec.
// - argument0 Type de codec.
// - Renvoie  0 ou un code d'erreur.
//
// List des codecs:
// 0 Vorbis
////////////////////////////////////////////////////////
external_call(global.dll_GMWRegisterCodec, argument0);
