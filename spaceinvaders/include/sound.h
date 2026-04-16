#include <SDL2/SDL_mixer.h>

class Sound
{
public:
    Sound();
    ~Sound();

    bool initSoundSystem();
    void createSoundResource();
    void playCum();
    void playMourn();
    void playBGM();
    void clean();

private:
    Mix_Music *bgm;
    Mix_Chunk *mourn;
    Mix_Chunk *cum;
};