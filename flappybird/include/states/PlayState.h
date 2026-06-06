#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include <string>
// systems
#include <systems/imagemanager.h>
#include <systems/FontManager.h>

// objects
#include <entities/bird.h>
#include <entities/pipepair.h>

class PlayState
{
    public:
    
    PlayState();

    void init();

    void input(SDL_Event &event);
    void process_logic(float dt);

    void render(SDL_Renderer *renderer , IMGManager &img_manager, FontManager &font_manager);

    // HELPER FUNCTION
    void spawn(float dt);
    void move(float dt);
    void remove();
    bool collide();
    int score(SDL_Renderer *renderer, FontManager &font_manager);

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