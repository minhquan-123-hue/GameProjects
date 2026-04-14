#pragma once                // mỗi file mà copy cái header này thì chỉ được 1 lần duy nhất
#include <SDL2/SDL.h>       // thư viên kết nối với OS
#include <SDL2/SDL_image.h> // thư viện cung cấp hàm xử lý ảnh .png
#include <vector>           // thư viện cung cấp std::vector<type>

// thư viện tự tạo
#include <dick.h>
#include <sperm.h>
#include <pussy.h>
#include <pussywater.h>
#include <score.h>

class SpaceInvaders
{
public:
    SpaceInvaders();
    ~SpaceInvaders();

    bool init();
    void run();

private:
    // 1. GAME STATE
    enum class Screen
    {
        MENU,
        PLAYING,
        GAMEOVER,
        WIN
    };

    Screen currentScreen;

    // tách hàm trong init()
    bool connectVideoHandler();
    bool connectImageHandler();
    bool createWindow();
    bool createRenderer();
    bool loadPicture();

    // 2. CORE LOOP
    // xử lý các sự kiện đầu vào
    void handleEvents();
    void quitEvents();
    void playEvents();
    void stateEvents();

    // cập nhật các biến theo input đầu vào, hoặc va chạm, dừng game khi thắng thua
    void updateSimulation();
    void updateCollision();
    void updateWin();
    void updateLose();
    void resetEntireSystem();

    // gửi lệnh vẽ
    void renderFrame();

    // 5. WINDOW / RENDER CONTEXT (Môi trường sống)
    SDL_Window *window;
    SDL_Renderer *renderer;

    // OBJECT
    Dick dick;
    Sperm spermShady;
    Pussy pussyShady;
    PussyWater pussyWater;
    ScoreUI scoreUI;

    // 7. RULE & STATE FLAGS
    SDL_Event event;
    bool isRunning;

    // giới hạn va chạm với tường
    int leftWall;
    int rightWall;
    int topWall;
    int bottomWall;

    // điểm
    int score;
    int life;

    // 10. CLEANUP (dọn tài nguyên )
    void cleanUp();
};