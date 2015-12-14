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
