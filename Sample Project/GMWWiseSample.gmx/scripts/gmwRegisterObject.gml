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
