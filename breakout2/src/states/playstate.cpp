#include "../../lib/states/playstate.h"

#include <iostream>

PlayState::PlayState(GraphicManager* graphicManager)
    : gfxMgr(graphicManager), soundMgr(nullptr)
{
}

PlayState::~PlayState()
{
}

// init() resource
void PlayState::setSoundManager(SoundManager* soundManager)
{
    soundMgr = soundManager;
}

void PlayState::onEnter()
{
    if (gfxMgr == nullptr)
    {
        std::cerr << "PlayState: GraphicManager is null." << std::endl;
        return;
    }

    SDL_Texture* paddleTexture = gfxMgr->getTexture("paddle");
    SDL_Texture* ballTexture = gfxMgr->getTexture("ball");

    if (paddleTexture == nullptr)
    {
        std::cerr << "PlayState: paddle texture not loaded." << std::endl;
        return;
    }

    paddle.setTexture(paddleTexture);
    ball.setTexture(ballTexture);
    ball.setSoundManager(soundMgr);

    // (x, y, width, height) inside breakout.png
    paddle.setSourceRect({32, 64, 64, 16});
    ball.setSourceRect({96,48,8,8});

    paddle.setWorldBounds(
        0,
        800,
        0,
        600);

    ball.setWorldBounds(
        0,800,0,600
    );

    paddle.setPosition(
        (800 - paddle.getWidth()) / 2.0f,
        600.0f - 60.0f);
    
    ball.setPosition(396.0f, 250.0f);

    paddle.setSpeed(500.0f);
    ball.setVelocity(250.0f, -250.0f);
}

void PlayState::onExit()
{
}

void PlayState::handleInput(const SDL_Event& ev)
{
    // Paddle reads keyboard directly in update().
    (void)ev;
}

void PlayState::update(float dt)
{
    paddle.update(dt);
    ball.update(dt);

    bool overlapX =
    ball.getX() < paddle.getX() + paddle.getWidth() &&
    ball.getX() + ball.getWidth() > paddle.getX();

    bool overlapY =
        ball.getY() < paddle.getY() + paddle.getHeight() &&
        ball.getY() + ball.getHeight() > paddle.getY();

    if (overlapX && overlapY)
    {
        ball.setPosition(
            ball.getX(),
            paddle.getY() - ball.getHeight());

        ball.bounceVertical();

        if (soundMgr)
            soundMgr->playSound("brick-hit-1");
    }
}

void PlayState::render(SDL_Renderer* renderer)
{
    if (renderer == nullptr)
    {
        return;
    }

    SDL_Texture* background = gfxMgr->getTexture("background");

    if (background != nullptr)
    {
        SDL_RenderCopy(
            renderer,
            background,
            nullptr,
            nullptr);
    }

    paddle.render(renderer);
    ball.render(renderer);
}