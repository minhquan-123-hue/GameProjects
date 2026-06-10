#pragma once
#include <SDL2/SDL_mixer.h>
#include <string>

class AudioManager
{
    public:

    AudioManager();

    void destroy();

    bool init();

    // Play sound effects
    void play_jump_sound();
    void play_hurt_sound();
    void play_explosion_sound();
    void play_score_sound();
    void play_pause_sound();

    // Music control
    void play_background_music();
    void stop_background_music();
    

    // Volume control
    void set_volume(int volume); // 0-128

    private:

    // Sound effects
    Mix_Chunk *jump_sound;
    Mix_Chunk *hurt_sound;
    Mix_Chunk *explosion_sound;
    Mix_Chunk *score_sound;
    Mix_Chunk *pause_sound;

    // Background music
    Mix_Music *background_music;

    // Flag to track if music is playing
    bool is_music_playing;
};
