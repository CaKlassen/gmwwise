/*
    SCRIPT: gmwPostEvent(triggerID, object);

    PARAMETERS: 
        triggerID - the trigger ID to post
        object - the object to post from

    RETURNS: nothing

    AUTHOR: Cédric Liaudet
            Martin Bussy-Pâris
            Julien Renoux

    DATE: N/A

    NOTES: 
        This function posts a trigger for a specific game object.
*/


external_call(global.dll_GMWPostTrigger, argument0, argument1);
