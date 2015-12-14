/*
    SCRIPT: gmwSetBasePath(basePath);

    PARAMETERS: 
        basePath - the path to set

    RETURNS: 0 if successful, otherwise an error code

    AUTHOR: Cédric Liaudet

    DATE: N/A

    NOTES: 
        This function sets the base path to search for the sound banks.
*/


return external_call(global.dll_GMWSetBasePath, argument0);
