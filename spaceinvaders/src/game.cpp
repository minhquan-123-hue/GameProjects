#include <dick.h>
#include <iostream>
#include <algorithm>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <game.h>
#include <pussy.h>

SpaceInvaders::SpaceInvaders() : // những con trỏ chư lưu bất kỳ địa chỉ nào
                                 window(nullptr),
                                 renderer(nullptr),

                                 isRunning(false),
                                 leftWall(0),
                                 rightWall(1000),
                                 topWall(0),
                                 bottomWall(1000),

                                 life(0),
                                 score(0),
                                 currentScreen(Screen::MENU)

{
}

bool SpaceInvaders::init()
{
    bool hasVideo = connectVideoHandler(); // 4 hàm này đều là nạp code của SDL vào thời điểm chạy
    bool hasImage = connectImageHandler();
    bool hasWindow = createWindow();
    bool hasBackend = connectBackend();
    bool hasPicture = loadPicture();
    bool hasFontSystem = scoreUI.initFontSystem();
    bool hasFont = scoreUI.loadFont();
    bool hasAudio = sound.initSoundSys();

    createResource();

    if (!hasVideo || !hasImage || !hasBackend || !hasPicture || !hasFont || !hasFontSystem || !hasWindow || !hasAudio)
    {
        std::cout << "init đã failed" << std::endl;
        return false;
    }

    isRunning = true;
    return true;
}
void SpaceInvaders::run()
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

        updateCollision();

        dick.updateMovement();
        dick.updateCollision(leftWall, rightWall);
        dick.updateRespawn();

        sperm.updateMovement();
        sperm.updateCollision();

        pussy.updateMovement();
        pussy.updateCollision(leftWall, rightWall);
        pussy.shootRandom(pussyWater);

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
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    if (currentScreen == Screen::MENU)
    {
        scoreUI.renderMenu(renderer);
    }
    else if (currentScreen == Screen::PLAYING)
    {
        dick.render(renderer);
        sperm.render(renderer);
        pussy.render(renderer);
        pussyWater.render(renderer);

        scoreUI.render(renderer);
    }
    else if (currentScreen == Screen::GAMEOVER)
    {
        scoreUI.renderGameover(renderer);
    }
    else if (currentScreen == Screen::WIN)
    {
        scoreUI.renderWin(renderer);
    }

    SDL_RenderPresent(renderer);
}

SpaceInvaders::~SpaceInvaders()
{
    cleanUp();
}

void SpaceInvaders::cleanUp()
{
    if (renderer)
    {
        SDL_DestroyRenderer(renderer);
    }
    if (window)
    {
        SDL_DestroyWindow(window);
    }
    IMG_Quit();
    SDL_Quit();
}
// khởi tạo tài nguyên : hỏi OS mở chương trình xử lý video, ảnh png , cửa sổ , backend, hình ảnh, ...
bool SpaceInvaders::connectVideoHandler()
{
    int initResult = SDL_Init(SDL_INIT_VIDEO);
    if (initResult != 0)
    {
        std::cout << "không thể kết nối với chương trình xử lý video" << SDL_GetError() << std::endl;
        return false;
    }
    return true;
}

bool SpaceInvaders::connectImageHandler()
{
    int initImage = IMG_Init(IMG_INIT_PNG);
    if (initImage == false)
    {
        std::cout << "không thể kết nối với chương trình xử lý ảng PNG" << SDL_GetError() << std::endl;
        return false;
    }
    return true;
}

bool SpaceInvaders::createWindow()
{
    window = SDL_CreateWindow(
        "SpaceInvaders",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        1000,
        1000,
        SDL_WINDOW_SHOWN);

    if (window == nullptr)
    {
        std::cout << "không thể tạo được cửa sổ" << SDL_GetError() << std::endl;
        return false;
    }
    return true;
}

bool SpaceInvaders::connectBackend()
{
    renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (renderer == nullptr)
    {
        std::cout << "không khởi tạo được backend" << std::endl;
        return false;
    }
    return true;
}

bool SpaceInvaders::loadPicture()
{
    bool hasDickPic = dick.loadTexture(renderer);
    bool hasSpermPic = sperm.loadTexture(renderer);
    bool hasPussyPic = pussy.loadTexture(renderer);
    bool hasPussyWaterPic = pussyWater.loadTexture(renderer);

    if (!hasDickPic || !hasSpermPic || !hasPussyPic || !hasPussyWaterPic)
    {
        std::cout << "tài nguyên ảnh tải không thành công" << std::endl;
        return false;
    }
    return true;
}

void SpaceInvaders::quitEvents()
{

    if (event.type == SDL_QUIT)
    {
        isRunning = false;
    }
}

void SpaceInvaders::playEvents()
{
    if (event.type == SDL_KEYDOWN)
    {
        if (event.key.keysym.scancode == SDL_SCANCODE_SPACE && dick.isAlive && currentScreen == Screen::PLAYING)
        {
            sperm.create(dick.body.rect.x, dick.body.rect.y);
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
    auto &sperms = sperm.sperms;   // truy vào vector một thành object thành viên trong object Sperm sperm
    auto &pussies = pussy.pussies; // truy cập vào vector một thành object thành viên trong object Pussy pussy

    for (auto spermIt = sperms.begin(); spermIt != sperms.end();)
    {
        bool hit = false;
        for (auto pussyIt = pussies.begin(); pussyIt != pussies.end();)
        {

            if (SDL_HasIntersection(&spermIt->rect, &pussyIt->rect))
            {
                score += 1;

                scoreUI.updateScore(renderer, score);

                sound.playMourn();

                pussyIt = pussies.erase(pussyIt); // chuyển sang object tiếp theo sau khi bị xóa
                hit = true;
                break;
            }
            else
            {
                ++pussyIt;
            }
        }

        if (hit == true)
        {
            spermIt = sperms.erase(spermIt);
        }
        else
        {
            ++spermIt;
        }
    }

    auto &pussywater = pussyWater.watersSystem;

    for (auto pussywaterIt = pussywater.begin(); pussywaterIt != pussywater.end();)
    {
        if (dick.isAlive && SDL_HasIntersection(&pussywaterIt->rect, &dick.body.rect))
        {

            life += 1;

            scoreUI.updateLife(renderer, life);

            sound.playCum();

            dick.die();

            pussywaterIt = pussywater.erase(pussywaterIt);
        }
        else
        {
            ++pussywaterIt;
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
    life = 0;
    score = 0;

    pussy.pussies.clear();
    pussyWater.watersSystem.clear();
    sperm.sperms.clear();

    pussy.create();

    scoreUI.updateScore(renderer, score);
    scoreUI.updateLife(renderer, life);
}

void SpaceInvaders::createResource()
{
    dick.create();

    sound.createSound();
    sound.playBGM();

    scoreUI.createFrame();
    scoreUI.createFont(renderer);

    resetScore();
}