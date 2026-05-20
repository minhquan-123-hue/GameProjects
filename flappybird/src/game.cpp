#include <game.h>
#include <iostream> // thư viện xử lý input/output in ra terminal 

Game::Game(): window(nullptr),renderer(nullptr),is_Running(false){}
Game::~Game()
{
    clean_Up();
}

void Game::clean_Up()
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

bool Game::init()
{   
    bool has_Sys = wakeup_SDL();
    bool has_Win = create_Win();
    bool has_Backend = connect_Backend();

    bool has_Background = background.init(renderer);

    if (!has_Sys || !has_Win || !has_Backend || !has_Background)
    {
        std::cerr << "khởi tạo tài nguyên bị lỗi" << std::endl;
        return false;
    }

    is_Running = true;
    return true;

}

void Game::run()
{
    // đo khoảng cách giữa 2 frame
    // preTime scope ở ngoài vòng lặp vì nó cần
    // được lưu trự lại liên tục
    // vòng curTime thì liên tục được tạo mới
    Uint32 preTime = SDL_GetTicks();
    while(is_Running)
    {
        Uint32 curTime = SDL_GetTicks();
        float dt = (curTime - preTime) / 1000.0f;
        preTime = curTime;

        handle_Input();
        update_Sim(dt);
        render_Frame();

    }
}

void Game::handle_Input()
{
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            is_Running = false;
        }
    }
}

void Game::update_Sim(float dt)
{
    background.update(dt);
}

void Game::render_Frame()
{
    SDL_SetRenderDrawColor(renderer, 0,0,0,255);
    SDL_RenderClear(renderer);

    background.render(renderer);
    
    SDL_RenderPresent(renderer);
}

bool Game::wakeup_SDL()
{
    bool initResult = SDL_Init(SDL_INIT_VIDEO);

    if (initResult != 0)
    {
        std::cerr << "không nạp được SDL vào ram" << SDL_GetError() << std::endl;
        return false;
    }
    return true;
}

bool Game::create_Win()
{
    window = SDL_CreateWindow(
        "sextoy bird",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        1000,
        1000,
        SDL_WINDOW_SHOWN
    );

    if (window == nullptr)
    {
        std::cerr << "không tạo được cửa sổ" << std::endl;
        return false;
    }
    return true;
}

bool Game::connect_Backend()
{
    renderer = SDL_CreateRenderer(
        window,
        -1, // rendering driver 
        SDL_RENDERER_ACCELERATED 
    );

    if (renderer == nullptr)
    {
        std::cerr << "không kết nối được với backend" << std::endl;
        return false;
    }
    return true;
}