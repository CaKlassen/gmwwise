// Toggling music
if (keyboard_check_pressed(ord("M")))
{
    if (global.VOLUME == 100)
    {
        // Mute the music
        global.VOLUME = 0;
        gmwSetGlobalParameter(global.WWP_MUSIC_VOLUME, global.VOLUME);
    }
    else
    {
        // Mute the music
        global.VOLUME = 100;
        gmwSetGlobalParameter(global.WWP_MUSIC_VOLUME, global.VOLUME);
    }
}

// Toggling ear state
if (keyboard_check_pressed(vk_space))
{
    if (global.PLUGGED_EARS)
    {
        // Set the ear state back to regular
        global.PLUGGED_EARS = false;
        gmwSetState(global.WWSG_AUDIO_TYPE, global.WWS_REGULAR_EARS);
    }
    else
    {
        // Set the ear state to plugged ears
        global.PLUGGED_EARS = true;
        gmwSetState(global.WWSG_AUDIO_TYPE, global.WWS_PLUGGED_EARS);
    }
}

