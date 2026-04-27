#include <game.h>

int main(void)
{
    Pong pong;
    bool initResult = pong.init();
    if (!initResult)
    {
        return 1; // lỗi không khởi tạo tài nguyên thành công
    }
    pong.run();
    return 0;
}