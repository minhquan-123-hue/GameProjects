#pragma once
#include <systems/sdl_manager.h>
#include <systems/font_manager.h>
#include <systems/graphic_manager.h>
#include <states/statemachine.h>

class Game
{
public:
    Game();
    ~Game();

    bool init();
    void clean();
    void run();

    void handle_Input();
    void process_Logic();
    void render_frame();

    bool is_Running() const;

private:
    // this is helper function make init easier to read
    bool initializeSdl();
    bool initializeWindow();
    bool initializeRenderer();
    bool initializeFontManager();
    bool initializeGraphicManager();
    bool loadAssets();
    void initializeMenuState();

    bool running;
    SDLManager sdl_manager;

    // Managers and states
    FontManager font_manager;
    GraphicManager graphic_manager;
    StateMachine state_machine;
};
