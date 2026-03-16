// viết lại cái màn hình đen đầu tiên

#pragma once // mỗi file mà copy cái header này thì chỉ được 1 lần duy nhất
// thư viện này cung cấp : toàn bộ code xử lý về cửa số , kết nối backend và các thư viện con ở dưới
#include <SDL2/SDL.h>
// thư viện này cung cấp phần xử lý : đọc được font tải về (kích thước, dáng ,...)
#include <SDL2/SDL_ttf.h>
// thư viện này cung cấp phần xử lý : đọc file âm thanh
#include <SDL2/SDL_mixer.h>
// thư viện này cấp cho ta một cái gọi là class template (khuôn đúc kiểu "bê tông" có sẵn thành class dùng được)
#include <SDL2/SDL_image.h>
// cho phép ta tạo mảng động để chứa 1 kiểu với số lượng nhiều
#include <vector>
#include <string>

// tạo bản thiết kế kiểu dáng và hành vi cho đối tượng
class SpaceInvaders
{
public:
    SpaceInvaders();
    ~SpaceInvaders();

    bool init();
    void run();

private:
    // 1. GAME STATE

    //  dùng lại 4 trạng thái game từ BreakOut

    enum class Screen
    {
        MENU,
        PLAYING,
        GAMEOVER,
        WIN

    };
    // TODO: cái tuyên bố này đã tạo ra gì trong bộ nhớ chưa ?
    // TODO: vậy cái biến này currentScreen là gì ? nó có phải là một enum không ? hay nó là tên của một class , và class này chứa dữ liệu kiểu enum ?
    Screen currentScreen;
    // 2. CORE LOOP
    void handleEvents();
    void updateSimulation();
    void renderFrame();

    // 5. WINDOW / RENDER CONTEXT (Môi trường sống)
    SDL_Window *window;
    SDL_Renderer *renderer;

    // Object
    struct Ship
    {
        SDL_Rect rect;
        float speed;
    };
    Ship ship;
    SDL_Texture *shipTexture; // đây là một họa tiết nằm trong vram , nhưng mà SDL chỉ trả lại con trỏ cho ta , và nó chỉ đến một struct chứa 1 con trỏ chỉ tới dữ liệu nằm trong vram thật

    // 7. RULE & STATE FLAGS
    SDL_Event event;
    bool isRunning;

    // 10. CLEANUP (dọn tài nguyên )
    void cleanUp();
};