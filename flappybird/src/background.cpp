#include <background.h>
#include <iostream>
#include <cmath>

Background::Background(): background_texture(nullptr),
                        speed(120),
                        RESET_POINT(1000)
{}
Background::~Background()
{
    clean();
}

void Background::clean()
{
    if (background_texture)
    {
        SDL_DestroyTexture(background_texture);
    }

    IMG_Quit();
}

bool Background::init(SDL_Renderer *renderer)
{
    create_Texture(renderer);

    return true;
}

void Background::update(float dt)
{
    coor.rect.x += -speed * dt;
    
    // tái thiết lập vị trí
    std::cout << "BG width: " << coor.rect.x << std::endl;
    if (coor.rect.x <= RESET_POINT)
    {
        coor.rect.x = coor.rect.x % RESET_POINT;
    }
}

void Background::render(SDL_Renderer *renderer)
{
    // API này gửi lệnh vẽ 
    SDL_RenderCopy(renderer,background_texture, nullptr, &coor.rect);
}


bool Background::create_Texture(SDL_Renderer *renderer)
{
    SDL_Surface *background_surface = IMG_Load("../assets/background_lab.png");

    if (!background_surface)
    {
        std::cerr << "không tạo được surface[chứa metadata + pixel]" << std::endl;
        return false;
    }

    background_texture = SDL_CreateTextureFromSurface(renderer, background_surface);

    if (!background_texture)
    {
        std::cerr << "pixel của BG không copy được vào VRAM" << std::endl;
        return false;
    }

    float width = (*background_surface).w;
    
    std::cout << "BG width: " << width << std::endl;
    coor.rect.w = 2000;
    coor.rect.h = 1000;
    coor.rect.x = 0;
    coor.rect.y = 0;

    SDL_FreeSurface(background_surface);
    return true;
}