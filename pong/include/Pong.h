// các file khác mà dùng header này chỉ được phép include 1 lần
#pragma once

// dùng 2 thư viện (API) ngoài : tạo màn hình, âm thanh , text
// (API): bộ quy nói chuyện giữa các phần mềm => SDL nói chuyện với OS => driver => phần cứng: tính -> lưu -> tiêu
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
// làm việc với mảng động chuyên biệt cho text (tạo ra objecct)
#include <string>
// tạo ra mảng động từ class template
#include <vector>

// ------------------------------------------------------------
// Pong
// Quản lý toàn bộ vòng đời game: init → loop → shutdown
// ------------------------------------------------------------
class Pong
{
public:
    // -------- Lifecycle (bên ngoài chỉ cần biết chừng này) --------
    Pong();  // constructor : khởi tạo các tài nguyên (đi liền với object khi sinh ra) != khác với gắn
    ~Pong(); // destructor : hủy tài nguyên C++ sau khi ra khỏi scope của int main{} tức là dừng chương trình

    bool init(); // khởi tạo tạo tài nguyên
    void run();  // vòng lặp (gửi lệnh vẽ từng frame)

private:
    // ============================================================
    // 1. GAME STATE (xương sống)
    // ============================================================
    enum class Screen
    {
        MENU, // các lựa chọn: chơi 1 người hoặc 2 người
        ONE_PLAYER,
        TWO_PLAYER,
        GAMEOVER // game kết thúc khi thua
    };

    // tạo biến để so sánh hoặc gán để thay đổi trạng thái (Màn) game
    Screen currentScreen;

    // ============================================================
    // 2. CORE LOOP (chạy mỗi frame)
    // ============================================================

    // xử lý sự kiện di chuyển từ phím(giữ/nhấn): cho chơi game , và chuyển trạng thái
    // dùng cho cả xử lý va chạm với tường cho 2 chiếc vợt
    // dùng thời gian phụ thuộc phần cứng (khoảng 60 frame / giây) == 0.016ms (thời gian hoàn thành vẽ 1 frame) == thời gian vật di chuyển
    // xử dụng ẩn dụ : XE MÁY + CAMERA để tượng tượng cách vẽ của máy tính
    // thay đổi giá trị trong RAM (vị trị của vật)
    void handleEvents(float delta);
    // xử lý va chạm cho bóng: với object(vợt) , với tường
    // thay đổi giá trị trong RAM (vị trí của bóng)
    void update(float delta);
    // gửi lệnh vẽ cho GPU (đọc state trong ram hoặc VRAM)
    void render();

    bool running;

    // ============================================================
    // 3. RENDER THEO STATE
    // ============================================================
    void renderPaddleBall();
    void renderMiddleLine();
    void renderScore();

    // vẽ hai TEXT cho hai trạng thái màn : MENU và GAMEOVER
    void renderMenuTextVram();
    void renderGameOverTextVram();

    // ============================================================
    // 4. LOGIC ĐẶC BIỆT (không chạy mỗi frame)
    // ============================================================

    // tái thiết lập : điểm , vị trí, cờ
    void startGame(int direction);
    void resetBall(int direction);

    // ============================================================
    // 5. WINDOW / RENDER CONTEXT (môi trường sống)
    // ============================================================

    // con trỏ chứa tài nguyên : mà thương lượng được (nhờ OS hỏi) cho hệ thống window "tờ giấy để vẽ lên" , renderer:"cây bút" hay còn gọi là quyết định GPU hay CPU sẽ vẽ
    SDL_Window *window;
    SDL_Renderer *renderer;

    // kích thước màn hình
    int MinWindowW;
    int MaxWindowW;
    int MinWindowH;
    int MaxWindowH;

    // ============================================================
    // 6. GAME OBJECTS (dữ liệu gameplay)
    // ============================================================
    // ---- Ball ----
    int ballSize;
    float ballX;
    float ballY;
    float ballVelX;
    float ballVelY;

    // ---- Paddle ----
    int paddleW;
    int paddleH;
    float paddleLeftX;
    float paddleLeftY;
    float paddleRightX;
    float paddleRightY;
    float paddleSpeed;

    // ============================================================
    // 7. RULE & STATE FLAGS
    // ============================================================
    int leftScore;
    int rightScore;

    bool ballFrozen;
    bool paddleFroze;

    Uint32 delayGameOver;
    bool endDelay;

    // ============================================================
    // 8. TEXT / FONT (presentation, không đụng logic)
    // ============================================================
    TTF_Font *font; // tải font trên mạng về dùng

    SDL_Texture *menuText; // bitmap vram
    SDL_Texture *gameOverText;

    SDL_Rect menuTextBlock; // kich thuoc cua chữ
    SDL_Rect gameOverTextBlock;

    // hàm trả lại con trỏ chứa dữ liệu "ảnh" trong vram
    SDL_Texture *CreateTextTexture(const std::string &text,
                                   SDL_Rect &rect);

    // ============================================================
    // 9. AUDIO (giác quan – phản xạ của logic)
    // ============================================================

    SDL_AudioDeviceID audioDevice; // mã đại diện cho tài nguyên

    // cờ trạng thái khi mà va chạm để tạo âm thanh
    bool HitPaddleThisFrame;
    bool HitWallThisFrame;
    bool ScoreThisFrame;

    // nhưng biến thuộc về âm thanh
    struct Beep
    {
        float frequency;
        float phase;
        float loudness;
        float samplesRemaining;
    };

    // mảng động: object chứa nhiều object cùng kiểu , nằm liên tiếp trong RAM (kích thước, vị trí)
    std::vector<Beep> playingSounds;

    // hàm callback ,không phụ thuộc object Pong, ghi dữ liệu vào buffer
    static void fillAudioBuffer(void *userdata,
                                Uint8 *outputBuffer,
                                int bufferSize);

    // ============================================================
    // 10. CLEANUP (cái chết của chương trình)
    // ============================================================

    // trả lại tài nguyên (trong RAM/VRAM) của chương trình khi (dừng game )
    void cleanUp();
};
