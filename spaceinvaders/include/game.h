// viết lại cái màn hình đen đầu tiên

#pragma once
#include <SDL2/SDL.h>

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
    // 2. CORE LOOP
    void handleEvents();
    void updateSimulation();
    void renderFrame();
    // 3. CỜ
    bool isRunning;
    // tạo màn hình
    SDL_Window *window;
    SDL_Renderer *renderer;

    // dọn dẹp tài nguyên
    void cleanUp();
};