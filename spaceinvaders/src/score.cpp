#include <iostream>
#include <score.h>

ScoreUI::ScoreUI() : font(nullptr),
                     scoreTexture(nullptr),
                     lifeTexture(nullptr) {}
ScoreUI::~ScoreUI()
{
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

// vẽ điểm bằng font
// khởi tạo hệ thống xử lý phông chữ
bool ScoreUI::initFontSystem()
{
    int isFont = TTF_Init(); // BUG: mai hỏi : có phải hỏi OS tìm bật chương trình xử lý font lên không ?

    if (isFont == -1)
    {
        std::cerr << "không khởi tạo được hệ thống xử lý font: " << TTF_GetError() << std::endl;
        return false;
    }
    return true;
}

// tải phông chữ lên
bool ScoreUI::loadFont()
{
    font = TTF_OpenFont("../assets/font.ttf", 48); // BUG: mai hỏi

    if (font == nullptr)
    {
        std::cerr << "đường dẫn tải font không đúng: " << std::endl;
        return false;
    }
    return true;
}

// tạo texture cho font + với văn bản
SDL_Texture *ScoreUI::createTextTexture(SDL_Renderer *renderer, const std::string &text, SDL_Rect &rect)
{
    SDL_Color color = {255, 255, 255, 255}; // BUG: mai hỏi

    SDL_Surface *surface = TTF_RenderText_Solid(font, text.c_str(), color); // BUG: mai hỏi

    if (surface == nullptr)
    {
        std::cerr << "không tạo được bitmap trong surface" << std::endl;
    }

    // copy bitmap từ ram sang vram
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface); // BUG: mai hỏi

    rect.w = surface->w; // BUG: mai hỏi
    rect.h = surface->h;

    SDL_FreeSurface(surface);

    return texture;
}

// truyền tham số vào hàm để khởi tạo hình vẽ điểm số và mạng
void ScoreUI::updateScore(SDL_Renderer *renderer, int &score)
{
    std::string scoreText = "Score: " + std::to_string(score); // BUG: mai hỏi

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
