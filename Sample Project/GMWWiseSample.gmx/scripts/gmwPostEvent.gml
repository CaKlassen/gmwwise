/*
    SCRIPT: gmwPostEvent(eventID, object);

    PARAMETERS: 
        eventID - the event ID to post
        object - the object to post from

    RETURNS: the event ID, otherwise an error code

    AUTHOR: Cédric Liaudet

    DATE: N/A

    NOTES: 
        This function posts an event for a specific game object.
*/


return external_call(global.dll_GMWPostEvent, argument0, argument1);
