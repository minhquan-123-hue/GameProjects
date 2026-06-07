#pragma once
#include <vector>

// systems
#include <systems/sdlmanager.h>
#include <systems/imagemanager.h>
#include <systems/FontManager.h>
#include <systems/AudioManager.h>

// entities
#include <entities/background.h>
#include <entities/ground.h>

// state machine
#include <states/StateMachine.h>

class Game
{
    public:

    Game();
    ~Game();

    bool init();
    void run();

    private:

    // systems 
    SDLManager sdl_manager;
    IMGManager img_manager;
    FontManager font_manager;
    AudioManager audio_manager;

    // state machine
    StateMachine state_machine;

    // entities
    BackGround bg;
    Ground ground;

    void handle_input();
    void process_logic(float dt);
    void render_frame();


    // flag for loop
    bool is_running;
    
};