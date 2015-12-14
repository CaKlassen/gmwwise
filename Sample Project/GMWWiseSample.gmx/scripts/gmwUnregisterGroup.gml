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
