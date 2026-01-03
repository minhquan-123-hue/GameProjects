// đầu tiên là include Game.h vào và SDL cùng với iostream , và cmath để dùng std::abs (free funciton)
#include <Pong.h>
#include <SDL2/SDL.h>
#include <cmath>
#include <iostream>

// hàm khởi tạo constructor :để khởi tạo các biến thành viên (các chỉ số của chúng) không phải gán mà là đi kèm khi sinh ra luôn
Pong::Pong() : // window : min max
               MaxWindowH(1000),
               MinWindowH(0),
               MaxWindowW(1000),
               MinWindowW(0),
               // ball: size , position , speed
               ballSize(30),
               ballVelX(700.0f),
               ballVelY(700.0f),
               ballX(MaxWindowW / 2),
               ballY(MaxWindowH / 2),
               // paddle: size, position, speed
               paddleH(100),
               paddleW(20),
               paddleLeftX(MinWindowW + 10),
               paddleLeftY(MinWindowH + 10),
               paddleRightX(MaxWindowW - 10 - paddleW),
               paddleRightY(MinWindowH + 10),
               paddleSpeed(1000.0f),
               // pointer: van chua co gi
               window(nullptr),
               renderer(nullptr),
               // loop control: đúng khi mà khởi tạo thành công "tờ giấy" + "cây chổi cọ"
               running(false),
               // màn hình hiện tại
               currentScreen(Screen::MENU),
               // bóng bị đóng băng
               ballFrozen(true),
               // điểm
               rightScore(0),
               leftScore(0),
               // tạo biến kiểm soát : làm chậm trước khi nhảy sang thua
               endDelay(false) // cái y/n trì hoãn đồng hồ chưa được bật

{
}

// hàm tạo ra "giấy" và "chổi"
bool Pong::init()
{
    std::cout << "start game..." << std::endl;

    // hỏi OS,driver tạo ra hệ thống video để ta có thể tạo ra "tờ giấy chuyển động"
    int initResult = SDL_Init(SDL_INIT_VIDEO);

    // kiểm tra xem có khởi tạo subsystem thành công hay không
    if (initResult != 0)
    {
        std::cerr << "SDL can't work" << SDL_GetError() << std::endl;
        return false;
    }

    // tạo tờ giấy chuyển động để vẽ lên
    window = SDL_CreateWindow(
        "pong",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        MaxWindowW,
        MaxWindowH,
        SDL_WINDOW_SHOWN);

    // kiểm tra xem tờ giấy có được tạo ra không => nếu không sẽ trả lại nullptr
    if (!window)
    {
        std::cerr << "can't create window" << SDL_GetError() << std::endl;
        return false;
    }

    // tạo cây chổi cọ bự => nếu không tạo được chổi sẽ trả lại nullptr
    renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED);

    if (!renderer)
    {
        std::cerr << "can't create renderer" << SDL_GetError() << std::endl;
        return false;
    }

    running = true;
    return true;
}

// vẽ MENU
void Pong::renderMenu()
{
    // vẽ 3 khối
    // khối một : thay chữ MENU
    SDL_Rect Menu;
    Menu.x = 400; // x hiện tại ở vị trí 400 khối tiếp theo thụt vào khoảng 50 => 2 hình onePLayer , twoPlayer = 450
    Menu.y = 100; // y hiện tại đã ở 100 khối tiếp theo nên cách ít nhất 50 => 150 cho 2 hình onePlayer , twoPlayer
    Menu.w = 200;
    Menu.h = 100;

    // khối hai : thay chứ ONE_PLAYER , tạo ra một object ở đâu đó trong bộ nhớ , và cần & address of operator để truy cập vào nơi nó ở để có thể vẽ nó
    SDL_Rect onePlayer;
    onePlayer.x = 450;
    onePlayer.y = 250;
    onePlayer.w = 100;
    onePlayer.h = 80;

    // khối ba: thay cho chữ TWO_Player
    SDL_Rect TwoPlayer;
    TwoPlayer.x = 450;
    TwoPlayer.y = 450;
    TwoPlayer.w = 100;
    TwoPlayer.h = 80;

    // giờ ta sẽ thiết lập màu và vẽ lên 3 khối này
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // hiểu đơn giản function này là để thiết lập trạng thái màu
    SDL_RenderFillRect(renderer, &Menu);                  // function này là mang bút màu đi tô màu vào cái khối đó trong window
    SDL_RenderFillRect(renderer, &onePlayer);
    SDL_RenderFillRect(renderer, &TwoPlayer);
}

// vẽ bóng và vợt
void Pong::renderPaddleBall()
{

    // vợt trai
    SDL_Rect paddleLeft;
    paddleLeft.x = paddleLeftX;
    paddleLeft.y = paddleLeftY;
    paddleLeft.w = paddleW;
    paddleLeft.h = paddleH;

    // vợt phai
    SDL_Rect paddleRight;
    paddleRight.x = paddleRightX;
    paddleRight.y = paddleRightY;
    paddleRight.w = paddleW;
    paddleRight.h = paddleH;

    // ball
    SDL_Rect ball;
    ball.x = ballX;
    ball.y = ballY;
    ball.w = ballSize;
    ball.h = ballSize;

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &paddleLeft);
    SDL_RenderFillRect(renderer, &paddleRight);
    SDL_RenderFillRect(renderer, &ball);
}

// vẽ đường kẻ ở giữa
void Pong::renderMiddleLine()
{

    SDL_Rect middleLine;

    // đây là dùng công thức của ngày hôm qua
    for (int i = 0; i <= 20; i++)
    {
        middleLine.x = 498;
        middleLine.y = 0 + i * 60;
        middleLine.w = 4;
        middleLine.h = 50;

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &middleLine);
    }
}

// vẽ bảng điểm bằng khối
void Pong::renderScore()
{
    // câu hỏi: tại sao cái này của tôi nó lại vẽ luôn 2 block đầu tiên luôn ngay cả khi chưa ghi điểm ? và giải thích cho tôi nó hoạt động như thế nào , tôi vẫn chưa hiểu tại sao khi lông nó vào trong loop running mỗi lần chạm vào cái tường trục X 2 bên trái phải nó mới bắt đầu vẽ ra window không giống như các cái (vợt , vạch , bóng) vẽ ra từ đầu

    // tao ra một object SDL_Rect và member var (kích thước của nó)
    // dùng thêm cả công thức for loop : x = x_bắt đầu + i * khoảng cách (lớn hơn kích thước chiều cao của vật)

    SDL_Rect scoreBlockLeft;

    // vòng lặp for cần điều kiện start , end, step , và dùng ; để kết thúc từng statement , i++ là cộng +=
    for (int i = 0; i < leftScore; i++)
    {
        scoreBlockLeft.x = 200 + i * 20; // 20 là khoảng cách lớn hơn kích thước vật dự tính là 15
        scoreBlockLeft.y = 100;
        scoreBlockLeft.w = 15;
        scoreBlockLeft.h = 15;

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &scoreBlockLeft);
    }

    // score ben phai
    SDL_Rect scoreBlockRight;

    for (int i = 0; i < rightScore; i++)
    {
        scoreBlockRight.x = 600 + i * 20;
        scoreBlockRight.y = 100;
        scoreBlockRight.w = 15;
        scoreBlockRight.h = 15;

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &scoreBlockRight);
    }
}

// tạo một cái màn cuối cùng GAMEOVER
void Pong::renderGameOver()
{

    // tạo một object SDL_Rect và các biến thành viên (kích thước)
    SDL_Rect GameOver;
    GameOver.x = 200;
    GameOver.y = 100;
    GameOver.w = 600;
    GameOver.h = 300;

    // khổi 2 : gỉa chứ restart
    SDL_Rect Restart;
    Restart.x = 300;
    Restart.y = 450;
    Restart.w = 400;
    Restart.h = 200;

    // thiết lập màu cho khối
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &Restart);
    SDL_RenderFillRect(renderer, &GameOver);
}

// thiết lập điều kiện để nhay sang các trạng thái
void Pong::render()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    // so sánh biến currentScreen với giá trị của enum truy cập == scope
    if (currentScreen == Screen::MENU)
    {
        renderMenu();
    }
    else if (currentScreen == Screen::ONE_PLAYER)
    {
        renderPaddleBall();
        renderMiddleLine();
        renderScore();
    }
    else if (currentScreen == Screen::TWO_PLAYER)
    {
        renderPaddleBall();
        renderMiddleLine();
        renderScore();
    }
    else if (currentScreen == Screen::GAMEOVER)
    {
        renderGameOver();
    }

    // sau khi vẽ xong hết rồi đổi từ back buffer các hình vẽ sang front buffer (hiển thị lên màn hình để người chơi thấy)
    SDL_RenderPresent(renderer);
}

// tạo hàm xử lý sự kiện để nhảy qua nhảy lại 4 sự kiện
void Pong::handleEvents(float delta)
{
    // đầu tiên kiểm tra đang ở màn hình MENU sau đó nghe phím enter để bắt đầu game dùng PollEvent (hàm này ghi lại sự kiện mà SDL nghe từ OS cái sự kiện vừa diễn ra) toàn bộ sự kiện này nên đưa vào vòng lặp để lắng nghe toàn bộ sự kiện
    // Có 3 sự kiện mà ta phải kiểm tra bằng phím vừa ấn (SDL_PollEvent(&event)) đó là từ MENU sang ONE_PLAYER or TWO_PLAYER , và từ GAMEOVER về MENU và cả sự kiện thoát toàn bộ game SDL_QUIT
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {

        // giờ sẽ là sự kiện yêu cầu kết thúc : có thể là hủy window bằng chuột , có thể dùng super + Q , có thể tắt máy nên không quan trọng là yêu cầu hủy bằng cái nào chỉ gom lại thành 1 loại sự kiện duy nhất gửi về từ OS ghi lại VÀ TRAO CHO SDL và SDL_PollEvent sẽ đọc và ghi vào Event đó chính là SDL_QUIT
        // không quan trọng là đang ở trạng thái nào khi có lệnh yêu cầu hủy là phải hủy thế thôi
        if (event.type == SDL_QUIT)
        {
            // ta sẽ tắt toàn bộ trò chơi bằng cách tắt loop chính đi => running = false;
            running = false;
        }

        if (event.type == SDL_KEYDOWN)
        {

            if (currentScreen == Screen::MENU && event.key.keysym.scancode == SDL_SCANCODE_1)
            {
                // ta sẽ nhảy về màn hình của 1 người chơi
                currentScreen = Screen::ONE_PLAYER;
                ballFrozen = false;
            }
            // event là object kiểu SDL_Event được PollEvent ghi sự kiện xảy ra vào các biến thành viên của nó , nên ta phải truy cập theo dạng chuỗi để đọc được nội dung của sự kiện đó , có một sự trường hợp khác nhau như event.type là kiểu của sự kiện , event.key.keysym.scancode là phím vật lý nào đang được ấn
            if (currentScreen == Screen::MENU && event.key.keysym.scancode == SDL_SCANCODE_2)
            {
                // ta sẽ nhảy vào màn 2 người chơi
                currentScreen = Screen::TWO_PLAYER;
                ballFrozen = false;
            }

            if (currentScreen == Screen::GAMEOVER && event.key.keysym.scancode == SDL_SCANCODE_R)
            {
                currentScreen = Screen::MENU;
            }
        }
    }

    // sự kiện phím bấm giữ => phải dùng GetKeyboardState tức là dùng con trỏ để đi đến mảng đọc trạng thái của nó: những thứ ta cần dùng là: toán con trỏ , index (= 1 giá trị của 1 enum Scancode)

    const Uint8 *keystate = SDL_GetKeyboardState(nullptr); // ta cho nullptr vì ta chỉ cần địa chỉ con trỏ không phải là số lượng keystate mà GetKeyboardState chứa

    // Xử lý trạng thái một người chơi với máy
    if (currentScreen == Screen::ONE_PLAYER)
    {
        // lắng nghe phím cho người chơi bên trais
        if (keystate[SDL_SCANCODE_W])
        {
            paddleLeftY -= paddleSpeed * delta;
        }
        if (keystate[SDL_SCANCODE_S])
        {
            paddleLeftY += paddleSpeed * delta;
        }

        // giờ là máy 0.1 đuổi theo tâm bóng
        float ballCenter = ballY + ballSize * 0.5f;
        float paddleCenter = paddleRightY + paddleH * 0.5f;

        if (ballCenter < paddleCenter)
        {
            paddleRightY -= paddleSpeed * delta;
        }
        if (ballCenter > paddleCenter)
        {
            paddleRightY += paddleSpeed * delta;
        }

        // ngăn lại không cho vợt di chuyển qua khỏi màn hình trên trục Y
        if (paddleLeftY <= MinWindowH)
        {
            paddleLeftY = MinWindowH;
        }
        if (paddleLeftY >= MaxWindowH - paddleH)
        {
            paddleLeftY = MaxWindowH - paddleH;
        }
        if (paddleRightY <= MinWindowH)
        {
            paddleRightY = MinWindowH;
        }
        if (paddleRightY >= MaxWindowH - paddleH)
        {
            paddleRightY = MaxWindowH - paddleH;
        }
    }

    // màn hai người chơi nghe 4 phím : W , S , UP , DOWN , và có cả ngăn va chạm trượt ra khỏi màn hình
    if (currentScreen == Screen::TWO_PLAYER)
    {

        // dùng toán con trỏ , mảng đến tính được vị trí của phím sau đó kiểm tra trạng thái (0 hoặc 1) , a[b] = *(a + b)
        if (keystate[SDL_SCANCODE_W])
        {
            paddleLeftY -= paddleSpeed * delta;
        }
        if (keystate[SDL_SCANCODE_S])
        {
            paddleLeftY += paddleSpeed * delta;
        }
        if (keystate[SDL_SCANCODE_UP])
        {
            paddleRightY -= paddleSpeed * delta;
        }
        if (keystate[SDL_SCANCODE_DOWN])
        {
            paddleRightY += paddleSpeed * delta;
        }

        // không di chuyển trượt ra khỏi màn hình
        if (paddleLeftY <= MinWindowH)
        {
            paddleLeftY = MinWindowH;
        }
        if (paddleLeftY >= MaxWindowH - paddleH)
        {
            paddleLeftY = MaxWindowH - paddleH;
        }
        if (paddleRightY <= MinWindowH)
        {
            paddleRightY = MinWindowH;
        }
        if (paddleRightY >= MaxWindowH - paddleH)
        {
            paddleRightY = MaxWindowH - paddleH;
        }
    }

    if (currentScreen == Screen::ONE_PLAYER || currentScreen == Screen::TWO_PLAYER)
    {
        if (endDelay == false && (rightScore == 10 || leftScore == 10))
        {
            // đo thời điểm game bắt đầu dừng sau khi đã kết chiến thắng / thua
            delayGameOver = SDL_GetTicks();
            // thiết lập bool bằng đúng để bằng đầu so sánh thời gian đã được 3 giây chưa
            endDelay = true;

            // cho bóng và vợt dừng lại
            ballFrozen = true;
        }
    }

    if (endDelay == true)
    {
        Uint32 now = SDL_GetTicks();
        if ((now - delayGameOver) >= 3000)
        {
            // sau điều kiện khớp , ta nhảy đến màn hình kết thúc , điểm thiết lập lại thành 0 để khi nhảy vào ONE_PLAYER , TWO_PLAYER thì không bị bật về GAMEOVER do chưa reset game
            currentScreen = Screen::GAMEOVER;
            rightScore = 0;
            leftScore = 0;
            endDelay = false;
        }
    }
}

// hàm cập nhật : va chạm , bóng đóng băng
void Pong::update(float delta)
{

    // đầu tiên là kiểm tra điều kiện nếu mà : màn hình là GAMEOVER ,hoặc MENU thì bóng sẽ đóng băng
    if (ballFrozen)
    {
        return;
    }

    // nếu mà điều kiện bóng không đóng băng == false thì ta sẽ nhay sang điều kiện này mà không cần nằm trong if
    ballX += ballVelX * delta;
    ballY += ballVelY * delta;

    // tính toán va chạm cho bong với tuongwf  và đập lại
    if (ballX <= MinWindowW)
    {
        rightScore++;
        std::cout << "totalpoint:(rightpaddle): " << rightScore << std::endl;
        resetBall(1);
    }
    if (ballX >= MaxWindowW - ballSize)
    {
        leftScore++;
        std::cout << "totalpoint:(leftPaddle): " << leftScore << std::endl;
        resetBall(-1);
    }
    if (ballY <= MinWindowH)
    {
        ballY = MinWindowH;
        ballVelY = -ballVelY;
    }
    if (ballY >= MaxWindowH - ballSize)
    {
        ballY = MaxWindowH - ballSize;
        ballVelY = -ballVelY;
    }

    // giờ là cập nhật va chạm với 2 vật thể : bóng và vợt , so sánh 2 trục va chạm , với truc X thì chỉ cần va chạm mặt trước còn với trục y thì từ cạnh thân đến cạnh thân giữa là điểm va chạm

    bool overlapLeftX = ballX <= paddleLeftX + paddleW;
    bool overlapLeftY = ballY + ballSize >= paddleLeftY && ballY <= paddleLeftY + paddleH;

    if (overlapLeftX && overlapLeftY && ballVelX < 0)
    {
        ballX = paddleLeftX + paddleW;
        ballVelX = -ballVelX;

        // tính điểm bật lại của trục y bằng cách tính độ lệch của giữa bóng và vợt
        float ballCenter = ballY + ballSize * 0.5f;
        float paddleCenter = paddleLeftY + paddleH * 0.5f;
        float offset = (ballCenter - paddleCenter) / (paddleH * 0.5f); // chuẩn hóa độ lệch : công thức của chatGpt độ lệch thật / chia độ lệch tối đa
        // tạo ra một tốc độ không thể thay đổi để bóng không bị tác động bằng nhiều trạng thái đổi chiều , hoặc có thể bị thay đổi tốc độ , gợi ý chatGPt không biết chính xác có chuẩn không
        const float fixSpeed = 700.0f;
        ballVelY = fixSpeed * offset;
    }

    // tạo thêm điều kiện va chạm với vợt phải

    bool overlapRightX = ballX + ballSize >= paddleRightX;
    bool overlapRightY = ballY + ballSize >= paddleRightY && ballY <= paddleRightY + paddleH;

    if (overlapRightX && overlapRightY && ballVelX > 0)
    {

        ballX = paddleRightX - ballSize;
        ballVelX = -ballVelX;

        float ballCenter = ballY + ballSize * 0.5f;
        float paddleCenter = paddleRightY + paddleH * 0.5f;
        float offset = (ballCenter - paddleCenter) / (paddleH * 0.5f);
        const float fixSpeed = 700.0f;
        ballVelY = fixSpeed * offset;
    }
}

// tạo hàm thiết lập về ban đầu khi mà bóng va chạm vào Trục X (trái / phải)
void Pong::resetBall(int direction)
{
    paddleLeftY = MaxWindowW / 2;

    paddleRightY = MaxWindowW / 2;
    ballX = MaxWindowW / 2;
    ballY = MaxWindowH / 2;

    ballVelY = 0.0f;
    ballVelX = direction * std::abs(ballVelX);
}
// dùng run để test xem từng bước đã hoạt động được chưa
void Pong::run()
{
    // tính thời gian độ lệch giữa 2 frame dịch chuyển: tạo ra 2 khung thời gian để đo được khoảng khắc bóng đã di chuyển được bao xa rồi
    Uint32 previousTime = SDL_GetTicks();
    while (running)
    {
        Uint32 currentTime = SDL_GetTicks();
        float delta = (currentTime - previousTime) / 1000.0f; // đổi sang second để tính
        // phải gắn gian của frame mới nhất về thành frame hiện tại để tính
        previousTime = currentTime; // #lỗi : khi thời gian mà làm sai thì di chuyển sai (vật lý bựa)
        render();
        handleEvents(delta);
        update(delta);
    }
}

// don tam tai nguyen
void Pong::cleanUp()
{
    if (renderer)
    {
        SDL_DestroyRenderer(renderer);
    }
    if (window)
    {
        SDL_DestroyWindow(window);
    }
    SDL_Quit();
}

// gọi hàm phá hủy sau khi đã vượt ra khỏi phạm vi của hàm main
Pong::~Pong()
{
    cleanUp();
}