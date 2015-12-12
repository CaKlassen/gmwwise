/*
    SCRIPT: gmwUnload();

    PARAMETERS: 

    RETURNS: nothing

    AUTHOR: Cédric Liaudet

    DATE: N/A

    NOTES: 
        This function is called at the end of the game to free the DLLs.
*/


external_free(working_directory + "\GMWwise.dll");
