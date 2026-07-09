#include "../lib/game.h"

#include <iostream>

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

    running = true;
    return true;
}

void Game::clean()
{
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

    while (running)
    {
        handle_Input();
        process_Logic();
        render();
    }

    clean();
}

void Game::handle_Input()
{
    int event_result = sdl_manager.read_Event();

    if (event_result == 1)
    {
        running = false;
    }
    else if (event_result == 2)
    {
        running = false;
    }
}

void Game::process_Logic()
{
}

void Game::render()
{
    sdl_manager.setup_Window();
    sdl_manager.draw_Everything();
}

bool Game::is_Running() const
{
    return running;
}
