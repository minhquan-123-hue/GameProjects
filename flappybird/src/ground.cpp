#include <ground.h>
#include <iostream>

Ground::Ground(): ground_texture(nullptr){}
Ground::~Ground()
{
    clean();
}

void Ground::clean()
{
    if (ground_texture)
    {
        SDL_DestroyTexture(ground_texture);
    }

}

bool Ground::init(SDL_Renderer *renderer, int down_win, int right_win)
{

    bool has_image = open_Path(renderer);
    create(down_win,right_win);

    if (!has_image)
    {
        std::cerr << "không tạo được object ground" << std::endl;
        return false;
    }
    return true;
}

void Ground::update(float dt)
{

}

void Ground::render(SDL_Renderer *renderer)
{
    SDL_RenderCopy(renderer, ground_texture , nullptr , &coor.rect);
}

bool Ground::open_Path(SDL_Renderer *renderer)
{
    ground_texture = IMG_LoadTexture(renderer, "../assets/ground.png");

    if (!ground_texture)
    {
        std::cerr << "không tạo được ảnh trong VRAM của ground_texture" << std::endl;
        return false;
    }
    return true;
}

void Ground::create(int down_win,int right_win)
{
    coor.rect.x = 0;
    coor.rect.y = down_win - 100;
    coor.rect.w = 1000;
    coor.rect.h = 100;
}