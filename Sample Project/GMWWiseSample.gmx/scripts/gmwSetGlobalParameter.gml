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
