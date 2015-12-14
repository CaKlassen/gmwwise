/*
    SCRIPT: gmwSet2DPosition(xPos, yPos, xOr, yOr);

    PARAMETERS: 
        xPos - the x position of the object
        yPos - the y position of the object
        xOr - the x orientation of the object
        yOr - the y orientation of the object

    RETURNS: nothing

    AUTHOR: Cédric Liaudet

    DATE: N/A

    NOTES: 
        This function sets the 2D position and orientation of an object in GMW.
*/


external_call(global.dll_GMWSet2DPosition, argument0, argument1, argument2, argument3, argument4);
