#pragma once 
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>

class Ground 
{
    public:

    Ground();
    ~Ground();

    void clean();

    bool init(SDL_Renderer *renderer, int down_win, int right_win);
    void update(float dt);
    void render(SDL_Renderer *renderer);

    bool open_Path(SDL_Renderer *renderer);
    void create(int down_win , int right_win);

    private:

    SDL_Texture * ground_texture;
    
    struct Coor
    {
        SDL_Rect rect;
    };

    Coor coor;

    float speed;
    int RESET_POINT;

};