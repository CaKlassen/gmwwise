/*
    SCRIPT: gmwSet2DPosition(xPos, yPos, zPos, xOr, yOr, zOr);

    PARAMETERS: 
        xPos - the x position of the object
        yPos - the y position of the object
        zPos - the z position of the object
        xOr - the x orientation of the object
        yOr - the y orientation of the object
        zOr - the z orientation of the object

    RETURNS: nothing

    AUTHOR: Cédric Liaudet

    DATE: N/A

    NOTES: 
        This function sets the 3D position and orientation of an object in GMW.
*/


external_call(global.dll_GMWSet3DPosition, argument0, argument1, argument2, argument3, argument4, argument5, argument6);
