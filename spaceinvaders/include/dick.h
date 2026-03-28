#include <SDL2/SDL_image.h> // thư viên cung cấp API xử lý ảnh png

class Dick
{
public:
    Dick(); // constructor
    ~Dick();

    bool loadTexture(SDL_Renderer *renderer);
    void create();

    void updateMovement();
    void updateCollision(int leftWall, int rightWall);

    void render(SDL_Renderer *renderer);
    void clean();

    struct Body
    {
        SDL_Rect rect;
        float speed;
    };
    Body dick;
    SDL_Texture *texture;
};