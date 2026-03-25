
#include <iostream>
#include <algorithm>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <game.h>

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
    createDick();
    createPussy();

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
    updateDickMovement();
    updateDickCollision();
    updateSpermMovement();
    updateSpermCollision();
}
void SpaceInvaders::renderFrame()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    renderDick();
    renderPussy();
    renderSperm();
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
    if (pussyTexture)
    {
        SDL_DestroyTexture(pussyTexture);
    }
    if (dickTexture)
    {
        SDL_DestroyTexture(dickTexture);
    }
    if (spermTexture)
    {
        SDL_DestroyTexture(spermTexture);
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
    dickTexture = IMG_LoadTexture(renderer, "../assets/dick.png");
    spermTexture = IMG_LoadTexture(renderer, "../assets/sperm.png");
    pussyTexture = IMG_LoadTexture(renderer, "../assets/pussy.png");

    if (dickTexture == nullptr)
    {
        std::cout << "không tải được ảnh dick lên" << std::endl;
        return false;
    }

    if (spermTexture == nullptr)
    {
        std::cout << "không tải được ảnh sperm lên" << std::endl;
        return false;
    }

    if (pussyTexture == nullptr)
    {
        std::cout << "không tải được ảnh pussy lên" << std::endl;
        return false;
    }
    return true;
}

void SpaceInvaders::createDick()
{
    dick.rect.w = 120;
    dick.rect.h = 120;
    dick.rect.x = 100;
    dick.rect.y = 900;
    dick.speed = 15;
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
            std::cout << "SPACE pressed" << std::endl;
            createSperm(); // khi mà người chưa nhấn space tạo sperm
        }
    }
}

void SpaceInvaders::updateDickMovement()
{
    const Uint8 *state = SDL_GetKeyboardState(nullptr);

    if (state[SDL_SCANCODE_LEFT])
    {
        dick.rect.x -= dick.speed;
    }
    if (state[SDL_SCANCODE_RIGHT])
    {
        dick.rect.x += dick.speed;
    }
}

void SpaceInvaders::updateDickCollision()
{
    if (dick.rect.x <= leftWall)
    {
        dick.rect.x = leftWall;
    }
    if (dick.rect.x >= rightWall - dick.rect.w)
    {
        dick.rect.x = rightWall - dick.rect.w;
    }
}

void SpaceInvaders::renderDick()
{
    SDL_RenderCopy(renderer, dickTexture, nullptr, &dick.rect);
}

void SpaceInvaders::createSperm()
{
    sperm.rect.w = 64;
    sperm.rect.h = 64;
    sperm.rect.x = dick.rect.x + (sperm.rect.w / 2);
    sperm.rect.y = dick.rect.y;
    sperm.speed = 8;

    sperms.emplace_back(sperm); // nhét object mới tạo ra vào cuối mạng động
    std::cout << sperms.size() << std::endl;
}

void SpaceInvaders::renderSperm()
{
    for (auto &sperm : sperms)
    {
        SDL_RenderCopy(renderer, spermTexture, nullptr, &sperm.rect); // dùng & toán tử địa chỉ vì hàm yêu cầu địa chỉ trong RAM vì cái này phù thuộc object mà SDL không biết là gì nó chỉ quan tâm đến địa chỉ + dữ liệu bên trong để làm việc
    }
}

void SpaceInvaders::updateSpermMovement()
{
    for (auto &sperm : sperms)
    {
        sperm.rect.y -= sperm.speed;
    }
}

void SpaceInvaders::updateSpermCollision()
{
    auto smartPointer = std::remove_if(
        sperms.begin(),
        sperms.end(),
        [](auto &sperm)
        { return sperm.rect.y < 0; });

    sperms.erase(smartPointer, sperms.end());
}

void SpaceInvaders::createPussy()
{
    int startX = 100;
    int startY = 100;
    int spaceX = 64 + 16; // kích thước của vật + khoảng cách mong muốn
    int spaceY = 64 + 16;
    int totalCols = 10;
    int totalRows = 5;

    // tạo ra 50 vòng lặp , 5 vòng ngoài chạy 10 vòng ở trong
    for (int pussyRow = 0; pussyRow < totalRows; pussyRow++)
    {
        for (int pussyCol = 0; pussyCol < totalCols; pussyCol++)
        {
            pussy.rect.w = 64;
            pussy.rect.h = 64;
            pussy.rect.x = startX + pussyCol * spaceX;
            pussy.rect.y = startY + pussyRow * spaceY;

            pussies.emplace_back(pussy);
        }
    }
}

void SpaceInvaders::renderPussy()
{
    for (auto &pussy : pussies)
    {
        SDL_RenderCopy(renderer, pussyTexture, nullptr, &pussy.rect);
    }
}
