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
    // những con trỏ để khởi tạo tài nguyên
    SDL_Window *window;

    SDL_Renderer *renderer;
    // sau đó là vẽ phải vẽ
    void render();

    // cần 1 cờ để điều khiển vòng lặp
    bool running;
    // tạo một đối tượng lưu sự kiện của OS đưa cho SDL
    SDL_Event event;
    // và tạo ra một nơi để xử lý "SỰ KIỆN" (phím , chuột ,...)
    void handleEvents(float delta);
};