#include <SDL2/SDL.h>

class Pong
{
public:
    Pong();
    ~Pong();

    bool init();
    void run();

private:
    bool initVideoSys();
    bool createWin();
    bool createRen();

    void handleInputs();
    void updateSim();
    void renderFrame();

    void clean();

    bool isRunning;

    SDL_Window *window;
    SDL_Renderer *renderer;

    SDL_Event event;
};
