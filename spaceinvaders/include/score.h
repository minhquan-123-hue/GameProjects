#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class ScoreUI
{
public:
    ScoreUI();
    ~ScoreUI();

    void createFrame();

    bool initFontSystem();
    void createFontResource();
    SDL_Texture *createTextTexture(SDL_Renderer *renderer, const std::string &text, SDL_Rect &rect);

    void updateScore(SDL_Renderer *renderer, int &score);
    void updateLife(SDL_Renderer *renderer, int &life);
    void createFontState(SDL_Renderer *renderer);

    void render(SDL_Renderer *renderer);
    void renderLife(SDL_Renderer *renderer);
    void renderScore(SDL_Renderer *renderer);
    void renderFrame(SDL_Renderer *renderer, SDL_Rect &horizontalFrame, SDL_Rect &verticalFrame);

    void renderMenu(SDL_Renderer *renderer);
    void renderGameOver(SDL_Renderer *renderer);
    void renderWin(SDL_Renderer *renderer);

    void clean();

    SDL_Rect horRect;
    SDL_Rect verRect;

    TTF_Font *font; // cái này phải trả lại tài nguyên sau khi dùng xong

    SDL_Texture *scoreTexture; // cái này phải trả lại
    SDL_Rect scoreRect;

    SDL_Texture *lifeTexture; // cái này phải trả lại
    SDL_Rect lifeRect;

    // MENU
    SDL_Texture *menuTexture;
    SDL_Rect menuRect;

    // GAMEOVER
    SDL_Texture *gameoverTexture;
    SDL_Rect gameoverRect;

    // WIN
    SDL_Texture *winTexture;
    SDL_Rect winRect;
};