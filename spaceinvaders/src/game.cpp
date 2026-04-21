#include <game.h>    // thư viện chứa các hàm , biến, struct của game
#include <iostream>  // thư viên này cung cấp: hàm in chữ ra màn hình terminal (cửa sỗ gõ và hiển thị chữ)
#include <algorithm> // thư viện cung cấp hàm điểu khiển kích thước của mảng động: remove_if() sắp xếp mảng động , erase() xóa object trong mảng động

SpaceInvaders::SpaceInvaders() : renderer(nullptr),
                                 window(nullptr),
                                 leftWall(0),
                                 rightWall(1000),
                                 topWall(0),
                                 bottomWall(1000),

                                 isRunning(false),

                                 life(0),
                                 score(0),
                                 currentScreen(Screen::MENU)

{
}

bool SpaceInvaders::initSystem()
{
    bool hasVideo = conViHandler();
    bool hasImage = conImHandler();
    bool hasWindow = createWin();
    bool hasBackend = createRen();
    bool hasPicture = loadPic();
    bool hasFontSystem = scoreUI.initFontSystem();
    bool hasMusicSystem = sound.initSoundSystem();

    createResource();

    if (!hasVideo || !hasImage || !hasWindow || !hasBackend || !hasPicture || !hasFontSystem || !hasMusicSystem)
    {
        return false;
    }

    isRunning = true;
    return true;
}

void SpaceInvaders::runProgram()
{
    while (isRunning)
    {
        handleInputs();
        updateSimulation();
        renderFrame();
    }
}

void SpaceInvaders::handleInputs()
{
    while (SDL_PollEvent(&event))
    {
        quitEvents();
        playEvents();
        stateEvents();
    }
}

void SpaceInvaders::updateSimulation()
{
    if (currentScreen == Screen::PLAYING)
    {
        updateWin();
        updateLose();

        updateCollision(); // va chạm giữa object và object

        dick.updateMovement();
        dick.updateCollision(leftWall, rightWall);
        dick.updateRespawn();

        spermShady.updateMovement();
        spermShady.updateCollision(topWall + scoreUI.horRect.h + 80);

        pussyShady.updateMovement();
        pussyShady.updateCollision(leftWall, rightWall);
        pussyShady.shootRandom(pussyWater);

        pussyWater.updateMovement();
        pussyWater.updateCollision(bottomWall);
    }

    if (currentScreen == Screen::GAMEOVER || currentScreen == Screen::WIN)
    {
        resetScore();
    }
}

void SpaceInvaders::renderFrame()
{

    // thiết lập màu vẽ window (backend vẽ)
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

    // tô màu cho toàn bộ nền lên cửa sổ
    SDL_RenderClear(renderer);

    if (currentScreen == Screen::MENU)
    {
        scoreUI.renderMenu(renderer);
    }
    else if (currentScreen == Screen::PLAYING)
    {
        dick.render(renderer);

        spermShady.render(renderer);

        pussyShady.render(renderer);
        pussyWater.render(renderer);

        scoreUI.render(renderer);
    }
    else if (currentScreen == Screen::GAMEOVER)
    {
        scoreUI.renderGameOver(renderer);
    }
    else if (currentScreen == Screen::WIN)
    {
        scoreUI.renderWin(renderer);
    }

    // hiển thị của sổ và toàn bộ hình vẽ bên trong nó lên
    SDL_RenderPresent(renderer);
}

void SpaceInvaders::cleanUp()
{
    if (renderer)
    {
        SDL_DestroyRenderer(renderer); // hủy liên kết với backend
    }
    if (window)
    {
        SDL_DestroyWindow(window); // hủy cửa số
    }

    SDL_Quit(); // giải phóng tài nguyên SDL
    IMG_Quit();
}

SpaceInvaders::~SpaceInvaders() // hủy sau khi object "chết"
{
    cleanUp();
}

bool SpaceInvaders::conViHandler()
{
    // nó đơn giản là bắt đầu nói chuyện với hệ điều hành
    int initResult = SDL_Init(SDL_INIT_VIDEO);

    if (initResult != 0)
    {
        std::cout << "không khởi tạo hệ thống video thành công: " << SDL_GetError() << std::endl;
        return false; // báo lại sao để không khởi chạy phương thức object.run()
    }
    return true;
}

bool SpaceInvaders::conImHandler()
{

    // hỏi OS để giải quyết vấn đề liên quan đến ảnh (image)
    int intImage = IMG_Init(IMG_INIT_PNG);

    if (!intImage)
    {
        std::cout << "không kết nối được chương trình xử lý .PNG" << std::endl;
        return false;
    }
    return true;
}

bool SpaceInvaders::createWin()
{

    // hỏi OS tạo cửa sổ , và trả lại một con trỏ cho SDL_Window (struct) và SDL cho bạn một cái con trỏ chỉ tới struct của nó
    window = SDL_CreateWindow(  // các tham số không cần phải nhớ , chỉ cần hiểu nó làm gì
        "SpaceInvaders",        // tên của cửa sổ
        SDL_WINDOWPOS_CENTERED, // cho nằm giữa màn hình
        SDL_WINDOWPOS_CENTERED, // cho nằm giữa màn hình
        1000,                   // kích thước dài rộng của cửa sổ
        1000,
        SDL_WINDOW_SHOWN); // hiện thị lên màn hình

    // ! là đảo logic , nếu mà pointer thì sai không chạy thân code , nếu mà nullpointer thì false false = true chạy thân code
    if (!window)
    {
        std::cout << "không khởi tạo được cửa sổ: " << SDL_GetError() << std::endl;
        return false;
    }
    return true;
}

bool SpaceInvaders::createRen()
{

    // hỏi OS cho SDL kêt nối với backend để tí backend ra lệnh cho driver nói chuyện với GPU
    renderer = SDL_CreateRenderer(
        window,                                              // đưa cửa sổ cho nó để vẽ
        -1,                                                  // chọn backend mà hệ điều hành đang dùng cung cấp
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC // hỏi backend dùng GPU , và kết nối với màn hình để vòng lặp
        // phải đợi màn hình "clear" xong thì mới vẽ hình mới lên khiến vòng lặp không chạy liên tục vào gửi lệnh vẽ liên tục
    );

    // kiểm tra có backend hỗ trợ không
    if (!renderer) // dùng ! để đảo logic , nếu true tức có backend đảo thành false => vòng lặp không chạy , nếu false đảo thành true và bên trong câu điều kiện sẽ chạy
    {
        std::cout << "backend không hỗ trợ: " << SDL_GetError() << std::endl;
        return false;
    }
    return true;
}

bool SpaceInvaders::loadPic()
{
    bool hasDickPic = dick.loadTexture(renderer);

    bool hasSpermPic = spermShady.loadTexture(renderer);

    bool hasPussyPic = pussyShady.loadTexture(renderer);

    bool hasPussyWetPic = pussyWater.loadTexture(renderer);

    if (!hasDickPic || !hasSpermPic || !hasPussyPic || !hasPussyWetPic)
    {
        std::cout << "ảnh không mở đươc" << std::endl;
        return false;
    }

    return true;
}

void SpaceInvaders::quitEvents()
{
    if (event.type == SDL_QUIT) // nếu mà click vào dấu x ; và dùng alt+f4 ,.. thì chạy body của control flow
    {
        // dừng vòng lặp (không gửi lệnh vẽ nữa)
        isRunning = false;
    }
}

void SpaceInvaders::playEvents()
{

    if (event.type == SDL_KEYDOWN) // nếu SPACE được ấn thì "xuất tinh"
    {
        if (event.key.keysym.scancode == SDL_SCANCODE_SPACE && dick.isAlive)
        {
            spermShady.create(dick.dick.rect.x, dick.dick.rect.y); // dick ngoài là dick objet, dick trong là dick biến thành viên (struct)
        }
    }
}

void SpaceInvaders::stateEvents()
{
    if (event.type == SDL_KEYDOWN)
    {
        if (event.key.keysym.scancode == SDL_SCANCODE_RETURN && currentScreen == Screen::MENU)
        {
            currentScreen = Screen::PLAYING;
        }

        if (event.key.keysym.scancode == SDL_SCANCODE_R && currentScreen == Screen::GAMEOVER)
        {
            currentScreen = Screen::MENU;
        }
        if (event.key.keysym.scancode == SDL_SCANCODE_R && currentScreen == Screen::WIN)
        {
            currentScreen = Screen::MENU;
        }
    }
}

void SpaceInvaders::updateCollision()
{
    auto &sperms = spermShady.sperms;
    auto &pussies =
        pussyShady.pussies; // tùy tên bạn đặt

    for (auto spermIt = sperms.begin(); spermIt != sperms.end();)
    {
        bool hit = false;

        for (auto pussyIt = pussies.begin(); pussyIt != pussies.end();)
        {
            if (SDL_HasIntersection(&spermIt->rect, &pussyIt->rect))
            {
                pussyIt->isBroken = true;

                // xóa enemy
                score += 1;

                scoreUI.updateScore(renderer, score);

                sound.playMourn();

                hit = true;

                break;
            }
            else
            {
                ++pussyIt;
            }
        }

        if (hit)
        {
            // xóa đạn
            spermIt = sperms.erase(spermIt);
        }
        else
        {
            ++spermIt;
        }
    }

    auto &waters = pussyWater.waters;

    for (auto waterIt = waters.begin(); waterIt != waters.end();)
    {
        if (dick.isAlive && SDL_HasIntersection(&waterIt->rect, &dick.dick.rect))
        {

            dick.setHit();

            life += 1;

            scoreUI.updateLife(renderer, life);

            sound.playCum();

            dick.die(); // chết

            waterIt = waters.erase(waterIt); // xóa giọt nước "lèo"
        }
        else
        {
            ++waterIt;
        }
    }
}

void SpaceInvaders::updateWin()
{
    if (score == 50)
    {
        currentScreen = Screen::WIN;
    }
}

void SpaceInvaders::updateLose()
{
    if (life == 10)
    {
        currentScreen = Screen::GAMEOVER;
    }
}

void SpaceInvaders::resetScore()
{
    score = 0;
    life = 0;

    spermShady.sperms.clear();
    pussyWater.waters.clear();

    scoreUI.updateScore(renderer, score);
    scoreUI.updateLife(renderer, life);

    pussyShady.create();
}

void SpaceInvaders::createResource()
{
    dick.create();

    scoreUI.createFontResource();
    scoreUI.createFrame();             // khung ngang doc chua score
    scoreUI.createFontState(renderer); // texture cho tung STATE

    sound.createSoundResource();
    sound.playBGM();
    resetScore();
}