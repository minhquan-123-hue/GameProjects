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
    void renderScore();
    void renderHealth();
    void renderMenu();
    void renderWin();
    void renderGameOver();

    // 4. LOGIC ĐẶC BIỆT (hàm)
    void resetState();
    bool checkCollison(const SDL_Rect &ball, const SDL_Rect &brick);

    // 5. WINDOW / RENDER CONTEXT (môi trường sống)

    // những con trỏ để khởi tạo tài nguyên
    SDL_Window *window;     // cửa sổ
    SDL_Renderer *renderer; // bộ vẽ backend

    // 6. GAME OBJECTS (dữ liệu gameplay)
    // ----mouse----
    int mouseX; // store codirnate of the mouse
    int mouseY;

    // ---- platform ----
    float platformWidth;
    float platformHeight;
    float platformX;
    float platformY;
    float platformSpeed;

    // ---- ball ---
    // thay đổi tạo ball trực tiếp và 1 quả duy nhất thì , tạo ra struct + vector để chứa nhiều quả
    struct Ball
    {
        float x;
        float y;
        float velX;
        float velY;
        float radius;
        bool alive;
    };

    std::vector<Ball> balls;

    void initBall();
    void DrawFilledCircle(SDL_Renderer *renderer, int ballCenterX, int ballCenterY, int ballradius);

    // ---- frame: health, point ----
    float frameWidth;
    float frameHeight;
    float frameX;
    float frameY;

    // ---- brick ----
    struct Brick
    {
        SDL_Rect rect;
        bool alive;
        int row;
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
    float windowLeft;
    float windowRight;
    float windowUp;
    float windowDown;

    // 7. RULE & STATE FLAGS

    int points;
    int hitwall;

    SDL_Event event;

    bool is_running;
    bool is_movingLeft;
    bool is_movingRight;
    bool is_ballFrozen;
    bool is_platformFrozen;
    bool is_multiplied;

    Screen currentScreen;

    // 8. TEXT / FONT

    TTF_Font *font;

    SDL_Texture *createTextTexture(const std::string &text, SDL_Rect &rect);

    SDL_Texture *textureMenu;
    SDL_Texture *textureGameover;
    SDL_Texture *textureWin;

    SDL_Rect rectMenu;
    SDL_Rect rectGameOver;
    SDL_Rect rectWin;
    void createFontResource();

    // con trỏ chỉ tới handle cho tài nguyên nằm trong VRAM + struct mô ta dữ liệu hình dáng của đối tượng
    SDL_Texture *textureScore;
    SDL_Rect rectScore;

    SDL_Texture *textureHealth;
    SDL_Rect rectHealth;

    void updateUIText();

    // 9. AUDIO
    Mix_Chunk *sfxbounce;
    Mix_Chunk *sfxhitBrick;
    Mix_Chunk *sfxloseHealth;
    Mix_Chunk *sfxwin;

    Mix_Music *bgm;
    bool loadSound();

    // 10. CLEANUP (cái chết của chương trình)
    void cleanUp();
};