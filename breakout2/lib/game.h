#pragma once
#include <systems/sdl_manager.h>

class Game
{
public:
    Game();
    ~Game();

    bool init();
    void clean();
    void run();

    void handle_Input();
    void process_Logic();
    void render();

    bool is_Running() const;

private:
    bool running;
    SDLManager sdl_manager;
};
