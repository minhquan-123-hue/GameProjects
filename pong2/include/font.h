#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>
#include <string>

class Font
{
    public:

    Font();
    ~Font();

    void clean();

    bool initFontSys();
    
    void create(SDL_Renderer *renderer);

    SDL_Texture * createTextTexture(
        SDL_Renderer *renderer ,
        const std::string text, 
        SDL_Rect &rect);

    void renderMenu(SDL_Renderer *renderer);
    void render1Win(SDL_Renderer *renderer);
    void render2Win(SDL_Renderer *renderer);

    TTF_Font *font;

    SDL_Rect menuRect;
    SDL_Texture *menuTexture;

    SDL_Rect win1Rect;
    SDL_Texture *win1Texture;

    SDL_Rect win2Rect;
    SDL_Texture *win2Texture;
      
};