#include <game.h>    // thư viện chứa các hàm , biến, struct của game
#include <iostream>  // thư viên này cung cấp: hàm in chữ ra màn hình terminal (cửa sỗ gõ và hiển thị chữ)
#include <algorithm> // thư viện cung cấp hàm điểu khiển kích thước của mảng động: remove_if() sắp xếp mảng động , erase() xóa object trong mảng động

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
    dick.create();
    pussy.create();

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
    dick.updateMovement();
    dick.updateCollision(leftWall, rightWall);
    sperm.updateMovement();
    sperm.updateCollision(topWall);
}

// sau khi đã nạp code của sdl bắt đầu tạo lệnh vẽ theo chỉ số sau đây
void SpaceInvaders::renderFrame()
{

    // thiết lập màu vẽ window (backend vẽ)
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

    // tô màu cho toàn bộ nền lên cửa sổ
    SDL_RenderClear(renderer);

    dick.render(renderer);
    sperm.render(renderer);
    pussy.render(renderer);
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
    dick.clean();
    sperm.clean();
    pussy.clean();
    SDL_Quit(); // turn off toàn bộ code đã kết nối với SDL
    IMG_Quit();
}

// gọi destructor để giải phóng tài nguyên của C++ trong RAM trả cho OS dùng
SpaceInvaders::~SpaceInvaders()
{
    cleanUp(); // gọi lệnh giải phóng tài nguyên của SDL
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
    bool hasDickPic = dick.loadTexture(renderer);
    bool hasSpermPic = sperm.loadTexture(renderer);
    bool hasPussyPic = pussy.loadTexture(renderer);

    if (!hasDickPic || !hasSpermPic || !hasPussyPic)
    {
        std::cout << "ảnh không mở đươc" << std::endl;
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
            sperm.create(dick.dick.rect.x, dick.dick.rect.y); // dick ngoài là dick objet, dick trong là dick biến thành viên (struct)
        }
    }
}
