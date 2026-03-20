#include <game.h>           // thư viện chứa các hàm , biến, struct của game
#include <iostream>         // thư viên này cung cấp: hàm in chữ ra màn hình terminal (cửa sỗ gõ và hiển thị chữ)
#include <SDL2/SDL.h>       // thư viện cung cấp hàm nói chuyển với OS để hỏi cấp quyền điều khiển : vẽ , tọa âm thanh ,...
#include <SDL2/SDL_ttf.h>   // thư viện cung cấp hàm biến text thành hình ảnh
#include <SDL2/SDL_image.h> // thư viện cung cấp hàm để vẽ ảnh lên cửa sổ
#include <SDL2/SDL_mixer.h> // thư viện cung cấp hàm điều khiển âm thanh ra loa
#include <string>           // thư viện cung cấp object điều khiển văn bản : phóng to , thu nhỏ , nối chữ ....
#include <vector>           // thư viện cung cấp "mảng động" chứa nhiều object cùng kiểu ở trong
#include <algorithm>        // thư viện cung cấp hàm điểu khiển kích thước của mảng động: remove_if() sắp xếp mảng động , erase() xóa object trong mảng động

// tạo constructor để khởi tạo các giá trị đi liền với "đối tượng"
SpaceInvaders::SpaceInvaders() : renderer(nullptr), // chưa chỉ tới struct SDL_Renderer
                                 window(nullptr),   // chưa chỉ tới struct SDL_Window
                                 leftWall(0),       // tường trái
                                 rightWall(1000),   // tường phải
                                 topWall(0),        // tường trên
                                 bottomWall(1000),  // tường dưới

                                 isRunning(false) // cờ chưa đúng vì chưa biết SDL đã kết nối được với OS chưa

{
}

bool SpaceInvaders::init()
{
    bool hasVideoConnected = connectVideoHandler();
    bool hasImageConnected = connectImageHandler();
    bool hasWindow = createWindow();
    bool hasBackend = createRenderer();
    bool hasPictureLoaded = loadPicture();
    createDick();
    createPussy();

    if (!hasVideoConnected || !hasImageConnected || !hasWindow || !hasBackend || !hasPictureLoaded)
    {
        return false;
    }

    isRunning = true;
    return true;
}

// sau khi đã vẽ rồi giờ tạo vòng lặp để gọi lệnh vẽ liên tục
void SpaceInvaders::run()
{
    // khi cờ isRunning = true , hãy chạy body của vòng lặp
    while (isRunning)
    {
        // xử lý sự kiện yêu cầu dùng màn hình
        handleEvents();

        // cập nhật trạng thái mô phỏng
        updateSimulation();

        // vẽ cửa sổ lên
        renderFrame();
    }
}

void SpaceInvaders::handleEvents()
{
    // SDL_PollEvent đọc dữ liệu sự kiện OS đưa cho SDL ghi vào event
    // và đọc kiểu dữ liệu trong struct SDL_Event thì phải truy cập vào biến thành viên .type
    // hàm này lấy ra một sự kiện một lần
    // nếu muốn đọc hết thì phải dùng vòng lặp
    while (SDL_PollEvent(&event))
    {
        quitEvents();
        playEvents();
    }
}

void SpaceInvaders::updateSimulation()
{

    updateDickMovement();
    updateDickCollision();
    updateSpermMovement();
    updateSpermCollision();
}

// sau khi đã nạp code của sdl bắt đầu tạo lệnh vẽ theo chỉ số sau đây
void SpaceInvaders::renderFrame()
{

    // thiết lập màu vẽ window (backend vẽ)
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

    // tô màu cho toàn bộ nền lên cửa sổ
    SDL_RenderClear(renderer);

    renderDick();
    renderPussy();
    renderSperm();

    // hiển thị của sổ và toàn bộ hình vẽ bên trong nó lên
    SDL_RenderPresent(renderer);
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
    IMG_Quit();
}

// gọi destructor để giải phóng tài nguyên của C++ trong RAM trả cho OS dùng
SpaceInvaders::~SpaceInvaders()
{
    cleanUp(); // gọi lệnh giải phóng tài nguyên của SDL
}

// tạo mấy con bướm dâm tặc
void SpaceInvaders::createPussy()
{
    int totalRows = 5;
    int totalCols = 10;
    int startX = 100;
    int startY = 100;
    int spacingX = 70; // chiều rộng của vật + khoảng cách mong muốn
    int spacingY = 70; // chiều cao của vật + khoảng cách mong muốn

    for (int pussyRow = 0; pussyRow < totalRows; pussyRow++)
    // vòng lặp lồng vòng lặp , với 1 vòng lặp ngoài , thì chạy 10 vòng lặp ở trong
    // và dựa vào các biến pussyRow (đổi sau kết thúc 10 vòng ở trong), pussyCol (thay đổi liên tục) để giá trị cho từng pussy về vị trí
    // có sự khác biệt vị trí , gửi lệnh vẽ ==> hình trên màn hình
    {
        for (int pussyCol = 0; pussyCol < totalCols; pussyCol++)
        {
            pussy.rect.w = 64;
            pussy.rect.h = 64;

            pussy.rect.x = startX + pussyCol * spacingX;
            std::cout << "pussy.rect.x: " << pussy.rect.x << std::endl;
            pussy.rect.y = startY + pussyRow * spacingY;
            std::cout << "pussy.rect.y " << pussy.rect.y << std::endl;

            pussies.push_back(pussy);
        }
    }
}

void SpaceInvaders::renderPussy()
{
    for (auto &pussy : pussies)
    // dùng vòng lặp để đi vào bên trong từng object của mảng động , để đọc dữ liệu
    // texture của pussy
    // rect của pussy
    {
        SDL_RenderCopy(renderer, pussy.texture, nullptr, &pussy.rect);
        // đây chỉ đơn giản là gửi lệnh vẽ
        // texture là là dữ liệu ảnh nằm trong VRAM nhưng OS chỉ cho ta cái handle chỉ tới cái dữ liệu đó , và SDL đưa cho ta 1 cái con trỏ chỉ tới dữ liệu của SDL (nơi chưa con trỏ chỉ tới dữ liệu của OS)
    }
}
void SpaceInvaders::createDick()
{
    dick.rect.x = 100;
    dick.rect.y = 900;
    dick.rect.w = 64;
    dick.rect.h = 64;
    dick.speed = 20;
}

void SpaceInvaders::renderDick()
{
    SDL_RenderCopy(renderer, dick.texture, nullptr, &dick.rect);
}

void SpaceInvaders::createSperm()
{
    Sperm sperm;
    sperm.rect.w = 20;
    sperm.rect.h = 30;
    sperm.rect.x = dick.rect.x + dick.rect.w - 2 + 2;
    sperm.rect.y = dick.rect.y - sperm.rect.h;

    sperm.speed = 3; // BUG: quên viết speed mà mà bóng không

    sperms.emplace_back(sperm);
}

void SpaceInvaders::killSperm()
{
    auto newEnd = std::remove_if(
        sperms.begin(),
        sperms.end(),
        [](Sperm &sperm)
        { return sperm.rect.y < 0; }

    );

    sperms.erase(newEnd, sperms.end());
}

void SpaceInvaders::renderSperm()
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    for (auto &sperm : this->sperms)
    {
        SDL_RenderFillRect(renderer, &sperm.rect);
    }
}

bool SpaceInvaders::connectVideoHandler()
{
    // nó đơn giản là bắt đầu nói chuyện với hệ điều hành
    int initResult = SDL_Init(SDL_INIT_VIDEO);

    if (initResult != 0)
    {
        std::cout << "không khởi tạo hệ thống video thành công: " << SDL_GetError() << std::endl;
        return false; // báo lại sao để không khởi chạy phương thức object.run()
    }
    return true;
}

bool SpaceInvaders::connectImageHandler()
{

    // hỏi OS để giải quyết vấn đề liên quan đến ảnh (image)
    int intImage = IMG_Init(IMG_INIT_PNG);

    if (!intImage)
    {
        std::cout << "không kết nối được chương trình xử lý .PNG" << std::endl;
        return false;
    }
    return true;
}

bool SpaceInvaders::createWindow()
{

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
    return true;
}

bool SpaceInvaders::createRenderer()
{

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
    return true;
}

bool SpaceInvaders::loadPicture()
{

    // tải hình ảnh tàu chiến lên
    // cần 2 tham số: path + backend giao tiếp với GPU nếu có
    dick.texture = IMG_LoadTexture(renderer, "../assets/dick.png");

    if (!dick.texture)
    {
        std::cout << "không mở được file ảnh" << std::endl;
        return false;
    }
    // khi mà có đủ : màn hình , backend , SDL kết nối với OS thành công
    // thì cho phép cờ của vòng lặp thành đúng
    // tạo "con câu"

    // mở ảnh quái vật đầu lồn + toilet lên
    pussy.texture = IMG_LoadTexture(renderer, "../assets/pussy.png");

    if (!pussy.texture)
    {
        std::cout << "không load được enemy" << SDL_GetError() << std::endl;
        return false;
    }
    return true;
}

void SpaceInvaders::quitEvents()
{
    if (event.type == SDL_QUIT) // nếu mà click vào dấu x ; và dùng alt+f4 ,.. thì chạy body của control flow
    {
        // dừng vòng lặp (không gửi lệnh vẽ nữa)
        isRunning = false;
    }
}

void SpaceInvaders::playEvents()
{

    if (event.type == SDL_KEYDOWN) // nếu SPACE được ấn thì "xuất tinh"
    {
        if (event.key.keysym.scancode == SDL_SCANCODE_SPACE)
        {
            createSperm();
        }
    }
}

void SpaceInvaders::updateDickMovement()
{
    // giờ sẽ đọc input từ phím để cho tàu "dick" di chuyển
    const Uint8 *state = SDL_GetKeyboardState(nullptr);

    if (state[SDL_SCANCODE_LEFT])
    {
        dick.rect.x = dick.rect.x - dick.speed;
    }
    if (state[SDL_SCANCODE_RIGHT])
    {
        dick.rect.x = dick.rect.x + dick.speed;
    }
}

void SpaceInvaders::updateDickCollision()
{
    // nếu mà con cu va chạm với tường thì dừng nó lại
    if (dick.rect.x <= leftWall)
    {
        // cạnh trái cu bằng tường trái
        dick.rect.x = leftWall;
    }
    if (dick.rect.x >= rightWall - dick.rect.w)
    {
        // cạnh trái con cu bằng tường phải trừ đi chiều ngang của con cu
        dick.rect.x = rightWall - dick.rect.w;
    }
}

void SpaceInvaders::updateSpermMovement()
{
    // xuất tinh lùi dần trên trục Y vào các con bướm
    for (auto &sperm : sperms) //
    {
        sperm.rect.y = sperm.rect.y - sperm.speed;
    }
}

void SpaceInvaders::updateSpermCollision()
{
    killSperm();
}