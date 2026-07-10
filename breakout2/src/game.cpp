#include "../lib/game.h"
#include "../lib/states/menu.h"

#include <iostream>
#include <string>

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
    if (!sdl_manager.init())
    {
        return false;
    }

    if (!sdl_manager.create_Window())
    {
        clean();
        return false;
    }

    if (!sdl_manager.create_Renderer())
    {
        clean();
        return false;
    }

    // Initialize managers
    if (!font_manager.init())
    {
        clean();
        return false;
    }

    const std::string assets_dir = BREAKOUT2_ASSETS_DIR;

    // load bundled font
    if (!font_manager.loadFont(assets_dir + "/fonts/font.ttf", 48))
    {
        clean();
        return false;
    }

    if (!graphic_manager.init())
    {
        clean();
        return false;
    }

    // load background
    graphic_manager.loadBackground(sdl_manager.renderer, assets_dir + "/graphics/background.png");

    // create menu state and set it as the initial state
    Menu *menu = new Menu();
    menu->setRenderer(sdl_manager.renderer);
    menu->setManagers(&font_manager, &graphic_manager);
    state_machine.changeState(menu);

    running = true;
    return true;
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
        render();
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

        // forward to current state if any
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

    // If current is Menu, check for selection
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

void Game::render()
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
