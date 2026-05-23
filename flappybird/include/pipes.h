#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>

class Pipe
{
    public:

    Pipe();
    ~Pipe();

    void clean();

    bool init(SDL_Renderer *renderer);
    void update(float delta);
    void render(SDL_Renderer *renderer);

    void create(float delta, int rightWin);

    private:
    SDL_Texture* pipe_texture;
    
    struct Coor
    {
        SDL_Rect rect;  
    };

    float velX;
    int y_random;

    Coor coor;

    std::vector<Coor> pipes;

    float spawn_timer;

};