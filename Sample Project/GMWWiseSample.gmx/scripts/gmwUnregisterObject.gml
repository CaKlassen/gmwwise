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
