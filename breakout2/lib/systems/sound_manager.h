#pragma once

#include <map>
#include <string>

#include <SDL2/SDL_mixer.h>

class SoundManager
{
public:
    SoundManager();
    ~SoundManager();

    bool init();
    bool loadSound(const std::string &name, const std::string &path);
    void playSound(const std::string &name);
    void clean();

private:
    bool initialized;
    std::map<std::string, Mix_Chunk *> sounds;
};
