#include <background.h>
#include <iostream>

Background::Background(): background_Texture(nullptr){}
Background::~Background()
{
    clean();
}

void Background::clean()
{
    if (background_Texture)
    {
        SDL_DestroyTexture(background_Texture);
    }

    IMG_Quit();
}

bool Background::init(SDL_Renderer *renderer)
{
    bool has_image_handler = image_Handler();
    bool has_path = connect_Path(renderer);
    create();

    if (!has_image_handler || !has_path)
    {
        return false;
        std::cerr << "khởi tạo background không thành công" << std::endl;
    }

    return true;
}

void Background::update(float dt)
{
    
}

void Background::render(SDL_Renderer *renderer)
{
    SDL_RenderCopy(renderer,background_Texture, nullptr, &coor.rect);
}

bool Background::image_Handler()
{
    int initResult = IMG_Init(IMG_INIT_PNG);

    if (initResult == 0)
    {
        std::cerr << "không khởi tạo được hệ thống xử lý ảnh" << std::endl;
        return false;
    }
    return true;
}

bool Background::connect_Path(SDL_Renderer *renderer)
{
    background_Texture = IMG_LoadTexture(renderer, "../assets/background.png");

    if (background_Texture == nullptr)
    {
        std::cerr << "không tải được ảnh nền lên" << std::endl;
        return false;
    }
    return true;
}

void Background::create()
{
    coor.rect.x = 0;
    coor.rect.y = 0;
    coor.rect.w = 1000;
    coor.rect.h = 1000;
    
}