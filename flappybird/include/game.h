#include <SDL2/SDL.h>

class Game
{
    public:

    Game();
    ~Game();

    bool init();
    void run();
    
    private:

    // kết nối với phần cứng
    bool wakeup_SDL();
    bool create_Win();
    bool connect_Backend();
    

    void handle_Input();
    void update_Sim(float dt);
    void render_Frame();

    void clean_Up();

    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Event event;

    bool is_Running;
};
