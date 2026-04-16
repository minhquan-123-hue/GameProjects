#include <SDL2/SDL_mixer.h>

class Sound
{
public:
    Sound();
    ~Sound();

    bool initSoundSys();
    void createSound();
    void playCum();
    void playMourn();
    void playBGM();

    void clean();

private:
    Mix_Music *bgm;
    Mix_Chunk *cum;
    Mix_Chunk *mourn;
};
