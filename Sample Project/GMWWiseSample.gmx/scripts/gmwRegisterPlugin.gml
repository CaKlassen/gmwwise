/*
    SCRIPT: gmwRegisterPlugin(pluginType);

    PARAMETERS: 
        pluginType - the type of plugin to register

    RETURNS: 0 if successful, or an error code

    AUTHOR: Cédric Liaudet

    DATE: N/A

    NOTES: 
        This function registers a plugin for Wwise.
        
        Types:
            0 - sine
            1 - tone generator
            2 - silence
            3 - audio input
            4 - delay
            5 - parametric EQ
            6 - Matrix Reverb
            7 - Compressor
            8 - Expander
            9 - Peak Limiter
            10 - Roomverb
*/


external_call(global.dll_GMWRegisterPlugin, argument0);
