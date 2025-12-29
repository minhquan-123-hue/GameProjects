// let fucking go
// include
#include <SDL2/SDL.h>
#pragma once

// create class : public , private

class Game
{
    // fucntion use outside of the class (API)
public:
    // constructor
    Game();
    // destructor
    ~Game();

    // return_type init
    bool init();
    // fuction only can use by the class
    // return_type run
    void run();

private:
    void render();
    // sub_render: state1:MENU, state2:PLAYING, state3:GAMEOVER
    void renderMenu();
    void renderGame();
    void renderGameOver();
    // handle input
    void handleEvents(float delta);
    // update: ball movement
    void update(float delta);
    // reset ball after lose -5 points
    void resetBall(int direction);
    // parent render : control state (what screen)
    // cleanUP: releash resource :window , renderer
    void cleanUp();

    // create enum class {}
    enum class Screen
    {
        MENU,
        PLAYING,
        GAMEOVER
    };

    // window size
    int windowHeight = 1000;
    int windowWidth = 1000;
    // Screen var
    Screen currentScreen;
    // BALL STOP
    bool ballFrozen;
    // initialize var
    // condition for loop
    bool running;
    // SDL pointer: the thick brush (to draw) , the paper to draw , tạo thêm cả Event(sự kiện) lắng nghe QUIT
    SDL_Event event;
    SDL_Window *window;
    SDL_Renderer *renderer;
    // create object: paddle: left, right ; ball (position,speed)
    float paddleLeftX;
    float paddleLeftY;
    float paddleRightX;
    float paddleRightY;
    float paddleSpeed;
    float ballX;
    float ballY;
    float ballVelX;
    float ballVelY;
    // points : left , right
    int leftPoint;
    int rightPoint;
};