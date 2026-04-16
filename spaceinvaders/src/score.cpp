#include <iostream>
#include <score.h>

ScoreUI::ScoreUI() : font(nullptr),
                     scoreTexture(nullptr),
                     lifeTexture(nullptr) {}
ScoreUI::~ScoreUI()
{
    clean();
}

// tạo khung
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

void ScoreUI::createFontState(SDL_Renderer *renderer)
{
    std::string textMenu = "RETURN - sperminvaders";

    menuTexture = createTextTexture(renderer, textMenu, menuRect);

    menuRect.x = 10;
    menuRect.y = 10;

    std::string textGameOver = "R - a wet pussy make you cum 1000 times";

    gameoverTexture = createTextTexture(renderer, textGameOver, gameoverRect);

    gameoverRect.x = 10;
    gameoverRect.y = 10;

    std::string textWin = "R - kill moster pussyWet. YEAH!!!!!!!";

    winTexture = createTextTexture(renderer, textWin, winRect);

    winRect.x = 10;
    winRect.y = 10;
}
// vẽ điểm bằng font
// khởi tạo hệ thống xử lý phông chữ
bool ScoreUI::initFontSystem()
{
    int isFont = TTF_Init();

    if (isFont == -1)
    {
        std::cerr << "không khởi tạo được hệ thống xử lý font: " << TTF_GetError() << std::endl;
        return false;
    }
    return true;
}

// tải phông chữ lên
void ScoreUI::createFontResource()
{
    font = TTF_OpenFont("../assets/font.ttf", 48);

    if (font == nullptr)
    {
        std::cerr << "đường dẫn tải font không đúng: " << std::endl;
    }
}

// tạo texture cho font + với văn bản
SDL_Texture *ScoreUI::createTextTexture(SDL_Renderer *renderer, const std::string &text, SDL_Rect &rect)
{
    SDL_Color color = {255, 255, 255, 255};

    SDL_Surface *surface = TTF_RenderText_Solid(font, text.c_str(), color);
    if (surface == nullptr)
    {
        std::cerr << "không tạo được bitmap trong surface" << std::endl;
    }

    // copy bitmap từ ram sang vram
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

    rect.w = surface->w;
    rect.h = surface->h;

    SDL_FreeSurface(surface);

    return texture;
}

// truyền tham số vào hàm để khởi tạo hình vẽ điểm số và mạng
void ScoreUI::updateScore(SDL_Renderer *renderer, int &score)
{

    std::string scoreText = "Score: " + std::to_string(score);

    scoreTexture = createTextTexture(renderer, scoreText, scoreRect);

    scoreRect.x = 20; // cái font nó chỉ tạo cho mình width và height của chữ thôi còn về vị trí x,y mình phải tự chỉnh
    scoreRect.y = 20;
}

void ScoreUI::updateLife(SDL_Renderer *renderer, int &life)
{
    std::string lifeText = "Life: " + std::to_string(10 - life);

    lifeTexture = createTextTexture(renderer, lifeText, lifeRect);

    lifeRect.x = 600;
    lifeRect.y = 20;
}

void ScoreUI::render(SDL_Renderer *renderer)
{
    renderFrame(renderer, horRect, verRect);
    renderScore(renderer);
    renderLife(renderer);
}

// vẽ khung
void ScoreUI::renderFrame(SDL_Renderer *renderer, SDL_Rect &horRect, SDL_Rect &verRect)
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    // tô màu
    SDL_RenderFillRect(renderer, &horRect);
    SDL_RenderFillRect(renderer, &verRect);
}

void ScoreUI::renderScore(SDL_Renderer *renderer)
{
    SDL_RenderCopy(renderer, scoreTexture, nullptr, &scoreRect);
}

void ScoreUI::renderLife(SDL_Renderer *renderer)
{
    SDL_RenderCopy(renderer, lifeTexture, nullptr, &lifeRect);
}

void ScoreUI::renderMenu(SDL_Renderer *renderer)
{
    SDL_Rect *menuPtr = &menuRect;

    SDL_RenderCopy(renderer, menuTexture, nullptr, menuPtr);
}

void ScoreUI::renderGameOver(SDL_Renderer *renderer)
{
    SDL_Rect *gameoverPtr = &gameoverRect;

    SDL_RenderCopy(renderer, gameoverTexture, nullptr, gameoverPtr);
}

void ScoreUI::renderWin(SDL_Renderer *renderer)
{
    SDL_Rect *winPtr = &winRect;

    SDL_RenderCopy(renderer, winTexture, nullptr, winPtr);
}

void ScoreUI::clean()
{
    if (lifeTexture)
    {
        SDL_DestroyTexture(lifeTexture);
    }
    if (scoreTexture)
    {
        SDL_DestroyTexture(scoreTexture);
    }
    if (font)
    {

        TTF_CloseFont(font);
    }
    TTF_Quit();
}
