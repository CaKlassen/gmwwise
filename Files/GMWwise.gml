#define gmwLoad
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

#define gmwInit
/*
    SCRIPT: gmwInit();

    PARAMETERS: 

    RETURNS: nothing

    AUTHOR: Cédric Liaudet

    DATE: N/A

    NOTES: 
        This function initializes the GMWwise engine at the start of the game.
*/


external_call(global.dll_GMWInit);

#define gmwSetBasePath
/*
    SCRIPT: gmwSetBasePath(basePath);

    PARAMETERS: 
        basePath - the path to set

    RETURNS: 0 if successful, otherwise an error code

    AUTHOR: Cédric Liaudet

    DATE: N/A

    NOTES: 
        This function sets the base path to search for the sound banks.
*/


return external_call(global.dll_GMWSetBasePath, argument0);

#define gmwSetLanguageDirName
/*
    SCRIPT: gmwSetLanguageDirName(path);

    PARAMETERS: 
        path - the path to set

    RETURNS: 0 if successful, otherwise an error code

    AUTHOR: Cédric Liaudet

    DATE: N/A

    NOTES: 
        This function sets the search directory for a specific language.
*/


//return external_call(global.dll_GMWSetLangSpecificDirName, argument0);

#define gmwRegisterPlugin
/*
    SCRIPT: gmwRegisterPlugin(pluginType);

    PARAMETERS: 
        pluginType - the type of plugin to register

    RETURNS: 0 if successful, or an error code

    AUTHOR: Cédric Liaudet

    DATE: N/A

    NOTES: 
        This function registers a plugin for Wwise.
        
        Types:
            0 - sine
            1 - tone generator
            2 - silence
            3 - audio input
            4 - delay
            5 - parametric EQ
            6 - Matrix Reverb
            7 - Compressor
            8 - Expander
            9 - Peak Limiter
            10 - Roomverb
*/


external_call(global.dll_GMWRegisterPlugin, argument0);

#define gmwRegisterCodec
/*
    SCRIPT: gmwRegisterCodec(codec);

    PARAMETERS: 
        codec - the codec to register

    RETURNS: 0 if successful, or an error code

    AUTHOR: Cédric Liaudet

    DATE: N/A

    NOTES: 
        This function registers a codec with Wwise.
        
        Types:
            0 - Ogg Vorbis
*/


external_call(global.dll_GMWRegisterCodec, argument0);

#define gmwStop
/*
    SCRIPT: gmwStop();

    PARAMETERS: 

    RETURNS: nothing

    AUTHOR: Cédric Liaudet

    DATE: N/A

    NOTES: 
        This function is called when the game ends to stop the GMWwise engine.
*/


external_call(global.dll_GMWShutdown);

#define gmwUnload
/*
    SCRIPT: gmwUnload();

    PARAMETERS: 

    RETURNS: nothing

    AUTHOR: Cédric Liaudet

    DATE: N/A

    NOTES: 
        This function is called at the end of the game to free the DLLs.
*/


external_free(working_directory + "\GMWwise.dll");

#define gmwProcess
/*
    SCRIPT: gmwProcess();

    PARAMETERS: 

    RETURNS: nothing
    
    AUTHOR: Cédric Liaudet

    DATE: N/A

    NOTES: 
        This function must be called in every frame to check for and update GMWwise events.
*/


external_call(global.dll_GMWProcessAudio);

#define gmwStopAll
/*
    SCRIPT: gmwStopAll(objectID);

    PARAMETERS: 
        objectID - the game object ID (-1 for all objects)

    RETURNS: nothing

    AUTHOR: Cédric Liaudet

    DATE: N/A

    NOTES: 
        This function stops all events for an object.
*/


external_call(global.dll_GMWStopAll, argument0);

#define gmwLoadBank
/*
    SCRIPT: gmwLoadBank(bankName);

    PARAMETERS: 
        bankName - the bank to load

    RETURNS: the bank ID, otherwise an error code

    AUTHOR: Cédric Liaudet

    DATE: N/A

    NOTES: 
        This function loads a specific bank by filename.
*/


return external_call(global.dll_GMWLoadBank, argument0);

#define gmwUnloadBank
/*
    SCRIPT: gmwUnloadBank(bankID);

    PARAMETERS: 
        bankID - the bank to unload

    RETURNS: 0 if successful, otherwise an error code

    AUTHOR: Cédric Liaudet

    DATE: N/A

    NOTES: 
        This function unloads a bank by its ID.
*/


return external_call(global.dll_GMWUnloadBank, argument0);

#define gmwSetActiveListeners
/*
    SCRIPT: gmwSetActiveListeners(objectID, listenerBitmask);

    PARAMETERS: 
        objectID - the object to update listeners for
        listenerBitmask - the bitmask to use when setting listeners

    RETURNS: nothing

    AUTHOR: Cédric Liaudet

    DATE: N/A

    NOTES: 
        This function sets the active listeners for an object via a bitmask.
*/


external_call(global.dll_GMWSetActiveListeners, argument0, argument1);

#define gmwSet2DListenerPosition
/*
    SCRIPT: gmwSet3DListenerPosition(xPos, yPos, xOr, yOr);

    PARAMETERS: 
        xPos - the x position of the listener
        yPos - the y position of the listener
        xOr - the x orientation of the listener
        yOr - the y orientation of the listener

    RETURNS: nothing

    AUTHOR: Cédric Liaudet

    DATE: N/A

    NOTES: 
        This function sets the 2D position and orientation of the listener
*/


external_call(global.dll_GMWSet2DListenerPosition, argument0, argument1, argument2, argument3);

#define gmwSet3DListenerPosition
/*
    SCRIPT: gmwSet3DListenerPosition(xPos, yPos, zPos, xOr, yOr, zOr);

    PARAMETERS: 
        xPos - the x position of the listener
        yPos - the y position of the listener
        zPos - the z position of the listener
        xOr - the x orientation of the listener
        yOr - the y orientation of the listener
        zOr - the z orientation of the listener

    RETURNS: nothing

    AUTHOR: Cédric Liaudet

    DATE: N/A

    NOTES: 
        This function sets the 3D position and orientation of the listener
*/


external_call(global.dll_GMWSet3DListenerPosition, argument0, argument1, argument2, argument3, argument4, argument5);

#define gmwSet2DPosition
/*
    SCRIPT: gmwSet2DPosition(xPos, yPos, xOr, yOr);

    PARAMETERS: 
        xPos - the x position of the object
        yPos - the y position of the object
        xOr - the x orientation of the object
        yOr - the y orientation of the object

    RETURNS: nothing

    AUTHOR: Cédric Liaudet

    DATE: N/A

    NOTES: 
        This function sets the 2D position and orientation of an object in GMW.
*/


external_call(global.dll_GMWSet2DPosition, argument0, argument1, argument2, argument3, argument4);

#define gmwSet3DPosition
/*
    SCRIPT: gmwSet2DPosition(xPos, yPos, zPos, xOr, yOr, zOr);

    PARAMETERS: 
        xPos - the x position of the object
        yPos - the y position of the object
        zPos - the z position of the object
        xOr - the x orientation of the object
        yOr - the y orientation of the object
        zOr - the z orientation of the object

    RETURNS: nothing

    AUTHOR: Cédric Liaudet

    DATE: N/A

    NOTES: 
        This function sets the 3D position and orientation of an object in GMW.
*/


external_call(global.dll_GMWSet3DPosition, argument0, argument1, argument2, argument3, argument4, argument5, argument6);

#define gmwRegisterGroup
/*
    SCRIPT: gmwRegisterGroup(groupID);

    PARAMETERS: 
        groupID - the group identifier to register

    RETURNS: nothing

    AUTHOR: Cédric Liaudet

    DATE: N/A

    NOTES: 
        This function registers a group of game objects.
*/


external_call(global.dll_GMWRegisterGroupGameObj, argument0);

#define gmwUnregisterGroup
/*
    SCRIPT: gmwUnregisterGroup(groupID);

    PARAMETERS: 
        groupID - the group identifier to unregister

    RETURNS: nothing

    AUTHOR: Cédric Liaudet

    DATE: N/A

    NOTES: 
        This function unregisters a group of game objects.
*/


external_call(global.dll_GMWUnregisterGroupGameObj, argument0);

#define gmwRegisterObject
/*
    SCRIPT: gmwRegisterObject(object, name, group);

    PARAMETERS: 
        object - the object to register
        name - the name of the object (for profiling)
        group - the group to register the object into

    RETURNS: 0 if successful, otherwise an error code

    AUTHOR: Cédric Liaudet

    DATE: N/A

    NOTES: 
        This function registers a game object into a group.
*/


return external_call(global.dll_GMWRegisterGameObj, argument0, argument2, argument1);

#define gmwUnregisterObject
/*
    SCRIPT: gmwUnregisterObject(object, group);

    PARAMETERS: 
        object - the object to unregister
        group - the group to unregister the object into

    RETURNS: 0 if successful, otherwise an error code

    AUTHOR: Cédric Liaudet

    DATE: N/A

    NOTES: 
        This function unregisters a game object from a group.
*/


return external_call(global.dll_GMWUnregisterGameObj, argument0, argument1);

#define gmwSetState
/*
    SCRIPT: gmwSetState(stateGroup, state);

    PARAMETERS: 
        stateGroup - the state group to modify
        state - the state to set the state group to

    RETURNS: nothing

    AUTHOR: Cédric Liaudet
            Martin Bussy-Pâris
            Julien Renoux

    DATE: N/A

    NOTES: 
        This function sets the state of a specific state group.
*/


external_call(global.dll_GMWSetState, argument0, argument1);

#define gmwPostEvent
/*
    SCRIPT: gmwPostEvent(eventID, object);

    PARAMETERS: 
        eventID - the event ID to post
        object - the object to post from

    RETURNS: the event ID, otherwise an error code

    AUTHOR: Cédric Liaudet

    DATE: N/A

    NOTES: 
        This function posts an event for a specific game object.
*/


return external_call(global.dll_GMWPostEvent, argument0, argument1);

#define gmwPostTrigger
/*
    SCRIPT: gmwPostEvent(triggerID, object);

    PARAMETERS: 
        triggerID - the trigger ID to post
        object - the object to post from

    RETURNS: nothing

    AUTHOR: Cédric Liaudet
            Martin Bussy-Pâris
            Julien Renoux

    DATE: N/A

    NOTES: 
        This function posts a trigger for a specific game object.
*/


external_call(global.dll_GMWPostTrigger, argument0, argument1);

#define gmwSetSwitch
/*
    SCRIPT: gmwSetSwitch(switchGroup, switchID, object);

    PARAMETERS: 
        switchGroup - the group to apply the switch to
        switchID - the switch to set
        object - the object to set from

    RETURNS: nothing

    AUTHOR: Cédric Liaudet
            Martin Bussy-Pâris
            Julien Renoux

    DATE: N/A

    NOTES: 
        This function sets a switch for a specific game object.
*/


external_call(global.dll_GMWSetSwitch, argument0, argument1, argument2);

#define gmwSetParameter
/*
    SCRIPT: gmwSetParameter(parID, parValue, object);

    PARAMETERS: 
        parID - the ID of the parameter
        parValue - the value to set the parameter to
        object - the object to set from

    RETURNS: nothing

    AUTHOR: Cédric Liaudet

    DATE: N/A

    NOTES: 
        This function sets the value of an RTPC in WWise.
*/


external_call(global.dll_GMWSetRTPCValue, argument0, argument1, argument2);

#define gmwSetGlobalParameter
/*
    SCRIPT: gmwSetGlobalParameter(parID, parValue);

    PARAMETERS: 
        parID - the ID of the parameter
        parValue - the value to set the parameter to

    RETURNS: nothing

    AUTHOR: Cédric Liaudet

    DATE: N/A

    NOTES: 
        This function sets the value of an RTPC in WWise.
*/


external_call(global.dll_GMWSetGlobalRTPCValue, argument0, argument1);

#define gmwGetParameter
/*
    SCRIPT: gmwGetParameter(parID, object);

    PARAMETERS: 
        parID - the ID of the parameter
        object - the object that it was set from

    RETURNS: the RTPC value, or an error code

    AUTHOR: Cédric Liaudet
            Chris Klassen

    DATE: N/A

    NOTES: 
        This function gets the value of an RTPC from WWise.
*/


return external_call(global.dll_GMWGetRTPCValue, argument0, argument1);

