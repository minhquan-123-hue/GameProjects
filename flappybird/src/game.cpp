#include <game.h>
#include <iostream> // thư viện xử lý input/output in ra terminal 
#include <cstdlib>
#include <ctime>

Game::Game(): window(nullptr),
            renderer(nullptr),
            is_Running(false),
            
            top_win(0),
            down_win(1000),
            left_win(0),
            right_win(1000)
            
{}

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
    IMG_Quit();
}

bool Game::init()
{   
    srand(time(NULL));

    bool has_resources = init_resource();
    bool has_objects = init_subobjects();

    if (!has_resources || !has_objects)
    {
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

        if (event.type == SDL_KEYDOWN)
        {
            bird.input(event);
        }
    }
}

void Game::update_Sim(float dt)
{
    parallax_effect(dt);
    
    bird.update(dt);
    pipe.update(dt, down_win);

}

void Game::render_Frame()
{
    SDL_SetRenderDrawColor(renderer, 0,0,0,255);
    SDL_RenderClear(renderer);

    background.render(renderer);
    pipe.render(renderer);
    ground.render(renderer);
    bird.render(renderer);

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
        right_win,
        down_win,
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
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    if (renderer == nullptr)
    {
        std::cerr << "không kết nối được với backend" << std::endl;
        return false;
    }
    return true;
}

bool Game::image_Handler()
{
    int image_handler = IMG_Init(IMG_INIT_PNG);

    if (image_handler == 0)
    {
        std::cerr << "ko mở được bộ mã xử lý hình ảnh" << std::endl;
        return false;
    }
    return true;
}

bool Game::init_resource()
{
        
    bool has_Sys = wakeup_SDL();
    bool has_Win = create_Win();
    bool has_Backend = connect_Backend();
    bool image_handler = image_Handler();


    if (!has_Sys || !has_Win || !has_Backend || !image_handler)
    {
        std::cerr << "khởi tạo tài nguyên bị lỗi" << std::endl;
        return false;
    }

    return true;
}

bool Game::init_subobjects()

{
    // object tự tạo 
    bool has_Background = background.init(renderer);
    bool has_Ground = ground.init(renderer, down_win, right_win);
    bool has_bird = bird.init(renderer);
    bool has_pipes = pipe.init(renderer, right_win);

    if (!has_Background || !has_Ground || !has_bird || !has_pipes)
    {
        std::cerr << "some of the object can't created successfully" << std::endl;
        return false;
    }

    return true;
}

void Game::parallax_effect(float dt)
{
    background.update(dt);
    ground.update(dt);
}

