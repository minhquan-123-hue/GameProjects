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
SpaceInvaders::SpaceInvaders() : renderer(nullptr),    // chưa chỉ tới struct SDL_Renderer
                                 window(nullptr),      // chưa chỉ tới struct SDL_Window
                                 dickTexture(nullptr), // họa tiệt của tàu chưa có
                                 leftWall(0),          // tường trái
                                 rightWall(1000),      // tường phải
                                 topWall(0),           // tường trên
                                 bottomWall(1000),     // tường dưới

                                 isRunning(false) // cờ chưa đúng vì chưa biết SDL đã kết nối được với OS chưa

{
    dick.rect.x = 30;
    dick.rect.y = 900;
    dick.rect.w = 64;
    dick.rect.h = 64; // BUG: viết sai tên biến thành viên cho SDL_Rect height là viết thành y
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
    // cần 2 tham số: path + backend giao tiếp với GPU nếu có
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

        if (event.type == SDL_KEYDOWN) // nếu SPACE được ấn thì "xuất tinh"
        {
            if (event.key.keysym.scancode == SDL_SCANCODE_SPACE)
            {
                std::cout << "BANG\n";
                Sperm sperm;

                sperm.rect.x = dick.rect.x + dick.rect.w / 2 - 2; // vị trí X của "trung tình" áng áng ở giữa con câu
                sperm.rect.y = dick.rect.y - 10;                  // vị trí Y của "trung tình" xuất phát nằm sâu bên trong con câu khoàng 10 phân vì kích thước của nó là 20
                sperm.rect.w = 10;
                sperm.rect.h = 20;

                sperm.speed = 15;

                sperms.push_back(sperm); // hàm này là để nhét struct mới vào vị trí ở cuối "mảng động"
            }
        }
    }
}

void SpaceInvaders::updateSimulation()
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

    // xuất tinh lùi dần trên trục Y vào các con bướm
    for (auto &sperm : sperms) //
    {
        sperm.rect.y = sperm.rect.y - sperm.speed;
    }

    // tinh bay hay hơi khi chạm vào tường trên (bồn cầu)
    // hàm trả lại con trỏ thông minh , chỉ vào giữa phần dữ liệu
    // đã được tách ra , bên trái cho dữ liệu không khớp với ĐK
    // bên phải cho dữ liệu đã khớp điều kiện
    auto newEnd = std::remove_if(
        sperms.begin(),
        sperms.end(),
        [](Sperm &sperm)
        { return sperm.rect.y < 0; }); // return sẽ trả lại true/false
    // nếu mà sperm.rect.y > 0 thì sẽ return false
    // nểu mà sperm.rect.y < 0 thật thì return true

    sperms.erase(newEnd, sperms.end()); // từ vị trí của con trỏ thốn minh đến phần còn lại của code xóa hết tất
}
// sau khi đã nạp code của sdl bắt đầu tạo lệnh vẽ theo chỉ số sau đây
void SpaceInvaders::renderFrame()
{

    // thiết lập màu vẽ window (backend vẽ)
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

    // tô màu
    SDL_RenderClear(renderer);

    SDL_RenderCopy(renderer, dickTexture, nullptr, &dick.rect); // hàm này là gửi lệnh vẽ vào hàng chờ render
    // tham số : backend , texture(vram) , cắt hình (yes/no), kích thước + vị trí(ram SDL_Rect)
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);

    for (auto &sperm : this->sperms)
    {
        // nếu object trung tình còn data trong mảng động thì vẽ
        // nếu object đã bị xóa thì không còn dữ liệu => không vẽ
        SDL_RenderFillRect(renderer, &sperm.rect);
    }

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

        // cập nhật trạng thái mô phỏng
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