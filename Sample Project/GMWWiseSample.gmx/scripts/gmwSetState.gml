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
