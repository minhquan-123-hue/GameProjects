#include <vector>

// systems
#include <systems/sdlmanager.h>
#include <systems/imagemanager.h>
// entities
#include <entities/background.h>
#include <entities/ground.h>
#include <entities/bird.h>
#include <entities/pipepair.h>

class Game
{
    public:

    Game();
    ~Game();

    bool init();
    void run();

    private:

    // systems 
    SDLManager sdl_manager;
    IMGManager img_manager;

    // entities 
    BackGround bg;
    Ground ground;
    Bird bird;
    
    std::vector<PipePair> pipe_pairs;
    float spawn_timer;
    void pipepairs_movement(float dt);
    void pipepairs_remove();
    void pipepairs_collide();

    void handle_input();
    void process_logic(float dt);
    void render_frame();


    // flag for loop
    bool is_running;
    
    // flag to collision
    bool is_collided;
    float last_Y;
};