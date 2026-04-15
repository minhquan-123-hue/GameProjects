#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class ScoreUI
{
public:
    // tạo constructor: hàm đặc biệt của struct/class để biến các em biến thành viên là giá trị sạch ngay từ khi object được tạo ra
    ScoreUI();
    ~ScoreUI(); // destructor: giải phóng hết tài nguyên của C++ và SDL

    // tạo khung trước
    void createFrame();
    void createFont(SDL_Renderer *renderer);

    // khởi tạo hệ thống xử lý phông chữ của OS
    bool initFontSystem();
    bool loadFont(); // tải phông chữ sau khi hệ thống xử lý phông hoạt động

    // copy bitmap sang vram tí vẽ cho nhanh, và tạo kích thước cho phông chữ dựa trên thuật toán vẽ phông
    SDL_Texture *createTextTexture(SDL_Renderer *renderer, const std::string &text, SDL_Rect &rect);

    // tạo tài nguyên phông chữ và cập nhật khi va chạm
    void updateScore(SDL_Renderer *renderer, int &score);
    void updateLife(SDL_Renderer *renderer, int &life);

    // tạo hình vẽ thay đổi mỗi khung hình
    void render(SDL_Renderer *renderer);
    void renderScore(SDL_Renderer *renderer);
    void renderLife(SDL_Renderer *renderer);
    void renderFrame(SDL_Renderer *renderer, SDL_Rect &verRect, SDL_Rect &horRect);
    void renderMenu(SDL_Renderer *renderer);
    void renderGameover(SDL_Renderer *renderer);
    void renderWin(SDL_Renderer *renderer);

    void clean();

    // biến khung hình
    SDL_Rect verRect;
    SDL_Rect horRect;

    // biến texture vẽ điểm số , vẽ mạng
    TTF_Font *font;

    SDL_Texture *scoreTexture;
    SDL_Rect scoreRect;

    SDL_Texture *lifeTexture;
    SDL_Rect lifeRect;

    // biến vẽ : phần MENU, GAMEOVER, WIN
    SDL_Texture *menuTexture;
    SDL_Rect menuRect;

    SDL_Texture *gameoverTexture;
    SDL_Rect gameoverRect;

    SDL_Texture *winTexture;
    SDL_Rect winRect;
};