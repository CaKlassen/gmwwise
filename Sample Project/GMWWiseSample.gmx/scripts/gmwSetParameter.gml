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
