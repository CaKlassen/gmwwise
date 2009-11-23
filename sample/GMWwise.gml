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
global.dll_GMWInit=external_define(dll_name, "GMWInit", dll_stdcall, ty_real, 0);

global.dll_GMWShutdown=external_define(dll_name, "GMWShutdown", dll_stdcall, ty_real, 0);

global.dll_GMWProcessAudio=external_define(dll_name, "GMWProcessAudio", dll_stdcall, ty_real, 0);


// Bank
global.dll_GMWSetBasePath=external_define(dll_name, "GMWSetBasePath", dll_stdcall, ty_real, 1, ty_string);

global.dll_GMWSetLangSpecificDirName=external_define(dll_name, "GMWSetLangSpecificDirName", dll_stdcall, ty_real, 1, ty_string);

global.dll_GMWLoadBank=external_define(dll_name, "GMWLoadBank", dll_stdcall, ty_real, 1, ty_string);

global.dll_GMWUnloadBank=external_define(dll_name, "GMWUnloadBank", dll_stdcall, ty_real, 1, ty_real);


// Listener
global.dll_GMWSet2DListenerPosition=external_define(dll_name, "GMWSet2DListenerPosition", dll_stdcall, ty_real, 4, ty_real, ty_real, ty_real, ty_real);

global.dll_GMWSet3DListenerPosition=external_define(dll_name, "GMWSet3DListenerPosition", dll_stdcall, ty_real, 6, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real);

global.dll_GMWSetActiveListeners=external_define(dll_name, "GMWSetActiveListeners", dll_stdcall, ty_real, 2, ty_real, ty_real);

// Game object
global.dll_GMWRegisterGroupGameObj=external_define(dll_name, "GMWRegisterGroupGameObj", dll_stdcall, ty_real, 1, ty_real);

global.dll_GMWUnregisterGroupGameObj=external_define(dll_name, "GMWUnregisterGroupGameObj", dll_stdcall, ty_real, 1, ty_real);

global.dll_GMWRegisterGameObj=external_define(dll_name, "GMWRegisterGameObj", dll_stdcall, ty_real, 2, ty_real, ty_real);

global.dll_GMWUnregisterGameObj=external_define(dll_name, "GMWUnregisterGameObj", dll_stdcall, ty_real, 2, ty_real, ty_real);

global.dll_GMWSet2DPosition=external_define(dll_name, "GMWSet2DPosition", dll_stdcall, ty_real, 5, ty_real, ty_real, ty_real, ty_real, ty_real);

global.dll_GMWSet3DPosition=external_define(dll_name, "GMWSet3DPosition", dll_stdcall, ty_real, 7, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real);

global.dll_GMWPostEvent=external_define(dll_name, "GMWPostEvent", dll_stdcall, ty_real, 2, ty_real, ty_real);

global.dll_GMWStopAll=external_define(dll_name, "GMWStopAll", dll_stdcall, ty_real, 1, ty_real);
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
#define GMWSet2DListenerPosition
////////////////////////////////////////////////////////
// Definie la position du listener.
// - argument0 Position du listener sur l'axe des X.
// - argument1 Position du listener sur l'axe des Y.
// - argument2 Orientation du listener sur l'axe des X.
// - argument3 Orientation du listener sur l'axe des Y.
////////////////////////////////////////////////////////
external_call(global.dll_GMWSet2DListenerPosition, argument0, argument1, argument2, argument3);
#define GMW3DListenerPosition
////////////////////////////////////////////////////////
// Definie la position du listener.
// - argument0 Position du listener sur l'axe des X.
// - argument1 Position du listener sur l'axe des Y.
// - argument2 Position du listener sur l'axe des Z.
// - argument3 Orientation du listener sur l'axe des X.
// - argument4 Orientation du listener sur l'axe des Y.
// - argument5 Orientation du listener sur l'axe des Z.
////////////////////////////////////////////////////////
external_call(global.dll_GMWSet3DListenerPosition, argument0, argument1, argument2, argument3, argument4, argument5);
#define GMWSetActiveListeners
external_call(global.dll_GMWSetActiveListeners, argument0, argument1);
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
// Dechargement de la banque.
// - argument0 Identifiant de la banque.
// - Renvoie 0 sinon un code d'erreur.
////////////////////////////////////////////////////////
return external_call(global.dll_GMWUnloadBank, argument0);
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
#define GMWSet2DPosition
////////////////////////////////////////////////////////
// Definie la position du "game object".
// - argument0 Identifiant du "game object".
// - argument1 Position sur l'axe des X.
// - argument2 Position sur l'axe des Y.
////////////////////////////////////////////////////////
external_call(global.dll_GMWSet2DPosition, argument0, argument1, argument2, argument3, argument4);
#define GMWSet3DPosition
////////////////////////////////////////////////////////
// Definie la position du "game object".
// - argument0 Identifiant du "game object".
// - argument1 Position sur l'axe des X.
// - argument2 Position sur l'axe des Y.
// - argument3 Position sur l'axe des Z.
// - argument4 Orientation sur l'axe des X.
// - argument5 Orientation sur l'axe des Y.
// - argument6 Orientation sur l'axe des Z.
////////////////////////////////////////////////////////
external_call(global.dll_GMWSet3DPosition, argument0, argument1, argument2, argument3, argument4, argument5, argument6);
#define GMWPostEvent
////////////////////////////////////////////////////////
// Envoie d'un evenements dans la pile d'evenements de wwise.
// - argument0 L'identifiant unique de l'evenement. 
// - argument1 Identifiant du "game object" associe a l'evenement.
// - Renvoie l'identifiant de l'evenement sinon un code d'erreur.
////////////////////////////////////////////////////////
return external_call(global.dll_GMWPostEvent, argument0, argument1);
#define GMWStopAll
////////////////////////////////////////////////////////
// Stop tout les evenements associe au "game object".
// Si argument0 vaut -1 tout les evenements sont stoppe.
// - argument0 Identifiant du "game object".
////////////////////////////////////////////////////////
external_call(global.dll_GMWStopAll, argument0);
