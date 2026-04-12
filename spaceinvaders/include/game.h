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

// tạo object riêng
#include <dick.h>
#include <sperm.h>
#include <pussy.h>
#include <pussywater.h>
#include <score.h>

// tạo bản thiết kế kiểu dáng và hành vi cho đối tượng
class SpaceInvaders
{
public:
    SpaceInvaders();
    ~SpaceInvaders();

    bool init();
    void run();

private:
    // tạo hàm phụ thuộc init():
    bool connectVideoHandler();
    bool connectImageHandler();
    bool createWindow();
    bool connectBackend();
    bool loadPicture();

    // 2. CORE LOOP
    void handleEvents();
    void quitEvents();
    void playEvents();
    void updateSimulation();
    void updateCollision();
    void renderFrame();

    // 5. WINDOW / RENDER CONTEXT (Môi trường sống)
    SDL_Window *window;
    SDL_Renderer *renderer;

    // Object

    Dick dick; // tạo object riêng biệt
    Sperm sperm;
    Pussy pussy;
    PussyWater pussyWater;
    ScoreUI scoreUI;

    // 7. RULE & STATE FLAGS
    SDL_Event event;
    bool isRunning;

    int leftWall;
    int rightWall;
    int topWall;
    int bottomWall;

    // biến điểm và mạng
    int life;
    int score;

    // 10. CLEANUP (dọn tài nguyên )
    void cleanUp();
};