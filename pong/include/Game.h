// include in this header : pragma once , SDL2/SDL.h
#pragma once
#include <SDL2/SDL.h>

// declare : class class_name {}
class Game
{
    // function declare function can use outside
public:
    // contructor: initlize member variable
    Game();
    // destructor : call after int main() {} out of the scope
    ~Game();

    // return_type init game
    bool init();
    // return_type run
    void run();

    // function : only class can use
private:
    // enum viết đầy đủ là gì ? cách để truy cập biến trong một class ? tại sao ở các biến tạo trong header ở trong các function có thể dùng được luôn mà cái này lại phải viết thế này Screen::MENU ? enum là thể lại gì trong c++ ? tại sao class Game  không cần cái gì đứng trước nó như enum class Screen ? khi tuyên bố thế này nó hoạt động thể nào trong phần cứng hoặc phần mềm ?
    enum class Screen
    {
        MENU,
        PLAYING,
        GAMEOVER,
    };

    Screen currentScreen;
    bool ballFrozen;
    // update
    void update(float delta);
    // handleEvents
    void handleEvents(float delta);
    // resetBall(int direction)
    void resetBall(int direction);
    // render
    void render();
    // cleanUp()
    void cleanUp();

    // SDL: pointer
    //  window lam cai gi ?
    SDL_Window *window;
    // renderer lam cai gi ? tai sao tham so cua renderer chua ca window
    SDL_Renderer *renderer;

    // boolean for loop
    bool running;
    // paddleLeft
    float paddleLeftX;
    float paddleLeftY;
    // paddleRight
    float paddleRightX;
    float paddleRightY;
    // paddle Speed
    float paddleSpeed;
    // ball
    float ballX;
    float ballY;
    float ballVelX;
    float ballVelY;

    // add point
    int rightPoint;
    int leftPoint;
};