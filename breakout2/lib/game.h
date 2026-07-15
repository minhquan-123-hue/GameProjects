#pragma once
#include <systems/sdl_manager.h>
#include <systems/font_manager.h>
#include <systems/graphic_manager.h>
#include <systems/sound_manager.h>
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
    void process_Logic(float dt);
    void render_frame();

    bool is_Running() const;

private:
    // this is helper function make init easier to read
    bool initSdl();
    bool initWin();
    bool initRen();
    bool initFontMgr();
    bool initGraphicMgr();
    bool initSoundMgr();
    bool loadAssets();
    void initMenuState();
    void initPlayState();


    bool running;
    SDLManager sdl_manager;

    // Managers and states
    FontManager font_manager;
    GraphicManager graphic_manager;
    SoundManager sound_manager;
    StateMachine state_machine;
};
