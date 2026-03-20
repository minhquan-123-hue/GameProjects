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
    void updateDickMovement();
    void updateDickCollision();
    void updateSpermMovement();
    void updateSpermCollision();
    void renderFrame();

    // 5. WINDOW / RENDER CONTEXT (Môi trường sống)
    SDL_Window *window;
    SDL_Renderer *renderer;

    // OBJECT

    struct Dick // con cu
    {
        SDL_Rect rect;
        float speed;
        SDL_Texture *texture;
    };
    Dick dick;

    void createDick();
    void renderDick();

    struct Sperm // đây là một struct : hộp nhóm nhiều kiểu dữ liệu vào trong
    {
        SDL_Rect rect; // struct con mô ta khối x,y,w,h
        float speed;   // tốc độ của trung tính bắn ra
    };
    std::vector<Sperm> sperms; // một class template là một khuôn đúc kiểu (xây class từ kiểu bê tông như int float struct) , thùng thông minh chứa nhiều object cùng kiểu
    void createSperm();
    void killSperm();
    void renderSperm();

    struct Pussy
    {
        SDL_Rect rect;        // hộp chứa kích thước
        SDL_Texture *texture; // hộp chứa họa tiết , màu sắc
    };
    Pussy pussy;                // tạo biến pussy từ kiểu struct Pussy chứa các giá trị của cả những struct con
    std::vector<Pussy> pussies; // tạo hộp thông minh chứa nhiều object "lồn" cùng kiểu
    void createPussy();         // tạo dữ liệu của lồn , và gọi trong init()
    void renderPussy();         // gửi lệnh vẽ "lồn" qua hàm của SDL_RenderCopy()

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