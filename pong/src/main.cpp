// include header để: preprocessor + linker kết nối các file với nhau
#include <Pong.h>

int main()
{
    // tạo object
    Pong pong;
    // khởi tạo chương trình nếu không chạy được trả về một thoát khỏi chương trình: trả lại tài nguyên C++ và SDL
    if (!pong.init())
    {
        return 1;
    }
    pong.run(); // chạy chương trình thành công , xong thì trả về không và thoát khỏi chương trình trả tài nguyên
    return 0;
}
