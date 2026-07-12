#include "../../lib/systems/graphic_manager.h"

#include <SDL2/SDL_image.h>
#include <iostream>

// khai báo biến chưa dùng 
GraphicManager::GraphicManager()
    : background(nullptr)
{
}

// dọn dẹp ảnh khi dùng xong
GraphicManager::~GraphicManager()
{
    clean();
}

// khởi tạo hệ thống xử lý hình ảnh png 
bool GraphicManager::init()
{
    int flags = IMG_INIT_PNG;
    if ((IMG_Init(flags) & flags) != flags)
    {
        std::cerr << "IMG_Init failed: " << IMG_GetError() << std::endl;
        return false;
    }
    return true;
}

// tải ảnh nền lên (bg) và trong đó có chứa
// toàn bộ các điểm ảnh của hình vẽ 
// nhét nó vào vram để lát vẽ cho nhanh
// chỉ có vị trí + kích thước là mình quyết định sau
bool GraphicManager::loadBackground(SDL_Renderer *renderer, const std::string &path)
{
    if (renderer == nullptr)
        return false;

    SDL_Surface *surf = IMG_Load(path.c_str());
    if (surf == nullptr)
    {
        std::cerr << "IMG_Load failed for '" << path << "': " << IMG_GetError() << std::endl;
        return false;
    }

    background = SDL_CreateTextureFromSurface(renderer, surf);
    SDL_FreeSurface(surf);

    if (background == nullptr)
    {
        std::cerr << "CreateTextureFromSurface failed: " << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}

// gọi hàm constant để nhận lại dữ liệu để đọc
// chứ không thể truy cập trực tiếp như là một biến thành viên
SDL_Texture *GraphicManager::getBackground() const
{
    return background;
}

// dọn dẹp khi dùng xong tài nguyên
// trả lại "không gian" cho ram 
void GraphicManager::clean()
{
    if (background != nullptr)
    {
        SDL_DestroyTexture(background);
        background = nullptr;
    }

    IMG_Quit();
}
