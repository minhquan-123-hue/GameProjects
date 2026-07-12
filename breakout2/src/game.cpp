#include "../lib/game.h"
#include "../lib/states/menu.h"

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
    if (!initializeSdl())
    {
        return false;
    }

    if (!initializeWindow())
    {
        clean();
        return false;
    }

    if (!initializeRenderer())
    {
        clean();
        return false;
    }

    if (!initializeFontManager())
    {
        clean();
        return false;
    }

    if (!initializeGraphicManager())
    {
        clean();
        return false;
    }

    if (!loadAssets())
    {
        clean();
        return false;
    }

    initializeMenuState();
    running = true;
    return true;
}

bool Game::initializeSdl()
{
    return sdl_manager.init();
}

bool Game::initializeWindow()
{
    return sdl_manager.create_Window();
}

bool Game::initializeRenderer()
{
    return sdl_manager.create_Renderer();
}

bool Game::initializeFontManager()
{
    return font_manager.init();
}

bool Game::initializeGraphicManager()
{
    return graphic_manager.init();
}

bool Game::loadAssets()
{
    // font 
    const std::string assets_dir = BREAKOUT2_ASSETS_DIR;

    if (!font_manager.loadFont(assets_dir + "/fonts/font.ttf", 48))
    {
        return false;
    }

    // png 
    return graphic_manager.loadBackground(sdl_manager.renderer, assets_dir + "/graphics/background.png");
}

// what the fuck is this ? 
void Game::initializeMenuState()
{
    Menu *menu = new Menu();
    
    menu->setRenderer(sdl_manager.renderer); // this is access mem fun throught pointer 
    menu->setManagers(&font_manager, &graphic_manager);

    // statemachine change state 
    state_machine.changeState(menu);
}

void Game::clean()
{
    // destroy state machine and managers
    state_machine.changeState(nullptr);
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

    while (is_Running())
    {
        handle_Input();
        process_Logic();
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

void Game::process_Logic()
{
    State *cur = state_machine.getCurrent();
    if (cur)
        cur->update();

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
                // Play selected - for now just exit the app (placeholder)
                running = false;
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
