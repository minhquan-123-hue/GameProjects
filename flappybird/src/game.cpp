#include <game.h>

Game::Game():
is_running(false)
{}


Game::~Game()
{
    sdl_manager.destroy();
}

bool Game::init()
{
    bool has_sdlm = sdl_manager.init();

    if (!has_sdlm)
    {
        return false;
    }

    is_running = true;
    return true;
}

void Game::run()
{
    Uint32 pt = SDL_GetTicks(); // return milisecond
    while(is_running)
    {
        Uint32 ct = SDL_GetTicks();
        float dt = (ct - pt) / 1000.0f; // convert to second 
        pt = ct;

        handle_input();
        process_logic(dt);
        render_frame();
    }
}

void Game::handle_input()
{
    while (sdl_manager.read_event())
    {
        if (sdl_manager.event.type == SDL_QUIT)
        {
            is_running = false;
        }
    }
}

void Game::process_logic(float dt)
{

}

void Game::render_frame()
{
    sdl_manager.setup_window();

    sdl_manager.draw_everything();
}

