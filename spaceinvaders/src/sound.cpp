#include <sound.h>
#include <iostream>

Sound::Sound() : bgm(nullptr),
                 mourn(nullptr),
                 cum(nullptr)
{
}

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
    if (mourn)
    {
        Mix_FreeChunk(mourn);
    }
    if (cum)
    {
        Mix_FreeChunk(cum);
    }

    Mix_CloseAudio();
    Mix_Quit();
}

bool Sound::initSoundSystem()
{
    int hasAudio = Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

    if (hasAudio == -1)
    {
        std::cout << "SDL_mixer lỗi: " << Mix_GetError() << std::endl;
        return false;
    }
    return true;
}

void Sound::createSoundResource()
{
    bgm = Mix_LoadMUS("../assets/bgm.mp3");

    mourn = Mix_LoadWAV("../assets/mourn.wav");
    cum = Mix_LoadWAV("../assets/cum.wav");

    if (!bgm || !mourn || !cum)
    {
        std::cerr << "lỗi load âm thanh: " << Mix_GetError() << std::endl;
    }
}

void Sound::playBGM()
{
    // -1 loop forever
    Mix_PlayMusic(bgm, -1);
    Mix_VolumeMusic(64);
}

void Sound::playMourn()
{
    // -1 SDL tự chọn kênh channel phát
    // 0 là không lặp lại
    Mix_PlayChannel(-1, mourn, 0);
    Mix_VolumeChunk(mourn, 120);
}

void Sound::playCum()
{
    Mix_PlayChannel(-1, cum, 0);
    Mix_VolumeChunk(cum, 120);
}