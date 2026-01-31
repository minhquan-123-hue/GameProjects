// giờ ta tạo object + nhập khẩu header vào để cho chương trình chạy

#include <Game.h>

int main()
{
    // tạo object
    BreakOut game;
    if (!game.init()) // kiểm tra xem chạy được không , sai trả về false => return 1; chạy thoát khỏi int main() và tài nguyên C++ sẽ được giải phóng ?
    {
        return 1;
    }
    game.run();
    return 0;
}