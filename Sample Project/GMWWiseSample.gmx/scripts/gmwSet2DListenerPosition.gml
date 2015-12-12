/*
    SCRIPT: gmwSet3DListenerPosition(xPos, yPos, xOr, yOr);

    PARAMETERS: 
        xPos - the x position of the listener
        yPos - the y position of the listener
        xOr - the x orientation of the listener
        yOr - the y orientation of the listener

    RETURNS: nothing

    AUTHOR: Cédric Liaudet

    DATE: N/A

    NOTES: 
        This function sets the 2D position and orientation of the listener
*/


external_call(global.dll_GMWSet2DListenerPosition, argument0, argument1, argument2, argument3);
