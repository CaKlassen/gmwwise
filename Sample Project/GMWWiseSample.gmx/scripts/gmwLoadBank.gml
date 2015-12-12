/*
    SCRIPT: gmwLoadBank(bankName);

    PARAMETERS: 
        bankName - the bank to load

    RETURNS: the bank ID, otherwise an error code

    AUTHOR: Cédric Liaudet

    DATE: N/A

    NOTES: 
        This function loads a specific bank by filename.
*/


return external_call(global.dll_GMWLoadBank, argument0);
