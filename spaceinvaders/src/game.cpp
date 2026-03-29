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
                                 bottomWall(1000)

{
}

bool SpaceInvaders::init()
{
    bool hasVideo = connectVideoHandler(); // 4 hàm này đều là nạp code của SDL vào thời điểm chạy
    bool hasImage = connectImageHandler();
    bool hasWindow = createWindow();
    bool hasBackend = connectBackend();
    bool hasPicture = loadPicture();
    dick.create();
    pussy.create();

    if (!hasVideo || !hasImage || !hasBackend || !hasPicture)
    {
        std::cout << "init đã failed" << std::endl;
        return false;
    }
    isRunning = true;
    return true;
}
void SpaceInvaders::run()
{
    // BUG: cửa số không chạy vì quên vòng lặp ở đâu , khiên mỗi hàm chỉ được gọi 1 lần , và biến mất
    while (isRunning)
    {
        handleEvents();
        updateSimulation();
        renderFrame();
    }
}

void SpaceInvaders::handleEvents()
{
    while (SDL_PollEvent(&event))
    {
        quitEvents();

        // hiện tại chưa gọi hàm tạo playEvents()
        playEvents();
    }
}
void SpaceInvaders::updateSimulation()
{
    dick.updateMovement();
    dick.updateCollision(leftWall, rightWall);
    sperm.updateMovement();
    sperm.updateCollision();
    pussy.updateMovement();
    pussy.updateCollision(leftWall, rightWall);
}
void SpaceInvaders::renderFrame()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    dick.render(renderer);
    sperm.render(renderer);
    pussy.render(renderer);
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

    dick.clean();
    sperm.clean();
    pussy.clean();

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

    if (!hasDickPic || !hasSpermPic || !hasPussyPic)
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
        if (event.key.keysym.scancode == SDL_SCANCODE_SPACE)
        {
            sperm.create(dick.body.rect.x, dick.body.rect.y);
        }
    }
}
