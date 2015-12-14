/*
    SCRIPT: gmwRegisterCodec(codec);

    PARAMETERS: 
        codec - the codec to register

    RETURNS: 0 if successful, or an error code

    AUTHOR: Cédric Liaudet

    DATE: N/A

    NOTES: 
        This function registers a codec with Wwise.
        
        Types:
            0 - Ogg Vorbis
*/


external_call(global.dll_GMWRegisterCodec, argument0);
