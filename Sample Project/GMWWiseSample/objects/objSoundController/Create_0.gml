// STARTING FUNCTIONALITY //

// GMWWise Initialization
global.GMW_PROFILE = true;

gmwInit();

var path = "";

if (os_type == os_macosx)
    path = working_directory + "sound/banks/Mac/";
else
    path = working_directory + "sound/banks/Windows/";
    
gmwSetBasePath(path);
    
// Initialize the banks
global.INIT_BANK = gmwLoadBank("Init.bnk");
global.GAME_BANK = gmwLoadBank("SoundBank.bnk");

global.DEFAULT_GROUP = 1;

// Register the sound controller with the engine
gmwRegisterObject(id, global.DEFAULT_GROUP, "Sound Controller");


// Initialize links to IDs
global.WWE_BOUNCE = 3465618802;
global.WWE_PLAY_MUSIC = 2932040671;

global.WWSG_AUDIO_TYPE = 1382476432;
global.WWS_REGULAR_EARS = 3909415557;
global.WWS_PLUGGED_EARS = 3764425673;

global.WWXG_WALL_GROUP = 376337484;
global.WWX_WALL_STONE = 1216965916;
global.WWX_WALL_WOOD = 2058049674;

global.WWP_MUSIC_VOLUME = 1006694123;

// Set the music volume to max and start playing it
global.VOLUME = 100;

gmwSetGlobalParameter(global.WWP_MUSIC_VOLUME, global.VOLUME);
gmwPostEvent(global.WWE_PLAY_MUSIC, id);

// Set up the initial ear state
global.PLUGGED_EARS = false;
gmwSetState(global.WWSG_AUDIO_TYPE, global.WWS_REGULAR_EARS);

