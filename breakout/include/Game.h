// giờ là đến bước tách file ra thành 3 file: 1 file chạy phần headers(tuyên bố chữ ký hàm trong class) , 1 file chạy các code chính , 1 file tạo object rồi chạy game
// giờ là dùng công cụ gì thì phải nhập khẩu vào bằng #include (để tí prepocessor nhét nó vào đây)
#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <string>
#include <vector>

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

    // 4 TRẠNG THÁI CỦA GAME
    enum class Screen
    {
        MENU,
        PLAYING,
        GAMEOVER,
        WIN
    };

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
    void resetState();
    bool checkCollison(const SDL_Rect &ball, const SDL_Rect &brick);

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

    // ---- frame: health, point ----
    float frameWidth;
    float frameHeight;
    float frameX;
    float frameY;
    float healthSize;
    float pointSize;

    // ---- brick ----
    struct Brick
    {
        SDL_Rect rect;
        bool alive;
    };
    struct Size
    {
        float Width;
        float Height;
        float Y;
    };
    std::vector<Brick> bricks;
    void initBricks();

    // ---- window size ----
    float windowMax;
    float windowMin;

    // 7. RULE & STATE FLAGS

    // điểm
    int points;
    // mạng
    int hitwall;
    // tạo một đối tượng lưu sự kiện của OS đưa cho SDL
    SDL_Event event;
    bool is_running;
    bool is_movingLeft;
    bool is_movingRight;
    // dừng chương trình khi chiến thắng || thua
    bool is_ballFrozen;
    bool is_platformFrozen;
    // cờ 4 trạng thái của màn hình
    Screen currentScreen;

    // 8. TEXT / FONT

    // tạo một con trỏ chỉ tới file font mình tải trên mạng về để dùng làm font cho dự án , nhưng cách nó lấy nó và dùng như thế nào thì chưa biết
    TTF_Font *font;
    // tạo hàm biến dữ liệu bitmap trong RAM sang VRAM để ta vẽ lên màn hình
    SDL_Texture *createTextTexture(const std::string &text, SDL_Rect &rect);
    // 3 pointer chứa nội dung của khối văn bản
    SDL_Texture *textureMenu;
    SDL_Texture *textureGameover;
    SDL_Texture *textureWin;
    // tạo ra khối để vẽ chữ dựa theo kích thước
    SDL_Rect textMenu;
    SDL_Rect textGameover;
    SDL_Rect textWin;
    // tạo ra hàm để chứa "tài nguyên" khối chữ được tạo
    void createFontResource();

    // 9. AUDIO

    // tạo nhạc nền và hiệu ứng âm thanh va chạm

    Mix_Chunk *sfxHitwall;
    Mix_Chunk *sfxHitbrick;
    Mix_Chunk *sfxLose;
    Mix_Chunk *sfxWin;

    Mix_Music *backgroundMusic;

    bool loadSound();

    // 10. CLEANUP (cái chết của chương trình)
    void cleanUp();
};