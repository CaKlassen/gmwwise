/*
    SCRIPT: gmwLoad();

    PARAMETERS: 

    RETURNS: boolean - whether or not GMWwise was found

    AUTHOR: Cédric Liaudet

    DATE: N/A

    NOTES: 
        This function is called when the game is first launched in order to load the DLLs.
*/


dll_name = 'GMWwise.dll';

if(global.GMW_PROFILE == true)
{
    dll_name = 'GMWwise_profile.dll';
}

if !file_exists(dll_name)
{
    return false;
}


// Basic engine
global.dll_GMWInit=external_define(dll_name, "GMWInit", dll_cdecl, ty_real, 0);

global.dll_GMWShutdown=external_define(dll_name, "GMWShutdown", dll_cdecl, ty_real, 0);

global.dll_GMWProcessAudio=external_define(dll_name, "GMWProcessAudio", dll_cdecl, ty_real, 0);

global.dll_GMWSetState=external_define(dll_name, "GMWSetState", dll_cdecl, ty_real, 2, ty_real, ty_real);

global.dll_GMWRegisterPlugin=external_define(dll_name, "GMWRegisterPlugin", dll_cdecl, ty_real, 1, ty_real);

global.dll_GMWRegisterCodec=external_define(dll_name, "GMWRegisterCodec", dll_cdecl, ty_real, 1, ty_real);


// Bank
global.dll_GMWSetBasePath=external_define(dll_name, "GMWSetBasePath", dll_cdecl, ty_real, 1, ty_string);

//global.dll_GMWSetLangSpecificDirName=external_define(dll_name, "GMWSetLangSpecificDirName", dll_cdecl, ty_real, 1, ty_string);

global.dll_GMWLoadBank=external_define(dll_name, "GMWLoadBank", dll_cdecl, ty_real, 1, ty_string);

global.dll_GMWUnloadBank=external_define(dll_name, "GMWUnloadBank", dll_cdecl, ty_real, 1, ty_real);


// Listener
global.dll_GMWSet2DListenerPosition=external_define(dll_name, "GMWSet2DListenerPosition", dll_cdecl, ty_real, 4, ty_real, ty_real, ty_real, ty_real);

global.dll_GMWSet3DListenerPosition=external_define(dll_name, "GMWSet3DListenerPosition", dll_cdecl, ty_real, 6, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real);

global.dll_GMWSetActiveListeners=external_define(dll_name, "GMWSetActiveListeners", dll_cdecl, ty_real, 2, ty_real, ty_real);


// Game object
global.dll_GMWRegisterGroupGameObj=external_define(dll_name, "GMWRegisterGroupGameObj", dll_cdecl, ty_real, 1, ty_real);

global.dll_GMWUnregisterGroupGameObj=external_define(dll_name, "GMWUnregisterGroupGameObj", dll_cdecl, ty_real, 1, ty_real);

global.dll_GMWRegisterGameObj=external_define(dll_name, "GMWRegisterGameObj", dll_cdecl, ty_real, 3, ty_real, ty_real, ty_string);

global.dll_GMWUnregisterGameObj=external_define(dll_name, "GMWUnregisterGameObj", dll_cdecl, ty_real, 2, ty_real, ty_real);

global.dll_GMWSet2DPosition=external_define(dll_name, "GMWSet2DPosition", dll_cdecl, ty_real, 5, ty_real, ty_real, ty_real, ty_real, ty_real);

global.dll_GMWSet3DPosition=external_define(dll_name, "GMWSet3DPosition", dll_cdecl, ty_real, 7, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real);

global.dll_GMWPostEvent=external_define(dll_name, "GMWPostEvent", dll_cdecl, ty_real, 2, ty_real, ty_real);

global.dll_GMWStopAll=external_define(dll_name, "GMWStopAll", dll_cdecl, ty_real, 1, ty_real);

global.dll_GMWSetRTPCValue=external_define(dll_name, "GMWSetRTPCValue", dll_cdecl, ty_real, 3, ty_real, ty_real, ty_real);

global.dll_GMWSetGlobalRTPCValue=external_define(dll_name, "GMWSetGlobalRTPCValue", dll_cdecl, ty_real, 2, ty_real, ty_real);

global.dll_GMWGetRTPCValue=external_define(dll_name, "GMWGetRTPCValue", dll_cdecl, ty_real, 2, ty_real, ty_real);

global.dll_GMWPostTrigger=external_define(dll_name, "GMWPostTrigger", dll_cdecl, ty_real, 2, ty_real, ty_real);

global.dll_GMWSetSwitch=external_define(dll_name, "GMWSetSwitch", dll_cdecl, ty_real, 3, ty_real, ty_real, ty_real);

return true;
