#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class ScoreUI
{
public:
    ScoreUI();
    ~ScoreUI();

    bool initFontSystem();

    bool loadTexture();
    SDL_Texture *createTextTexture(const std::string &text, SDL_Rect &rect);

    void createFontResource(int &score, int &life);
    void createFrame();

    void renderLife();
    void renderScore();

    void renderFrame(SDL_Renderer *renderer, SDL_Rect &horizontalFrame, SDL_Rect &verticalFrame);

    void clean();

    SDL_Rect horRect;
    SDL_Rect verRect;

    TTF_Font *font;

    SDL_Texture *scoreTexture;
    SDL_Rect scoreRect;

    SDL_Texture *lifeTexture;
    SDL_Rect lifeRect;
};