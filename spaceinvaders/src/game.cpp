
#include <iostream>
#include <algorithm>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <game.h>

SpaceInvaders::SpaceInvaders() :
{
}

bool SpaceInvaders::init()
{
    connectVideoHandler();
    connectImageHandler();
    createWindow();
    connectBackend();
    loadPicture();
    createDick();
    createPussy();

    isRunning = true;
    return true;
}
void SpaceInvaders::run()
{
    handleEvents();
    updateSimulation();
    renderFrame();
}

void SpaceInvaders::handleEvents()
{
    quitEvents();
    playEvents();
}
void SpaceInvaders::updateSimulation()
{
    updateDickMovement();
    updateDickCollision();
    updateSpermMovement();
    updateSpermCollision();
}
void SpaceInvaders::renderFrame()
{
    renderSDL();
    renderDick();
    renderPussy();
    renderSperm();
}

SpaceInvaders::~SpaceInvaders()
{
    cleanUp();
}