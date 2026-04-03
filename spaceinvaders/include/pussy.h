#include <SDL2/SDL_image.h>
#include <vector>
#include <pussywater.h>

class Pussy
{
public:
    Pussy();
    ~Pussy();

    // thêm hàm mới từ phần pussy_water
    void shootRandom(PussyWater &waterSystem);
    bool loadTexture(SDL_Renderer *renderer);
    void create();

    void updateMovement(); // di chuyển cả đoàn quân pussy hùng mạnh

    void updateCollision(int leftWall, int rightWall); // va chạm thì mới cần điều kiện tường trái phải

    void render(SDL_Renderer *renderer);
    void clean();

    struct Body
    {
        SDL_Rect rect;
        float speed;
    };

    int direction;    // 1 = sang phải , -1 sang trái
    int dropDistance; // độ rơi khi va tường , tức là đi xuống

    Body pussy;
    std::vector<Body> pussies;
    SDL_Texture *texture;

    // cờ
    bool hitWall; // va với tường trái phải
};