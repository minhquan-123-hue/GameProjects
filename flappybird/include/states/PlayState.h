#pragma once

//outsource 
#include <SDL2/SDL.h>

// built-in 
#include <vector>
#include <string>

// systems
#include <systems/imagemanager.h>
#include <systems/FontManager.h>
#include <systems/AudioManager.h>

// objects
#include <entities/bird.h>
#include <entities/pipepair.h>

class PlayState
{
    public:
    
    PlayState();

    void init();

    void input(SDL_Event &event, AudioManager &audio_manager);

    void process_logic(float dt, AudioManager &audio_manager);

    void render(SDL_Renderer *renderer , IMGManager &img_manager, FontManager &font_manager);

    // HELPER FUNCTION
    void spawn(float dt);
    void move(float dt);
    void remove();
    bool collide(AudioManager &aduio_manager);
    int score(SDL_Renderer *renderer, FontManager &font_manager, AudioManager &audio_manager);

    void reset();
    
    float spawn_timer;
    float ct;

    // objects
    Bird bird;

    std::vector<PipePair> pipepairs;

    int point;

    // flag

    bool is_collided;

    std::string play_text;
};