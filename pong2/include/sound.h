#pragma once
#include <SDL2/SDL_mixer.h>

class Sound
{
    public:

    Sound();
    ~Sound();

    void clean();

    bool initSoundSys();
    void loadSound();
    
    void playHit();
    void playWall();
    void playMusic();

    Mix_Chunk *hit;
    Mix_Chunk *wall;
    Mix_Music *bgm;

};