#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class FontManager
{
public:
    // khởi tạo giá trị ban đầu để về sau làm việc cho an toàn 
    FontManager();
    // sau khi làm viêc với font xong giả tài nguyên lại 
    // RAM sạch còn làm việc khác 
    ~FontManager();

    // kết nối với hệ thống xử lý font của SDL 
    bool init();

    // tải font lên: gồm kích thước + kiểu vẽ
    bool loadFont(const std::string &path, int size);

    // từ font chữ được tải lên trong ram 
    // copy pixel [các điểm ảnh] vào trong vram tí vẽ cho nhanh
    SDL_Texture *createTextTexture(SDL_Renderer *renderer, const std::string &text, SDL_Color color);

    // dọn dẹp tài nguyên khi dùng xong 
    void clean();

private:
    // font chữ : mà trong đó công thức vẽ chữ.
    // một con trỏ chứa địa chỉ của 
    TTF_Font *font;
};