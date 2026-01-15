// đầu tiên bao gồm các chỉ thì tiền xử lý cái này sẽ hoạt động trước cả khi code chạy
#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

// tạo lớp bằng cú pháp (keyword) class và tên của class mà mình muốn đặt (chọn Pong) và dùng curly bracket để đóng gói dữ liệu
class Pong
{
    // ta tạo ra các hàm sử dụng công công (public) tức là bên môi trường bên ngoài cũng có thể truy cập vào , keyword = public:
public:
    // tạo ra (hàm khởi tạo) và (hàm hủy diệt)
    Pong();
    ~Pong();

    // tạo ra hàm khởi tạo tài nguyên tờ giấy và bút mực vẽ "ẩn dụ" của window và renderer , cách dùng return type + tên function
    bool init();
    void run();

    // ta tạo ra hàm sử dụng riêng tự (private) , chỉ có người chủ mới có quyền truy cập nghĩa là người tạo class đó
private:
    // ta sẽ tạo ra nhưng hàm theo thứ tự xuất hiện của nó trong hệ thống phân cấp
    // đầu tiên là ta sẽ tạo ra function của các đối tượng (vẽ) sau khi ta có được tờ giấy và cây bút mực to để dùng (ẩn dụ window và renderer) :chế độ chơi:( paddle, ball, vạch kẻ giữa, điểm ) ; chế độ MENU: (3 rect đại diện cho MENU, chế độ 1 người, chế độ 2 người) , chế độ GameOver: (2 rect: 1 cái là GAMEOVER, một cái là restart) tức là trả về màn hình MENUrender
    void renderPaddleBall();
    void renderMiddleLine();
    void renderScore();
    void render();

    // tạo thêm 2 hàm nữa chứa khối chữ trong vram : 2 hàm này sẽ nhận 2 biến chứa SDL_Texture*
    void renderMenuTextVram();
    void renderGameOverTextVram();

    // tiếp theo sau khi có được các object đã được vẽ ta sẽ làm chúng : di chuyển bằng cách gắn chúng cho các sự kiện xảy ra (bằng cách phím): chuyển màn thì dùng PollEvent , giữ phím thì dùng GetKeyboardState
    void handleEvents(float delta);

    // sau khi ta có được sự kiện chuyển cảnh và vợt di chuyển ta sẽ cho bóng di chuyển , tính toán va chạm với màn hình và va chạm với bóng
    void update(float delta);

    // chatgpt : tạo thêm hàm resetBall sau khi va chạm tường trái/phải để tính điểm
    void resetBall(int direction);

    // hàm này phục vụ cho việc tái thiết lập trạng thái game: bóng đứng yên , điểm số về 0 , kết thúc trì hoàn thiết lập về sai
    void startGame(int direction);

    // dọn dẹp tài nguyên
    void cleanUp();

    // tạo hàm trả lại SDL_TextTure* : hàm nhận 2 tham số gồm : cam kết không thay đổi dạng chuỗi + khối struct SDL_Rect
    SDL_Texture *CreateTextTexture(const std::string &text, SDL_Rect &rect);

    // 2 biến chứa địa chỉ của 2 texture trong vram , rồi sau đó gắn vào 2 hàm renderMenuTextVram() và renderGameOverTextVram()
    SDL_Texture *menuText;
    SDL_Texture *gameOverText;

    // 2 biến khối chữ để thiết lập chiều cao , chiều rộng , vị trí kinh độ và vĩ đỗ của chữ (text) trên màn hình , biến này được đưa vào trong hàm createTextTexture() để thay đổi giá trị ngay sau khi thiết lập Surface trong Ram bằng cách nhét : TTF_Font* font , SDL_Color color , text.c_str() vào trong hàm SDL_Surface TTF_RenderText_Solid() sẽ tạo ra bitmap trong ram và cái này chứa luôn cả kích thước dài , rộng của khối chữ nên gán vào khối SDL_Rect luôn
    SDL_Rect menuTextBlock;
    SDL_Rect gameOverTextBlock;

    // để mà tạo được một bitmap và metadata của một text ta cần font tải từ trên google xuống có đầy đủ toán vector trong đó rồi (không cần tạo lại nữa chỉ dùng thôi và hiểu nó) đưa nó vào hàm TTF_RenderText_Solid() và nó yêu cầu một TTF_Font*
    TTF_Font *font;

    // tạo trạng thái của game qua enum scope
    enum class Screen
    {
        MENU,
        ONE_PLAYER,
        TWO_PLAYER,
        GAMEOVER
    };

    // biến lưu giá trị của enum kiểu Screen
    Screen currentScreen;
    // các biến thuộc render: vợt , ball , speed , windowH , windowWinit (funciton render)
    // biến trạng thái : MENU , ONE_PLAYER , TWO_PLAYER , ENDGAME
    int MinWindowW;
    int MaxWindowW;
    int MinWindowH;
    int MaxWindowH;
    // ball
    int ballSize;
    float ballVelX;
    float ballVelY;
    float ballX;
    float ballY;
    // paddle: left , right
    int paddleH;
    int paddleW;
    float paddleLeftX;
    float paddleLeftY;
    float paddleRightX;
    float paddleRightY;
    float paddleSpeed;

    // các biến pointer : đê lưu địa chỉ của "tờ giấy" và "chổi vẽ" (function init)
    SDL_Window *window;
    SDL_Renderer *renderer;

    // biến của loop
    bool running;
    // biến tính điểm
    int rightScore;
    int leftScore;
    // bóng bị đóng băng
    bool ballFrozen;
    // biến của phần làm chậm
    Uint32 delayGameOver;
    bool endDelay;
};