#include <sdlmanager.h>

class Game
{
    public:

    Game();
    ~Game();

    bool init();
    void run();

    private:

    SDLManager sdl_manager;

    void handle_input();
    void process_logic(float dt);
    void render_frame();


    // flag for loop
    bool is_running;

};