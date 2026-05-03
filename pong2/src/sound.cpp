#include <sound.h>
#include <iostream>

Sound::Sound():
hit(nullptr),
wall(nullptr),
bgm(nullptr)
{}

Sound::~Sound()
{
    clean();
}

void Sound::clean()
{
    if (hit)
    {
        Mix_FreeChunk(hit);
    }
    if (wall)
    {
        Mix_FreeChunk(wall);
    }
    if (bgm)
    {
        Mix_FreeMusic(bgm);
    }

    Mix_CloseAudio();
}

bool Sound::initSoundSys()
{
    int initResult = Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2,2048);

    if (initResult != 0)
    {
        std::cerr << "không khởi tạo được hê thống âm thanh" << std::endl;
        return false;
    }
    return true;
}

void Sound::loadSound()
{
    hit = Mix_LoadWAV("../assets/hit.wav");
    wall = Mix_LoadWAV("../assets/wall.wav");
    bgm = Mix_LoadMUS("../assets/music.mp3");

    if (!hit || !wall || !bgm)
    {
        std::cerr << "đường dẫn âm thanh có vấn đề" << std::endl;
    }
}

void Sound::playHit()
{
    Mix_VolumeChunk(hit,120);
    Mix_PlayChannel(-1,hit, 0);
}

void Sound::playWall()
{
    Mix_VolumeChunk(wall,120);
    Mix_PlayChannel(-1,wall,0);
}

void Sound::playMusic()
{
    Mix_PlayMusic(bgm,-1);
}