// systems
#include <systems/sdlmanager.h>
#include <systems/imagemanager.h>
// entities
#include <entities/background.h>

class Game
{
    public:

    Game();
    ~Game();

    bool init();
    void run();

    private:

    SDLManager sdl_manager;
    IMGManager img_manager;
    BackGround bg;
    
    void handle_input();
    void process_logic(float dt);
    void render_frame();


    // flag for loop
    bool is_running;

};