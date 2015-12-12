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
