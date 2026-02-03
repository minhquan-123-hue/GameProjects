// giờ là đến bước tách file ra thành 3 file: 1 file chạy phần headers(tuyên bố chữ ký hàm trong class) , 1 file chạy các code chính , 1 file tạo object rồi chạy game
// giờ là dùng công cụ gì thì phải nhập khẩu vào bằng #include (để tí prepocessor nhét nó vào đây)
#pragma once
#include <SDL2/SDL.h>

class BreakOut
{
    // những hàm có thể gọi được bởi bên ngoài
public:
    // constructor: khởi tạo cách biến ngay đi cùng với thời điểm object sỉnh ra ?
    BreakOut();
    // destructor: trả tài nguyên cho RAM (những tài nguyên C++ dùng), sẽ được gọi khi mà int main ra khỏi phạm vi
    ~BreakOut();

    // hàm khởi tạo tài nguyên
    bool init();
    // vòng lặp cho game chạy
    void run();

    // chỉ có nội bộ mới có thể gọi được
private:
    // 1.GAME STATE : xương sống
    // 2.CORE LOOP: chạy mỗi frame

    // và tạo ra một nơi để xử lý "SỰ KIỆN" (phím , chuột ,...)
    void handleEvents();
    void update(float delta);
    void render();

    // 3. RENDER THEO STATE
    void renderPlatform();
    void renderBall();
    void renderBrick();
    void renderFrame();

    // 4. LOGIC ĐẶC BIỆT (hàm)

    // 5. WINDOW / RENDER CONTEXT (môi trường sống)

    // những con trỏ để khởi tạo tài nguyên
    SDL_Window *window;     // cửa sổ
    SDL_Renderer *renderer; // bộ vẽ

    // 6. GAME OBJECTS (dữ liệu gameplay)
    // ---- platform ----
    float platformWidth;
    float platformHeight;
    float platformX;
    float platformY;
    float platformSpeed;

    // ---- ball ---
    float ballSize;
    float ballX;
    float ballY;
    float ballVelX;
    float ballVelY;

    // ---- brick ----
    float brickWidth;
    float brickHeight;
    float brickX;
    float brickY;

    // ---- frame: health, point ----
    float frameWidth;
    float frameHeight;
    float frameX;
    float frameY;
    float healthSize;
    float pointSize;

    // ---- window size ----
    float windowMax;
    float windowMin;

    // 7. RULE & STATE FLAGS
    // điểm
    int points;
    // mạng
    int health;
    // tạo một đối tượng lưu sự kiện của OS đưa cho SDL
    SDL_Event event;

    bool is_running;

    bool is_movingLeft;
    bool is_movingRight;

    // dừng chương trình khi chiến thắng || thua
    bool is_ballFrozen;
    bool is_platformFrozen;

    // 8. TEXT / FONT

    // 9. AUDIO

    // 10. CLEANUP (cái chết của chương trình)
    void cleanUp();
};