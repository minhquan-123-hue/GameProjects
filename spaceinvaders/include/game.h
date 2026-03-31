#pragma once                // mỗi file mà copy cái header này thì chỉ được 1 lần duy nhất
#include <SDL2/SDL.h>       // thư viên kết nối với OS
#include <SDL2/SDL_image.h> // thư viện cung cấp hàm xử lý ảnh .png
#include <vector>           // thư viện cung cấp std::vector<type>

// thư viện tự tạo
#include <dick.h>
#include <sperm.h>
#include <pussy.h>

class SpaceInvaders
{
public:
    SpaceInvaders();
    ~SpaceInvaders();

    bool init();
    void run();

private:
    // 1. GAME STATE

    // tách hàm trong init()
    bool connectVideoHandler();
    bool connectImageHandler();
    bool createWindow();
    bool createRenderer();
    bool loadPicture();

    // 2. CORE LOOP
    void handleEvents();
    void quitEvents();
    void playEvents();
    void updateSimulation();
    void handleCollision(); // BUG: va chạm pussy và sperm
    void renderFrame();

    // 5. WINDOW / RENDER CONTEXT (Môi trường sống)
    SDL_Window *window;
    SDL_Renderer *renderer;

    // OBJECT
    Dick dick;
    Sperm spermShady;
    Pussy pussyShady;

    // 7. RULE & STATE FLAGS
    SDL_Event event;
    bool isRunning;

    // giới hạn va chạm với tường
    int leftWall;
    int rightWall;
    int topWall;
    int bottomWall;

    // 10. CLEANUP (dọn tài nguyên )
    void cleanUp();
};