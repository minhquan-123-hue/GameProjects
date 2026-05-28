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
    // systems
    bool has_sdlm = sdl_manager.init();
    bool has_imgm = img_manager.init(sdl_manager.renderer);
    
    // entities
    bg.init(sdl_manager.w_size);

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
    bg.process_logic(dt);
}

void Game::render_frame()
{
    sdl_manager.setup_window();

    // draw bg
    SDL_RenderCopy(sdl_manager.renderer , img_manager.bg, nullptr, &bg.rect);

    sdl_manager.draw_everything();
}

