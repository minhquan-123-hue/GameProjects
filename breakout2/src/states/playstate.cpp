#include "../../lib/states/playstate.h"

#include <iostream>

PlayState::PlayState(GraphicManager* graphicManager)
    : gfxMgr(graphicManager)
{
}

PlayState::~PlayState()
{
}

void PlayState::onEnter()
{
    if (gfxMgr == nullptr)
    {
        std::cerr << "PlayState: GraphicManager is null." << std::endl;
        return;
    }

    SDL_Texture* paddleTexture = gfxMgr->getTexture("paddle");

    if (paddleTexture == nullptr)
    {
        std::cerr << "PlayState: paddle texture not loaded." << std::endl;
        return;
    }

    paddle.setTexture(paddleTexture);

    // (x, y, width, height) inside breakout.png
    paddle.setSourceRect({32, 64, 64, 16});

    paddle.setWorldBounds(
        0,
        800,
        0,
        600);

    paddle.setPosition(
        (800 - paddle.getWidth()) / 2.0f,
        600.0f - 60.0f);

    paddle.setSpeed(500.0f);
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
}