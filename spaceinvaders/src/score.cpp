#include <score.h>
#include <iostream>

ScoreUI::ScoreUI() : font(nullptr), scoreTexture(nullptr), lifeTexture(nullptr) {}

ScoreUI::~ScoreUI()
{
    clean();
}

void ScoreUI::createFrame()
{
    horRect.x = 0;
    horRect.y = 100;
    horRect.w = 1000;
    horRect.h = 10;

    verRect.x = 498;
    verRect.y = 0;
    verRect.w = 4;
    verRect.h = 100;
}

bool ScoreUI::initFontSystem()
{
    int initFont = TTF_Init();

    if (initFont != 0)
    {
        std::cerr << "không mở được hệ thống xử phông chữ: " << SDL_GetError() << std::endl;
        return false;
    }
    return true;
}

bool ScoreUI::loadFont()
{
    font = TTF_OpenFont("../assets/font.ttf", 48);

    if (font == nullptr)
    {
        std::cerr << "không mở được đường dẫn vào font.ttf: " << TTF_GetError() << std::endl;
        return false;
    }
    return true;
}

SDL_Texture *ScoreUI::createTextTexture(SDL_Renderer *renderer, const std::string &text, SDL_Rect &rect)
{
    // tạo màu sắc bằng struct SDL_Color
    SDL_Color color = {255, 255, 255, 255};

    SDL_Surface *surface = TTF_RenderText_Solid(font, text.c_str(), color);

    if (surface == nullptr)
    {
        std::cerr << "không thể tạo bitmap và kích thước của phông chữ" << std::endl;
    }

    rect.w = surface->w;
    rect.h = surface->h;

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface); // hỏi backend tạo texture trong VRAM bằng cách copy bitmap từ surface

    SDL_FreeSurface(surface);

    return texture;
}

void ScoreUI::updateScore(SDL_Renderer *renderer, int &score)
{
    std::string scoreText = "Score: " + std::to_string(score);

    scoreRect.x = 20;
    scoreRect.y = 20;

    scoreTexture = createTextTexture(renderer, scoreText, scoreRect);
}

void ScoreUI::updateLife(SDL_Renderer *renderer, int &life)
{
    std::string lifeText = "Life: " + std::to_string(10 - life);

    lifeRect.x = 600;
    lifeRect.y = 20;

    lifeTexture = createTextTexture(renderer, lifeText, lifeRect);
}

void ScoreUI::render(SDL_Renderer *renderer)
{
    renderScore(renderer);
    renderLife(renderer);
    renderFrame(renderer, horRect, verRect);
}

void ScoreUI::renderScore(SDL_Renderer *renderer)
{
    SDL_RenderCopy(renderer, scoreTexture, nullptr, &scoreRect);
}

void ScoreUI::renderLife(SDL_Renderer *renderer)
{
    SDL_RenderCopy(renderer, lifeTexture, nullptr, &lifeRect);
}

void ScoreUI::renderFrame(SDL_Renderer *renderer, SDL_Rect &horRect, SDL_Rect &verRect)
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    SDL_RenderFillRect(renderer, &horRect);
    SDL_RenderFillRect(renderer, &verRect);
}

void ScoreUI::clean()
{
    if (font)
    {
        TTF_CloseFont(font);
    }
    if (scoreTexture)
    {
        SDL_DestroyTexture(scoreTexture);
    }
    if (lifeTexture)
    {
        SDL_DestroyTexture(lifeTexture);
    }
    TTF_Quit();
}