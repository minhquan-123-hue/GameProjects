#include <states/PlayState.h>
#include <algorithm>

PlayState::PlayState():
spawn_timer(0.0f),
ct(0.0f),
point(0),
play_text("Point: "),
is_collided(false)
{}

void PlayState::init()
{
    bird.init();

    // don't create pipepairs here 
}

void PlayState::input(SDL_Event &event)
{
    bird.input(event);
}

void PlayState::process_logic(float dt)
{

    bird.process_logic(dt);

    // pipepairs
    spawn(dt);
    move(dt);
    remove();
    collide();
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

    if (ct >= 3.0f)
    {
        PipePair pair;

        pair.init(-200); // temporary value

        pipepairs.emplace_back(pair);

        ct = 0.0f;
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

bool PlayState::collide()
{
    for (auto &pair : pipepairs)
    {
        if (bird.collide(pair.top_pipe) || bird.collide(pair.bottom_pipe))
        {
            is_collided = true; // hit the pipe 
        }
    }

    if (bird.rect.y > 1000 - bird.rect.h)
    {
        is_collided = true; // hit the ground 
    }

    return is_collided;
}

int PlayState::score(SDL_Renderer *renderer , FontManager &font_manager)
{
    for (auto &pair : pipepairs)
    {
        if (pair.is_passed == false && pair.top_pipe.rect.x + pair.top_pipe.rect.w < bird.rect.x && pair.bottom_pipe.rect.x + pair.bottom_pipe.rect.w < bird.rect.x)
        {
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
    spawn_timer = 0.0f;

    // reset bird position and velocity
    bird.init();
    bird.velY = 0.0f;

    // remove any existing pipes
    pipepairs.clear();
}