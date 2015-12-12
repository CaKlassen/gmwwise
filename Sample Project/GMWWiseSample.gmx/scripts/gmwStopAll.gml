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
