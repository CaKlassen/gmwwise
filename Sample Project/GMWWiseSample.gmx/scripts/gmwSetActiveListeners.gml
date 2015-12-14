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
