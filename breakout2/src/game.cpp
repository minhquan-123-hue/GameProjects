#include "../lib/game.h"
#include "../lib/states/menu.h"
#include <../lib/states/playstate.h>

#include <iostream>
#include <string>

// find and replace this var name
#ifndef BREAKOUT2_ASSETS_DIR
#define BREAKOUT2_ASSETS_DIR "../"
#endif

Game::Game()
    : running(false)
{
}

Game::~Game()
{
    clean();
}

bool Game::init()
{
    if (!initSdl())
    {
        return false;
    }

    if (!initWin())
    {
        clean();
        return false;
    }

    if (!initRen())
    {
        clean();
        return false;
    }

    if (!initFontMgr())
    {
        clean();
        return false;
    }

    if (!initGraphicMgr())
    {
        clean();
        return false;
    }

    if (!initSoundMgr())
    {
        clean();
        return false;
    }

    if (!loadAssets())
    {
        clean();
        return false;
    }

    initMenuState();
    running = true;
    return true;
}

bool Game::initSdl()
{
    return sdl_manager.init();
}

bool Game::initWin()
{
    return sdl_manager.create_Window();
}

bool Game::initRen()
{
    return sdl_manager.create_Renderer();
}

bool Game::initFontMgr()
{
    return font_manager.init();
}

bool Game::initGraphicMgr()
{
    return graphic_manager.init();
}

bool Game::initSoundMgr()
{
    if (!sound_manager.init())
        return false;

    const std::string assets_dir = BREAKOUT2_ASSETS_DIR;

    // if it connect sound handler succesfully , load sound then use to play later.
    return sound_manager.loadSound("no-select", assets_dir + "/sounds/no-select.wav")
        && sound_manager.loadSound("select", assets_dir + "/sounds/select.wav");
}

bool Game::loadAssets()
{
    // font 
    const std::string assets_dir = BREAKOUT2_ASSETS_DIR;

    if (!font_manager.loadFont(assets_dir + "/fonts/font.ttf", 48))
    {
        return false;
    }

    if (!graphic_manager.loadIMG(
            sdl_manager.renderer,
            "background",
            assets_dir + "/graphics/background.png"))
    {
        return false;
    }
    
    if (!graphic_manager.loadIMG(
            sdl_manager.renderer,
            "paddle",
            assets_dir + "/graphics/breakout.png"))
    {
        return false;
    }
    
    return true;
}

// what the fuck is this ? 
void Game::initMenuState()
{
    Menu *menu = new Menu();
    
    menu->setRenderer(sdl_manager.renderer); // this is access mem fun throught pointer 
    menu->setManagers(&font_manager, &graphic_manager);
    menu->setSoundManager(&sound_manager);

    // statemachine change state 
    state_machine.changeState(menu);
}

void Game::initPlayState()
{
    PlayState* play = new PlayState(&graphic_manager);

    state_machine.changeState(play);
}

void Game::clean()
{
    // destroy state machine and managers
    state_machine.changeState(nullptr);
    sound_manager.clean();
    graphic_manager.clean();
    font_manager.clean();
    sdl_manager.destroy();

    running = false;
}

void Game::run()
{
    if (!init())
    {
        std::cerr << "Game failed to initialize." << std::endl;
        return;
    }

    Uint32 preTime = SDL_GetTicks();
    while (is_Running())
    {
        Uint32 curTime = SDL_GetTicks();
        float deltaTime = (curTime - preTime) / 1000.0f;
        preTime = curTime;

        handle_Input();
        process_Logic(deltaTime);
        render_frame();
    }

    clean();
}

void Game::handle_Input()
{
    SDL_Event ev;
    while (sdl_manager.pollEvent(ev))
    {
        if (ev.type == SDL_QUIT)
        {
            running = false;
            return;
        }

        // trả lại state object hiện tại là gì 
        // và sau đó using -> thông qua con trỏ để truy cập member function
        State *cur = state_machine.getCurrent(); 
        if (cur)
            cur->handleInput(ev);
    }
}

void Game::process_Logic(float dt)
{
    State *cur = state_machine.getCurrent();
    if (cur)
        cur->update(dt);

    // trả lại cái đoạn văn bản[vị trí vẽ]
    // để hàm cập nhật thay đổi dữ liệu cần thiết.
    Menu *menu = dynamic_cast<Menu *>(state_machine.getCurrent());
    if (menu)
    {
        int r = menu->getResult();
        if (r != -1)
        {
            if (r == 0)
            {                
                initPlayState();
                return;   
            }
            else if (r == 1)
            {
                // High Score selected - placeholder behaviour
                running = false;
            }
        }
    }
}

void Game::render_frame()
{
    sdl_manager.setup_Window();

    State *cur = state_machine.getCurrent();
    if (cur)
        cur->render(sdl_manager.renderer);

    sdl_manager.draw_Everything();
}

bool Game::is_Running() const
{
    return running;
}
