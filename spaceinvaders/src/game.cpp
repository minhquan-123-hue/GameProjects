#include <game.h>
// thư viên này cung cấp: hàm in chữ ra màn hình terminal (cửa sỗ gõ và hiển thị chữ)
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <string>
#include <vector>
#include <algorithm> // thư viên cung cấp thuật toán sắp xếp mảng động

// tạo constructor để khởi tạo các giá trị đi liền với "đối tượng"
SpaceInvaders::SpaceInvaders() : renderer(nullptr), // chưa chỉ tới struct SDL_Renderer
                                 window(nullptr),   // chưa chỉ tới struct SDL_Window
                                 dickTexture(nullptr),

                                 isRunning(false), // cờ chưa đúng vì chưa biết SDL đã kết nối được với OS chưa
                                 leftWall(0),
                                 rightWall(1000),
                                 topWall(0),
                                 bottomWall(1000)

{
    dick.rect.x = 100;
    dick.rect.y = 900;
    dick.rect.w = 100;
    dick.rect.h = 100;
    dick.speed = 20;
}

bool SpaceInvaders::init()
{
    // nó đơn giản là bắt đầu nói chuyện với hệ điều hành
    int initResult = SDL_Init(SDL_INIT_VIDEO);

    if (initResult != 0)
    {
        std::cout << "không khởi tạo hệ thống video thành công: " << SDL_GetError() << std::endl;
        return false; // báo lại sao để không khởi chạy phương thức object.run()
    }

    // hỏi OS để giải quyết vấn đề liên quan đến ảnh (image)
    int intImage = IMG_Init(IMG_INIT_PNG);

    // hỏi OS tạo cửa sổ , và trả lại một con trỏ cho SDL_Window (struct) và SDL cho bạn một cái con trỏ chỉ tới struct của nó
    window = SDL_CreateWindow(  // các tham số không cần phải nhớ , chỉ cần hiểu nó làm gì
        "SpaceInvaders",        // tên của cửa sổ
        SDL_WINDOWPOS_CENTERED, // cho nằm giữa màn hình
        SDL_WINDOWPOS_CENTERED, // cho nằm giữa màn hình
        1000,                   // kích thước dài rộng của cửa sổ
        1000,
        SDL_WINDOW_SHOWN); // hiện thị lên màn hình

    // ! là đảo logic , nếu mà pointer thì sai không chạy thân code , nếu mà nullpointer thì false false = true chạy thân code
    if (!window)
    {
        std::cout << "không khởi tạo được cửa sổ: " << SDL_GetError() << std::endl;
        return false;
    }

    // hỏi OS cho SDL kêt nối với backend để tí backend ra lệnh cho driver nói chuyện với GPU
    renderer = SDL_CreateRenderer(
        window,                                              // đưa cửa sổ cho nó để vẽ
        -1,                                                  // chọn backend mà hệ điều hành đang dùng cung cấp
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC // hỏi backend dùng GPU , và kết nối với màn hình để vòng lặp
        // phải đợi màn hình "clear" xong thì mới vẽ hình mới lên khiến vòng lặp không chạy liên tục vào gửi lệnh vẽ liên tục
    );

    // kiểm tra có backend hỗ trợ không
    if (!renderer) // dùng ! để đảo logic , nếu true tức có backend đảo thành false => vòng lặp không chạy , nếu false đảo thành true và bên trong câu điều kiện sẽ chạy
    {
        std::cout << "backend không hỗ trợ: " << SDL_GetError() << std::endl;
        return false;
    }

    // tải hình ảnh tàu chiến lên
    dickTexture = IMG_LoadTexture(renderer, "../assets/dick.png");

    if (!dickTexture)
    {
        std::cout << "không mở được file ảnh" << std::endl;
    }
    // khi mà có đủ : màn hình , backend , SDL kết nối với OS thành công
    // thì cho phép cờ của vòng lặp thành đúng
    isRunning = true;
    return true;
}

void SpaceInvaders::createSperm()
{
    Sperm sperm;
    sperm.rect.w = 20;
    sperm.rect.h = 30;
    sperm.rect.x = dick.rect.x + dick.rect.w / 2 - 2;
    sperm.rect.y = dick.rect.y - sperm.rect.h;

    sperm.speed = 8;

    sperms.push_back(sperm);
}

void SpaceInvaders::killSperm()
{

    auto newEnd = std::remove_if(
        sperms.begin(),
        sperms.end(),
        [](Sperm &sperm)
        { return sperm.rect.y < 0; 
        std::cout << "kill" << std::endl; });

    sperms.erase(newEnd, sperms.end());
}

void SpaceInvaders::renderSperm()
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255); // màu là dùng chung nên không để ở trong vòng lặp, thiết lập 1 lần dùng cho tất cả
    for (auto &sperm : sperms)
    {
        SDL_RenderFillRect(renderer, &sperm.rect);
    }
}

// tạo hàm vẽ sperm

void SpaceInvaders::handleEvents()
{
    // SDL_PollEvent đọc dữ liệu sự kiện OS đưa cho SDL ghi vào event
    // và đọc kiểu dữ liệu trong struct SDL_Event thì phải truy cập vào biến thành viên .type
    // hàm này lấy ra một sự kiện một lần
    // nếu muốn đọc hết thì phải dùng vòng lặp
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT) // nếu mà click vào dấu x ; và dùng alt+f4 ,.. thì chạy body của control flow
        {
            // dừng vòng lặp (không gửi lệnh vẽ nữa)
            isRunning = false;
        }

        if (event.type == SDL_KEYDOWN)
        {
            if (event.key.keysym.scancode == SDL_SCANCODE_SPACE)
            {
                createSperm();
            }
        }
    }
}

void SpaceInvaders::updateSimulation()
{
    const Uint8 *state = SDL_GetKeyboardState(nullptr);

    if (state[SDL_SCANCODE_A])
    {
        dick.rect.x = dick.rect.x - dick.speed;
    }
    if (state[SDL_SCANCODE_D])
    {
        dick.rect.x = dick.rect.x + dick.speed;
    }

    if (dick.rect.x <= leftWall)
    {
        dick.rect.x = leftWall;
    }
    if (dick.rect.x >= rightWall - dick.rect.w)
    {
        dick.rect.x = rightWall - dick.rect.w;
    }

    // "trung trình" đi lùi lên trên
    for (auto &sperm : sperms)
    {
        sperm.rect.y = sperm.rect.y - sperm.speed;
    }
    killSperm(); // cái này bị gọi ngay lập tức khi mà con không có bất khi điều kiều gì
}

// sau khi đã nạp code của sdl bắt đầu tạo lệnh vẽ theo chỉ số sau đây
void SpaceInvaders::renderFrame()
{

    // thiết lập màu vẽ window (backend vẽ)
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

    // tô màu
    SDL_RenderClear(renderer);

    SDL_RenderCopy(renderer, dickTexture, nullptr, &dick.rect);
    renderSperm();
    // hiển thị của sổ
    SDL_RenderPresent(renderer);
}

// sau khi đã vẽ rồi giờ tạo vòng lặp để gọi lệnh vẽ liên tục
void SpaceInvaders::run()
{
    // khi cờ isRunning = true , hãy chạy body của vòng lặp
    while (isRunning)
    {
        // xử lý sự kiện yêu cầu dùng màn hình
        handleEvents();
        // BUG:quên nhét "cập nhật mô phỏng"
        updateSimulation();
        // vẽ cửa sổ lên
        renderFrame();
    }
}

// xóa tài nguyên của SDL khi không còn xử dụng nữa
void SpaceInvaders::cleanUp()
{
    if (renderer) // nếu đã liên kết với backend
    {
        SDL_DestroyRenderer(renderer); // hủy liên kết với backend
    }
    if (window) // nếu đã vẽ cửa sổ
    {
        SDL_DestroyWindow(window); // hủy cửa số
    }
    SDL_Quit(); // turn off toàn bộ code đã kết nối với SDL
}

// gọi destructor để giải phóng tài nguyên của C++ trong RAM trả cho OS dùng
SpaceInvaders::~SpaceInvaders()
{
    cleanUp(); // gọi lệnh giải phóng tài nguyên của SDL
}