#include <sound.h>
#include <iostream>

Sound::Sound() : bgm(nullptr),
                 cum(nullptr),
                 mourn(nullptr) {}

Sound::~Sound()
{
    clean();
}

void Sound::clean()
{
    if (bgm)
    {
        Mix_FreeMusic(bgm);
    }

    if (cum)
    {
        Mix_FreeChunk(cum);
    }

    if (mourn)
    {
        Mix_FreeChunk(mourn);
    }

    Mix_CloseAudio();
    Mix_Quit();
}

bool Sound::initSoundSys()
{
    int hasAudio = Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

    if (hasAudio == -1)
    {
        std::cerr << "không liên được với chương trình xử lý âm thanh" << std::endl;
        return false;
    }
    return true;
}

void Sound::createSound()
{
    bgm = Mix_LoadMUS("../assets/bgm.mp3");
    cum = Mix_LoadWAV("../assets/cum.wav");
    mourn = Mix_LoadWAV("../assets/mourn.wav");

    if (!bgm || !cum || !mourn)
    {
        std::cerr << "các file âm thanh không tải lên thành công" << std::endl;
    }
}

void Sound::playCum()
{
    // -1 tự chọn chọn channel
    // 0 là không lặp
    Mix_PlayChannel(-1, cum, 0);
    Mix_VolumeChunk(cum, 120);
}

void Sound::playMourn()
{
    Mix_PlayChannel(-1, mourn, 0);
    Mix_VolumeChunk(mourn, 120);
}

void Sound::playBGM()
{
    Mix_PlayMusic(bgm, -1);
    Mix_VolumeMusic(64);
}