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

    bool has_path = connect_Path(renderer);
    create();

    if (!has_path)
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
    // API này gửi lệnh vẽ 
    SDL_RenderCopy(renderer,background_Texture, nullptr, &coor.rect);
}


bool Background::connect_Path(SDL_Renderer *renderer)
{
    // API đọc dữ liệu hình ảnh , và lưu thành hình vẽ hoàn chỉnh dựa vào meta + pixel 
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