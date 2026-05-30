#include <iostream>
#include <game.h>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <cmath>

Game::Game():
is_running(false),
spawn_timer(0.0f)
{}


Game::~Game()
{
    sdl_manager.destroy();
    img_manager.destroy();
}

bool Game::init()
{
    // random machine
    srand(time(NULL));

    // systems
    bool has_sdlm = sdl_manager.init();
    bool has_imgm = img_manager.init(sdl_manager.renderer);
    
    // entities
    bg.init(sdl_manager.w_size);
    ground.init(sdl_manager.w_size);
    bird.init();
    

    if (!has_sdlm || !has_imgm)
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

        bird.input(sdl_manager.event);
    }
}

void Game::process_logic(float dt)
{
    bg.process_logic(dt);
    ground.process_logic(dt);
    bird.process_logic(dt);

    pipes_movement(dt);
    pipes_collide();
}

void Game::render_frame()
{
    sdl_manager.setup_window();

    // draw parrallax effect
    SDL_RenderCopy(sdl_manager.renderer , img_manager.bg, nullptr, &bg.rect);

        // draw pipes
    for (auto &pipe : pipes)
    {
        SDL_RenderCopy(sdl_manager.renderer, img_manager.pipe, nullptr, &pipe.rect);
    }

    SDL_RenderCopy(sdl_manager.renderer, img_manager.ground,nullptr, &ground.rect);
    
    // draw bird
    SDL_RenderCopy(sdl_manager.renderer, img_manager.bird, nullptr, &bird.rect);


    sdl_manager.draw_everything();
}

void Game::pipes_movement(float dt)
{
    spawn_timer += dt;

    if (spawn_timer >= 2.5f)
    {
        Pipe pipe;

        pipe.init();

        pipes.emplace_back(pipe);

        std::cout << "pipe count: " << pipes.size() << std::endl;
        spawn_timer = 0;
    }

    for (auto &pipe : pipes)
    {
        pipe.process_logic(dt);
    }
}

void Game::pipes_collide()
{
    for (auto it = pipes.begin(); it != pipes.end();)
    {

        if (it->is_out)
        {
            it = pipes.erase(it);
        }
        else
        {
            ++it;
        }
    }
}