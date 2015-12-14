/*
    SCRIPT: gmwSet3DListenerPosition(xPos, yPos, zPos, xOr, yOr, zOr);

    PARAMETERS: 
        xPos - the x position of the listener
        yPos - the y position of the listener
        zPos - the z position of the listener
        xOr - the x orientation of the listener
        yOr - the y orientation of the listener
        zOr - the z orientation of the listener

    RETURNS: nothing

    AUTHOR: Cédric Liaudet

    DATE: N/A

    NOTES: 
        This function sets the 3D position and orientation of the listener
*/


external_call(global.dll_GMWSet3DListenerPosition, argument0, argument1, argument2, argument3, argument4, argument5);
