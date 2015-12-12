/*
    SCRIPT: gmwUnloadBank(bankID);

    PARAMETERS: 
        bankID - the bank to unload

    RETURNS: 0 if successful, otherwise an error code

    AUTHOR: Cédric Liaudet

    DATE: N/A

    NOTES: 
        This function unloads a bank by its ID.
*/


return external_call(global.dll_GMWUnloadBank, argument0);
