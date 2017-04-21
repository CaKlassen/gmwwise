// Unregister the sound controller
gmwUnregisterObject(id, global.DEFAULT_GROUP);

// Unload the sound banks
gmwUnloadBank(global.TEST_BANK);
gmwUnloadBank(global.GAME_BANK);

// Stop GMWWise
gmwStop();

