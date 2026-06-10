#include <systems/AudioManager.h>
#include <iostream>

AudioManager::AudioManager():
jump_sound(nullptr),
hurt_sound(nullptr),
explosion_sound(nullptr),
score_sound(nullptr),
pause_sound(nullptr),
background_music(nullptr),
is_music_playing(false)
{}

void AudioManager::destroy()
{
    // Stop music before freeing
    if (is_music_playing)
    {
        Mix_HaltMusic();
    }

    // Free sound effects
    if (jump_sound)
    {
        Mix_FreeChunk(jump_sound);
    }

    if (hurt_sound)
    {
        Mix_FreeChunk(hurt_sound);
    }

    if (explosion_sound)
    {
        Mix_FreeChunk(explosion_sound);
    }

    if (score_sound)
    {
        Mix_FreeChunk(score_sound);
    }

    if (pause_sound)
    {
        Mix_FreeChunk(pause_sound);
    }
    // Free background music
    if (background_music)
    {
        Mix_FreeMusic(background_music);
    }

    // Close audio system
    Mix_Quit();
}

bool AudioManager::init()
{
    // Initialize mixer
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        std::cerr << "Failed to initialize audio system: " << Mix_GetError() << std::endl;
        return false;
    }

    // Load sound effects
    jump_sound = Mix_LoadWAV("../assets/sounds/jump.wav");
    if (!jump_sound)
    {
        std::cerr << "Failed to load jump sound: " << Mix_GetError() << std::endl;
    }

    hurt_sound = Mix_LoadWAV("../assets/sounds/hurt.wav");
    if (!hurt_sound)
    {
        std::cerr << "Failed to load hurt sound: " << Mix_GetError() << std::endl;
    }

    explosion_sound = Mix_LoadWAV("../assets/sounds/explosion.wav");
    if (!explosion_sound)
    {
        std::cerr << "Failed to load explosion sound: " << Mix_GetError() << std::endl;
    }

    score_sound = Mix_LoadWAV("../assets/sounds/score.wav");
    if (!score_sound)
    {
        std::cerr << "Failed to load score sound: " << Mix_GetError() << std::endl;
    }

    pause_sound = Mix_LoadWAV("../assets/sounds/pause.wav");
    if    (!pause_sound)
    {
        std::cerr << "Faild to load pause sound: " << Mix_GetError() << std::endl;
    }
    
    
    // Load background music
    background_music = Mix_LoadMUS("../assets/sounds/marios_way.mp3");
    if (!background_music)
    {
        std::cerr << "Failed to load background music: " << Mix_GetError() << std::endl;
    }

    return true;
}

void AudioManager::play_jump_sound()
{
    if (jump_sound)
    {
        Mix_PlayChannel(-1, jump_sound, 0);
    }
}

void AudioManager::play_hurt_sound()
{
    if (hurt_sound)
    {
        Mix_PlayChannel(-1, hurt_sound, 0);
    }
}

void AudioManager::play_explosion_sound()
{
    if (explosion_sound)
    {
        Mix_PlayChannel(-1, explosion_sound, 0);
    }
}

void AudioManager::play_score_sound()
{
    if (score_sound)
    {
        Mix_PlayChannel(-1, score_sound, 0);
    }
}

void AudioManager::play_pause_sound()
{
    if (pause_sound)
    {
        Mix_PlayChannel(-1, pause_sound, 0);
    }
}


void AudioManager::play_background_music()
{
    if (background_music)
    {
        Mix_PlayMusic(background_music, -1);
        is_music_playing = true;
    }
}

void AudioManager::stop_background_music()
{
    Mix_HaltMusic();
    is_music_playing = false;
}


void AudioManager::set_volume(int volume)
{
    // Clamp volume between 0 and 128 (SDL_mixer max)
    if (volume < 0)
    {
        volume = 0;
    }
    else if (volume > 128)
    {
        volume = 128;
    }

    Mix_Volume(-1, volume - 30); // Set volume for all channels
    Mix_VolumeMusic(volume); // Set volume for music
}
