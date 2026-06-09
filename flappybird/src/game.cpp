#include <iostream>
#include <game.h>


Game::Game():
is_running(false)
{}


Game::~Game()
{
    sdl_manager.destroy();
    img_manager.destroy();
    font_manager.destroy();
    audio_manager.destroy();
}

bool Game::init()
{

    // systems
    bool has_sdlm = sdl_manager.init();
    bool has_imgm = img_manager.init(sdl_manager.renderer);
    bool has_fm = font_manager.init();
    bool has_am = audio_manager.init();

    // set volume
    audio_manager.set_volume(60);
    audio_manager.play_background_music();
    
    // entities
    bg.init(sdl_manager.w_size);
    ground.init(sdl_manager.w_size);
    

    // state machine
    state_machine.init(sdl_manager.renderer, font_manager);


    if (!has_sdlm || !has_imgm || !has_fm || !has_am)
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

        state_machine.input(sdl_manager.event, audio_manager);
    }
}

void Game::process_logic(float dt)
{   

    bg.process_logic(dt);
    ground.process_logic(dt);

    state_machine.process_logic(dt, sdl_manager.renderer, font_manager, audio_manager);
}

void Game::render_frame()
{
    sdl_manager.setup_window();

    bg.render(sdl_manager.renderer, img_manager.bg);
    state_machine.render(sdl_manager.renderer, img_manager, font_manager);
    ground.render(sdl_manager.renderer, img_manager.ground);


    sdl_manager.draw_everything();
}
