// include the headers : SDL2, Game.h , iostream
#include <SDL2/SDL.h>
#include <Game.h>
#include <iostream>
#include <cmath>

// contructor: initialize var
Game::Game() : // set running for loop
               running(false),
               // create the paper to draw (window)
               window(nullptr),
               // create the paint brush
               renderer(nullptr),
               // set state for object
               paddleLeftX(10.0f),
               paddleLeftY(10.0f),
               paddleRightX(970.0f),
               paddleRightY(10.0f),
               paddleSpeed(650.0f),
               ballX(700.0f),
               ballY(700.0f),
               ballVelX(500.0f),
               ballVelY(500.0f),
               // set point to zero
               leftPoint(0),
               rightPoint(0),
               currentScreen(Screen::MENU),
               ballFrozen(true),
               windowHeight(1000),
               windowWidth(1000),
               gameOverTimer(0),
               gameOverPending(false)

{
}

// destructor : cleanUp after finishing use
Game::~Game()
{
    cleanUp();
}

// init : SDL_INIT_VIDEO , window , renderer , set running true for loop later if all init success , return true for main.cpp use later
bool Game::init()
{
    std::cout << "starting game... " << std::endl;

    // call os to create init video system
    int initResult = SDL_Init(SDL_INIT_VIDEO);

    if (initResult != 0)
    {
        std::cerr << "can't call os to create video system:" << SDL_GetError() << std::endl;
        return false;
    }

    // create the paper to draw, pointer point to where "paper" live
    window = SDL_CreateWindow(
        "pong",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        windowHeight,
        windowWidth,
        SDL_WINDOW_SHOWN);

    // if willdow is nullptr => false
    if (!window)
    {
        std::cerr << "can't create window (paper to draw):" << SDL_GetError() << std::endl;
        return false;
    }

    // create a thick brush to draw , pointer point to where "thick brush" live, need "paper" to draw (window)
    renderer = SDL_CreateRenderer(
        window,
        -1, // choose the rendering driver : trinh dieu khien do hoa (gpu or cpu)
        SDL_RENDERER_ACCELERATED);

    // if renderer return nullptr
    if (!renderer)
    {
        std::cerr << "cant create renderer" << SDL_GetError() << std::endl;
        return false;
    }

    // after window ,and renderer successfully created , set bool to true for run()
    running = true;
    // return to main.cpp
    return true;
}

// sub_render: FAKE MENU : 2 RECTANGLE
void Game::renderMenu()
{
    // create faketext : big on top
    SDL_Rect menu = {350, 100, 300, 250};
    SDL_SetRenderDrawColor(renderer, 125, 125, 125, 255);
    SDL_RenderFillRect(renderer, &menu);

    // create fake small text: ONE_PLAYER
    SDL_Rect ONE_PLAYER = {400, 400, 100, 150};
    SDL_SetRenderDrawColor(renderer, 205, 205, 205, 255);
    SDL_RenderFillRect(renderer, &ONE_PLAYER);

    // create fake small text: TWO_PLAYER
    SDL_Rect TWO_PLAYER = {400, 600, 100, 150};
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    SDL_RenderFillRect(renderer, &TWO_PLAYER);
}

// sub_render : objects(ball, paddle:left, right) => PLAYING
void Game::renderGame()
{
    // create paddle: Left , Right
    SDL_Rect paddleLeft;
    paddleLeft.x = static_cast<int>(paddleLeftX);
    paddleLeft.y = static_cast<int>(paddleLeftY);
    paddleLeft.w = 20;
    paddleLeft.h = 100;

    SDL_Rect paddleRight;
    paddleRight.x = static_cast<int>(paddleRightX);
    paddleRight.y = static_cast<int>(paddleRightY);
    paddleRight.w = 20;
    paddleRight.h = 100;

    SDL_Rect ball;
    ball.x = ballX;
    ball.y = ballY;
    ball.w = 30;
    ball.h = 30;

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &paddleLeft);
    SDL_RenderFillRect(renderer, &paddleRight);
    SDL_RenderFillRect(renderer, &ball);
}

// tạo vạch kẻ ở giữa sân bóng
void Game::renderMiddleLine()
{
    SDL_Rect middleLine;
    middleLine.x = 498;
    middleLine.y = 0;
    middleLine.w = 4;
    middleLine.h = 1000;

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &middleLine);
}
// create fake state widow :GameOver
void Game::renderGameOver()
{
    // VE HINH CHU NHAT GIA CHU "GAMEOVER"
    SDL_Rect gameover = {350, 100, 300, 100};
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &gameover);

    // ve hinh chu nhat gia chu "restart"
    SDL_Rect restart = {400, 300, 200, 200};
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &restart);
}

// bây giờ ta sẽ vẽ score
void Game::renderScore()
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    // left score
    // giải thích cho tôi : tại sao i lại phải nhỏ hơn điểm bên trái ? (tức là nhỏ hơn 5 => max=4)
    for (int i = 0; i < leftPoint; i++)
    {
        SDL_Rect block;
        // tại sao lại tính trục x = 200 + i * 20 ?
        block.x = 200 + i * 20;
        block.y = 50;
        block.w = 15;
        block.h = 15;

        SDL_RenderFillRect(renderer, &block);
    }

    // right Score
    for (int i = 0; i < rightPoint; i++)
    {
        SDL_Rect block;
        block.x = 600 + i * 20;
        block.y = 50;
        block.w = 15;
        block.h = 15;

        SDL_RenderFillRect(renderer, &block);
    }
}
// parent render , run condition if/else (MENU,PLAYING,GAMEOVER)
void Game::render()
{
    // VE HINH NEN DANG SAU
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    if (currentScreen == Screen::MENU)
    {
        renderMenu();
    }
    else if (currentScreen == Screen::ONE_PLAYER)
    {
        renderMiddleLine();
        renderScore();
        renderGame();
    }
    else if (currentScreen == Screen::TWO_PLAYER)
    {
        renderMiddleLine();
        renderScore();
        renderGame();
    }
    else if (currentScreen == Screen::GAMEOVER)
    {
        renderGameOver();
    }

    SDL_RenderPresent(renderer);
}

// xử lý các sự kiện đầu vào của 3 trạng thái : MENU , PLAYING , GAMEOVER
void Game::handleEvents(float delta)
{
    // dùng hàm : sdl này để lấy giá trị đầu tiên của mảng , sau đó có thể dùng công thức a[b] với con trỏ để biết được trạng (0 và 1) của phím có đang được bật hay không để quyết định vị trí đi tiếp theo
    const Uint8 *keystate = SDL_GetKeyboardState(nullptr);

    // hiện tại là chưa thể kết quá nhiều biến đổi nên tạm thời tạo const (cam kết không biến đổi) cho một số biến ở đây so đó sẽ so sánh va chạm
    const int min_Y = 0;
    const int max_Y = 1000;
    const int paddleH = 100;

    // lắng nghe sự kiện : quit (super + Q) để tắt vòng lặp , vì đây là sự kiện của cả 3 trạng thái tức là toàn game nên không được để trong riêng bất kỳ trạng thái nào cả
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_KEYDOWN)
        {

            // đầu tiên là so sánh dạng sự kiện đã xảy mà SDL_PollEvent() đã ghi vào trong type check xem có phải dạng bàn phím không nếu phải ta sẽ kiểm tra: TRẠNG THÁI + PHÍM VẬT NÀO ẤN => sau đó ta sẽ chuyển TRẠNG THÁI sang một của sổ khác sau khi đã biết 2 điền kiện trên khớp , vào ta sẽ truy cập phím vật lý bằng bằng cách sử dụng event.key.keysym.scancode để truy cập vào enum ?? để biết là phím nào đã được gõ ?

            // đây là chế độ 1 NGƯỜI CHƠI
            if (currentScreen == Screen::MENU && event.key.keysym.scancode == SDL_SCANCODE_1)
            {
                currentScreen = Screen::ONE_PLAYER;
                ballFrozen = false;
            }
            // đÂY LÀ CHẾ ĐỘ HAI người
            if (currentScreen == Screen::MENU && event.key.keysym.scancode == SDL_SCANCODE_2)
            {
                currentScreen = Screen::TWO_PLAYER;
                ballFrozen = false;
            }
            // đây là kết thúc game quay lại menu
            if (currentScreen == Screen::GAMEOVER && event.key.keysym.scancode == SDL_SCANCODE_R)
            {
                currentScreen = Screen::MENU;
                ballFrozen = true;
                rightPoint = 0;
                leftPoint = 0;
            }
        }

        // ta sẽ so sánh kiểu sự kiện nào đang xảy ở đây : là sự kiện yêu cầu dừng vậy ta sẽ hủy loop cái sự kiện yêu cầu dừng không phải là tự hủy window , ta dừng loop thì window mới dừng
        if (event.type == SDL_QUIT)
        {
            running = false;
        }
    }

    // đây là chể độ 2 người chơi 2 vợt
    if (currentScreen == Screen::TWO_PLAYER)
    {
        if (keystate[SDL_SCANCODE_W])
        {
            paddleLeftY -= paddleSpeed * delta; // ở đây ta hiểu delta chính là thời gian lệch của của 2 khoảnh khắc tức là thời gian của mà vật đã đi (ẩn dụ: xe máy + máy ảnh)
        }
        if (keystate[SDL_SCANCODE_S]) // ERROR0: nếu để if/else if nó sẽ chỉ check 1 phím một thời điểm nên bị khựng khi muốn cả 2 hai vợt di chuyển theo ý của người chơi
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
    }

    if (currentScreen == Screen::ONE_PLAYER)
    {

        if (keystate[SDL_SCANCODE_W])
        {
            paddleLeftY -= paddleSpeed * delta; // ở đây ta hiểu delta chính là thời gian lệch của của 2 khoảnh khắc tức là thời gian của mà vật đã đi (ẩn dụ: xe máy + máy ảnh)
        }
        if (keystate[SDL_SCANCODE_S]) // ERROR0: nếu để if/else if nó sẽ chỉ check 1 phím một thời điểm nên bị khựng khi muốn cả 2 hai vợt di chuyển theo ý của người chơi
        {
            paddleLeftY += paddleSpeed * delta;
        }
    }

    // so sánh điểm (thắng / thua) khi thấp đạt được +5 và sẽ nhảy về màn hình cuối là GAMEOVER
    if (gameOverPending == false && rightPoint == 5 || leftPoint == 5)
    {
        gameOverPending = true;
        gameOverTimer = SDL_GetTicks();
        ballFrozen = true;
    }

    if (gameOverPending == true)
    {
        Uint32 now = SDL_GetTicks();

        if (now - gameOverTimer >= 3000)
        {
            currentScreen = Screen::GAMEOVER;
            gameOverPending = false;
        }
    }
}

// hàm này để cập nhật bóng di chuyển cùng với va chạm  và đồng thời lệnh kiểm soát luông(if/else) xem có phải là ballFrozen(bóng đứng yên không)
void Game::update(float delta)
{
    // thoát khỏi update ngay khi biết ballFrozen == true, để không dùng bất kỳ cái gì trong này trừ điều kiện sai
    if (ballFrozen)
    {
        return;
    }
    // tất cả logic khi bóng không đóng băng (ballFrozen == false)
    if (!ballFrozen && currentScreen == Screen::TWO_PLAYER)
    {
        // đầu tiên là quả bóng di chuyển đã bằng cách cộng thêm pixel mỗi 1 frame dùng toán tử += để biết vị trí hiện tại = vận tốc bóng + thời gian(khoảng khắc ghi hình giữa 2 frames)
        ballX += ballVelX * delta;
        ballY += ballVelY * delta;

        // tạo các const để kiểm tra va chạm
        const int min_X = 0;
        const int max_X = 1000;
        const int min_Y = 0;
        const int max_Y = 1000;
        const int ballSize = 30;
        const int paddleW = 20;
        const int paddleH = 100;

        // so sánh va chạm của hai bên 2 cột với trục Y : không được để vướt quá nhảy ra khỏi màn hình
        if (paddleLeftY <= min_Y)
        {
            paddleLeftY = min_Y;
        }
        else if (paddleLeftY >= max_Y - paddleH)
        {
            paddleLeftY = max_Y - paddleH;
        }
        if (paddleRightY <= min_Y)
        {
            paddleRightY = min_Y;
        }
        else if (paddleRightY >= max_Y - paddleH)
        {
            paddleRightY = max_Y - paddleH;
        }

        // kiểm tra va chạm với tường
        if (ballX <= min_X)
        {
            rightPoint++;
            std::cout << "rightPoint: " << rightPoint << std::endl;
            resetBall(1);
        }
        if (ballX >= max_X - ballSize)
        {
            leftPoint++;
            std::cout << "leftPoint: " << leftPoint << std::endl;
            resetBall(-1);
        }
        if (ballY <= min_Y)
        {
            ballY = min_Y;
            ballVelY = -ballVelY;
        }
        if (ballY >= max_Y - ballSize)
        {
            ballY = max_Y - ballSize;
            ballVelY = -ballVelY;
        }

        // Kiểm tra va chạm với vợt : gồm hai bên trái và phải ( mặt trước của vợt , 2 cạnh trên dưới) đúng khi cả trục y và x thỏa mãn điều kiện + hướng của vận tốc (âm hoặc dương)
        // vợt trái và bóng
        bool overlapX = ballX <= paddleLeftX + paddleW;
        bool overlapY = ballY <= paddleLeftY + paddleH && ballY + ballSize >= paddleLeftY;

        if (overlapX && overlapY && ballVelX < 0)
        {
            ballX = paddleLeftX + paddleW;
            ballVelX = -ballVelX;

            // giờ là sẽ làm bóng khi đập có độ lệch (offset) Y khi va vào mép trên hoặc mép dưới hoặc ở dưới
            float paddleCenter = paddleLeftY + (paddleH * 0.5f);
            float ballCenter = ballY + (ballSize * 0.5f);
            // chuẩn hóa độ lệch : độ lệch thật sự / độ lệch tối đa (công thức của chatgpt)
            float offset = (ballCenter - paddleCenter) / (paddleH * 0.5f);
            // giờ là vận tốc sau va chạm thay đổi trục Y
            const float fixSpeed = 400.0f;
            ballVelY = fixSpeed * offset;
        }

        // vợt phải và bóng
        bool overlaprX = ballX + ballSize >= paddleRightX;
        bool overlaprY = ballY <= paddleRightY + paddleH && ballY + ballSize >= paddleRightY;

        // so sanh khi ca 3 dieu kien khop : va chạm cả trục X , trục Y , vận tốc của X phải dương
        if (overlaprX && overlaprY && ballVelX > 0)
        {
            ballX = paddleRightX - ballSize;
            ballVelX = -ballVelX;

            // tạo thêm độ lệch cho trục Y khi va chạm vào cách mép
            float paddleCenter = paddleRightY + (paddleH * 0.5f);
            float ballCenter = ballY + (ballSize * 0.5f);
            float offset = (ballCenter - paddleCenter) / (paddleH * 0.5f);
            const float fixSpeed = 400.0f;
            ballVelY = fixSpeed * offset;
        }
    }

    if (!ballFrozen && currentScreen == Screen::ONE_PLAYER)
    {
        // đầu tiên là quả bóng di chuyển đã bằng cách cộng thêm pixel mỗi 1 frame dùng toán tử += để biết vị trí hiện tại = vận tốc bóng + thời gian(khoảng khắc ghi hình giữa 2 frames)
        ballX += ballVelX * delta;
        ballY += ballVelY * delta;

        // tạo các const để kiểm tra va chạm
        const int min_X = 0;
        const int max_X = 1000;
        const int min_Y = 0;
        const int max_Y = 1000;
        const int ballSize = 30;
        const int paddleW = 20;
        const int paddleH = 100;

        // TẠO VỢT MÁY ĐÁNH
        float paddleCenter = paddleRightY + paddleH / 2;
        float ballCenter = ballY + ballSize / 2;

        if (ballCenter > paddleCenter)
        {
            paddleRightY += paddleSpeed * delta;
        }
        else
        {
            paddleRightY -= paddleSpeed * delta;
        }

        // so sánh va chạm của hai bên 2 cột với trục Y : không được để vướt quá nhảy ra khỏi màn hình
        if (paddleLeftY <= min_Y)
        {
            paddleLeftY = min_Y;
        }
        else if (paddleLeftY >= max_Y - paddleH)
        {
            paddleLeftY = max_Y - paddleH;
        }
        if (paddleRightY <= min_Y)
        {
            paddleRightY = min_Y;
        }
        else if (paddleRightY >= max_Y - paddleH)
        {
            paddleRightY = max_Y - paddleH;
        }

        // kiểm tra va chạm với tường
        if (ballX <= min_X)
        {
            rightPoint++;
            std::cout << "rightPoint: " << rightPoint << std::endl;
            resetBall(1);
        }
        if (ballX >= max_X - ballSize)
        {
            leftPoint++;
            std::cout << "leftPoint: " << leftPoint << std::endl;
            resetBall(-1);
        }
        if (ballY <= min_Y)
        {
            ballY = min_Y;
            ballVelY = -ballVelY;
        }
        if (ballY >= max_Y - ballSize)
        {
            ballY = max_Y - ballSize;
            ballVelY = -ballVelY;
        }

        // Kiểm tra va chạm với vợt : gồm hai bên trái và phải ( mặt trước của vợt , 2 cạnh trên dưới) đúng khi cả trục y và x thỏa mãn điều kiện + hướng của vận tốc (âm hoặc dương)
        // vợt trái và bóng
        bool overlapX = ballX <= paddleLeftX + paddleW;
        bool overlapY = ballY <= paddleLeftY + paddleH && ballY + ballSize >= paddleLeftY;

        if (overlapX && overlapY && ballVelX < 0)
        {
            ballX = paddleLeftX + paddleW;
            ballVelX = -ballVelX;

            // giờ là sẽ làm bóng khi đập có độ lệch (offset) Y khi va vào mép trên hoặc mép dưới hoặc ở dưới
            float paddleCenter = paddleLeftY + (paddleH * 0.5f);
            float ballCenter = ballY + (ballSize * 0.5f);
            // chuẩn hóa độ lệch : độ lệch thật sự / độ lệch tối đa (công thức của chatgpt)
            float offset = (ballCenter - paddleCenter) / (paddleH * 0.5f);
            // giờ là vận tốc sau va chạm thay đổi trục Y
            const float fixSpeed = 400.0f;
            ballVelY = fixSpeed * offset;
        }

        // vợt phải và bóng
        bool overlaprX = ballX + ballSize >= paddleRightX;
        bool overlaprY = ballY <= paddleRightY + paddleH && ballY + ballSize >= paddleRightY;

        // so sanh khi ca 3 dieu kien khop : va chạm cả trục X , trục Y , vận tốc của X phải dương
        if (overlaprX && overlaprY && ballVelX > 0)
        {
            ballX = paddleRightX - ballSize;
            ballVelX = -ballVelX;

            // tạo thêm độ lệch cho trục Y khi va chạm vào cách mép
            float paddleCenter = paddleRightY + (paddleH * 0.5f);
            float ballCenter = ballY + (ballSize * 0.5f);
            float offset = (ballCenter - paddleCenter) / (paddleH * 0.5f);
            const float fixSpeed = 400.0f;
            ballVelY = fixSpeed * offset;
        }
    }
}

// chatgpt dạy nhưng , ta có thể hiểu ngoài đời khi mà có hàm phát sinh ta sẽ tạo ra không theo tuần tự  , hàm này là thiết lập lại vị trí của bóng sau khi va chạm hai bên Trục X
void Game::resetBall(int direction)
{
    // cho bóng về giữa màn hình , người nào vừa đánh trượt bóng tiếp tục rơi về người đó
    ballX = windowWidth / 2;
    ballY = windowHeight / 2;
    paddleLeftX = 10.0f;
    paddleRightX = 970.0f;
    paddleLeftY = 10.0f;
    paddleRightY = 10.0f;

    ballVelX = direction * std::abs(ballVelX);
    ballVelY = 0.0f;
}

// gọi run lên để kiểm xem vẽ đã ổn chưa và cho tạm cái sự kiện event SDL_QUIT vào trong để có thể tắt được , sau khi test xong thì sẽ viết hàm handleEvents
void Game::run()
{
    // tính thời gian giữa 2 khoảnh khắc ghi lại bằng đồng (2frames) để biết được vận đã đi được bao nhiêu thời gian (ẩn dụ: thời gian 2 lần chụp của xe máy di chuyển lần 1 0m lần 2 10m lần 3 20m thì khoảng cách 10 chính là thời gian sẽ đã đi) , giờ ta sẽ dùng hàm GetTicks() để tính được thời gian đó : sẽ dùng thời gian của đồng hồ thứ 2 trong loop trừ đi đồng hồ đầu tiền ta sẽ tính được độ chênh lệch giữa 2 frames (2 khoảnh khắc) và sau khi mà trừ đi thì cần cập nhật thời gian đế biết thời gian giữa frame hiện tại và frame tiếp theo
    Uint32 previousTime = SDL_GetTicks();

    while (running)
    {
        Uint32 currentTime = SDL_GetTicks();
        float deltaTime = (currentTime - previousTime) / 1000.0f; // chuyển từ milisecond sang second chia cho 1000
        previousTime = currentTime;                               // gắn thời gian cho frame hiên tại để biết từ thời điểm frame này sang frame mới tiếp tục là bao nhiêu

        // test xem bóng hoạt động đúng chưa
        update(deltaTime);
        handleEvents(deltaTime);
        render();
    }
}

// tra lai tai nguyen cho os
void Game::cleanUp()
{
    if (renderer)
    {
        SDL_DestroyRenderer(renderer);
    }
    if (window)
    {
        SDL_DestroyRenderer(renderer);
    }
    SDL_Quit();
}
