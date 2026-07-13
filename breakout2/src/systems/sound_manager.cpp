#include "../../lib/systems/sound_manager.h"

#include <iostream>

SoundManager::SoundManager()
    : initialized(false)
{
}

SoundManager::~SoundManager()
{
    clean();
}

// connect to sound handler 
bool SoundManager::init()
{
    if (initialized)
        return true;

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        std::cerr << "Mix_OpenAudio failed: " << Mix_GetError() << std::endl;
        return false;
    }

    initialized = true;
    return true;
}

bool SoundManager::loadSound(const std::string &name, const std::string &path)
{
    // if connect with Sound handler successfully 
    if (!initialized && !init()) 
        return false;

    // load the sound using the path 
    // game provide
    // make it become "pure C string"
    Mix_Chunk *chunk = Mix_LoadWAV(path.c_str());
    if (chunk == nullptr)
    {
        std::cerr << "Mix_LoadWAV failed for '" << path << "': " << Mix_GetError() << std::endl;
        return false;
    }

    // store chunk in the map
    // as many as you want
    // not need to create each chunk mannually
    sounds[name] = chunk;
    return true;
}

void SoundManager::playSound(const std::string &name)
{
    // find the sound pointer in the map
    auto it = sounds.find(name);
    // if end the map and can't find anything
    // return nothing.
    if (it == sounds.end())
        return;
    
    Mix_PlayChannel(-1, it->second, 0);
}

void SoundManager::clean()
{
    // go to the map 
    // clear everything from start to end
    for (auto &entry : sounds)
    {
        if (entry.second)
        {
            Mix_FreeChunk(entry.second);
            entry.second = nullptr;
        }
    }
    sounds.clear();

    // turn off sound handler
    if (initialized)
    {
        Mix_CloseAudio();
        initialized = false;
    }
}
