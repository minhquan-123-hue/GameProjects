#include <states/PlayState.h>
#include <iostream>
#include <algorithm> // std::max, std::min
#include <cstdlib>   // rand, srand
#include <ctime>     // time


PlayState::PlayState():
spawn_timer(0.0f),
ct(0.0f),
point(0),
play_text("Point: "),
is_collided(false),
last_y(0),
MAX_TIME_SPAWN(3.0f),
MIN_TIME_SPAWN(3.0f)
{}

void PlayState::init()
{
    srand(time(nullptr));

    spawn_timer = rand() % (int)MAX_TIME_SPAWN  + (int)MIN_TIME_SPAWN; // tạo thời gian cho cái cột đầu tiên 

    bird.init();

    // don't create pipepairs here 
}

void PlayState::input(SDL_Event &event, AudioManager &audio_manager)
{
    bird.input(event, audio_manager);
}

void PlayState::process_logic(float dt, AudioManager &audio_manager)
{

    bird.process_logic(dt);

    // pipepairs
    spawn(dt);
    move(dt);
    remove();
}

void PlayState::render(SDL_Renderer *renderer , IMGManager &img_manager, FontManager &font_manager)
{
    bird.render(renderer,img_manager.bird);
    
    for (auto &pair : pipepairs)
    {
        pair.render(renderer, img_manager.pipe);
    }

    SDL_RenderCopy(renderer,font_manager.play_texture, nullptr, &font_manager.play_rect);
}

void PlayState::spawn(float dt)
{
    ct += dt;
    
    if (ct >= spawn_timer) 
    {
        std::cout << "spawn_timer: " << spawn_timer << std::endl;

        int y = std::max(-600,std::min(last_y + rand() % 201 - 100, -200)); 

        last_y = y;

        PipePair pair;

        pair.init(y); // y position for top pipe

        pipepairs.emplace_back(pair);

        ct = 0.0f;

        spawn_timer = rand() % (int)MAX_TIME_SPAWN  + (int)MIN_TIME_SPAWN;
    }
}

void PlayState::move(float dt)
{
    for (auto &pair : pipepairs)
    {
        pair.process_logic(dt);
    }
}

void PlayState::remove()
{
    auto It = std::remove_if(
        pipepairs.begin(),
        pipepairs.end(),
        [](PipePair &pair)
        {
            return pair.top_pipe.is_out || pair.bottom_pipe.is_out;
        }
    );

    pipepairs.erase(It, pipepairs.end());
}

bool PlayState::collide(AudioManager &audio_manager)
{
    for (auto &pair : pipepairs)
    {
        if (bird.collide(pair.top_pipe) || bird.collide(pair.bottom_pipe))
        {
            audio_manager.play_hurt_sound();

            is_collided = true; // hit the pipe 
        }
    }

    if (bird.rect.y > 1000 - bird.rect.h)
    {
        audio_manager.play_explosion_sound();

        is_collided = true; // hit the ground 
    }

    return is_collided;
}

int PlayState::score(SDL_Renderer *renderer , FontManager &font_manager, AudioManager &audio_manager)
{
    for (auto &pair : pipepairs)
    {
        if (pair.is_passed == false && pair.top_pipe.rect.x + pair.top_pipe.rect.w < bird.rect.x && pair.bottom_pipe.rect.x + pair.bottom_pipe.rect.w < bird.rect.x)
        {
            audio_manager.play_score_sound();

            point += 1;
            pair.is_passed = true;
        }
    }
    font_manager.create_play(renderer,play_text,point);

    return point;
}

void PlayState::reset()
{
    // reset gameplay-related state so a new match starts clean
    is_collided = false;
    point = 0;
    ct = 0.0f;

    // reset bird position and velocity
    bird.init();
    bird.velY = 0.0f;

    // remove any existing pipes
    pipepairs.clear();
}