#include <SDL2/SDL.h>

class Game
{
public:
    // constructor
    Game();
    // destructor
    ~Game();

    // create window, renderer , running set to true , return true
    bool init();
    // create game loop: render() , handleEvents() , update(), deltaTime: about frame update
    void run();

private:
    // create update the ball
    void update(float delta);
    // create render : ball , paddle , window color
    void render();
    // create handleEvents: keystate , listen to quitevent window + Q or ctrl + shift + w
    void handleEvents();
    // create cleanUp(): destroy window, renderer , quit
    void cleanUp();
    // create collision
    bool collision;
    // declare var bool running for game loop
    bool running;
    // create SDL_Window* , SDL_Renderer* , SDL_Event
    SDL_Event event;
    SDL_Window *window;
    SDL_Renderer *renderer;
    // paddle & ball; speed
    float paddleX;
    float paddleY;
    float paddleSpeed;

    float ballX;
    float ballY;
    float ballVelX;
    float ballVelY;
    const float timeFrame = 1.0f / 60.0f; // 1 second divive 60 frames => 16.67 ms 1 frame
};