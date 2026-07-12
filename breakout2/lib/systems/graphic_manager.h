#pragma once

#include <SDL2/SDL.h>
#include <string>

class GraphicManager
{
public:
    GraphicManager();
    ~GraphicManager();

    // khởi tạo hệ thống xử lý hình ảnh
    bool init();

    // tải ảnh nền lên bằng cách dùng đường dẫn của nó
    // ảnh tải lên có cả tất cả các điểm ảnh 
    bool loadBackground(SDL_Renderer *renderer, const std::string &path);

    // hàm này dùng để đọc dữ liệu từ hình nền
    // tức là các điêm ảnh 
    // nhưng không truy cập trực tiếp vào texture được cho an toàn
    SDL_Texture *getBackground() const;

    // Free resources and shutdown IMG.
    void clean();

private:
    SDL_Texture *background;
};