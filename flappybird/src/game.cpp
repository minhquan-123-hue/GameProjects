#include <iostream>
#include <game.h>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <cmath>

Game::Game():
is_running(false),
spawn_timer(0.0f),
last_Y(0.0f),
is_collided(false)
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
    if (is_collided)
    {
        return ;
    }

    
    bg.process_logic(dt);
    ground.process_logic(dt);
    bird.process_logic(dt);

    pipepairs_movement(dt);
    pipepairs_remove();
    pipepairs_collide();
}

void Game::render_frame()
{
    sdl_manager.setup_window();

    // draw parrallax effect
    bg.render(sdl_manager.renderer, img_manager.bg);

        // draw pipes
    for (auto &pair : pipe_pairs)
    {
        pair.render(sdl_manager.renderer, img_manager.pipe);
    }

    ground.render(sdl_manager.renderer, img_manager.ground);
    
    // draw bird
    bird.render(sdl_manager.renderer, img_manager.bird);


    sdl_manager.draw_everything();
}

void Game::pipepairs_movement(float dt)
{
    spawn_timer += dt;

    if (spawn_timer >= 2.5f)
    {
        
        last_Y = std::max(-300,std::min((int(last_Y) + rand() % 100 - 50), -100));
        PipePair pair;

        pair.init(last_Y);

        pipe_pairs.emplace_back(pair);

        std::cout << "pipe count: " << pipe_pairs.size() << std::endl;
        spawn_timer = 0;
    }

    for (auto &pair : pipe_pairs)
    {
        pair.process_logic(dt);
    }
}

void Game::pipepairs_remove()
{
    auto It = std::remove_if(
        pipe_pairs.begin(),
        pipe_pairs.end(),
        [](PipePair &pair)
        {
            return pair.top_pipe.is_out || pair.bottom_pipe.is_out;
        }
    );

    pipe_pairs.erase(It, pipe_pairs.end());
}


void Game::pipepairs_collide()
{
    for (PipePair &pair : pipe_pairs)
    {
        if (bird.collide(pair.top_pipe) || bird.collide(pair.bottom_pipe))
        {
            is_collided = true;           
        }
    }
}