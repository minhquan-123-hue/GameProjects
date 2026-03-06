// sau khi đã khởi tạo header (chữ ký hàm , bản thiết kế ta sẽ làm gì) thì ta sẽ tạo các hàm hoạt động được thật sự ở đây
// vẫn là sử dụng công cụ nào thì nhập khẩu = #include (để preprocessor copy + paste code vào đây) , rồi lát nữa khi compile để mà compiler biết là xem ghi đúng chữ ký mà chưa

#include <Game.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

// tạo constructor(hàm khởi tạo) , initialize tất cả biến thành viên và giá trị ban đầu của nó , để tránh có rác trong biến đó , hoặc con trỏ đó , gây ra undefined behaviors
BreakOut::BreakOut() : // chưa trỏ tới đâu cả
                       window(nullptr),
                       renderer(nullptr),
                       // hệ thống video , cửa sổ, cây bút vẽ chưa được tạo => vòng lặp chưa thể hoạt động
                       is_running(false),

                       // vị trí + kích thước của vợt + velocity
                       platformWidth(100.0f),
                       platformHeight(20.0f),
                       platformX(10.0f),
                       platformY(970.0f),
                       platformSpeed(1500.0f),

                       // wall min max
                       windowLeft(0.0f),
                       windowRight(1000.0f),
                       windowUp(0.0f),
                       windowDown(1000.0f),

                       // point + health
                       points(0),
                       hitwall(0),

                       // dừng chương trình khi thắng hoặc thua
                       is_ballFrozen(false),
                       is_platformFrozen(false),
                       is_multiplied(false),

                       // màn hình hiện tại lúc đầu
                       currentScreen(Screen::MENU),
                       // chưa trỏ để nơi chứa file nào cả
                       font(nullptr),
                       textureMenu(nullptr),
                       textureGameover(nullptr),
                       textureWin(nullptr),
                       textureScore(nullptr),
                       textureHealth(nullptr),

                       // cac con tro trỏ tới dữ liệu âm thanh
                       sfxbounce(nullptr),
                       sfxhitBrick(nullptr),
                       sfxloseHealth(nullptr),
                       sfxwin(nullptr),
                       bgm(nullptr)

{
}

// tiếp theo là khởi động SDL để "ghi danh" nói chuyện với OS
bool BreakOut::init()
{
    std::cout << "bắt đầu khởi tạo tài nguyên" << std::endl;
    int initResult = SDL_Init(SDL_INIT_VIDEO || SDL_INIT_AUDIO);
    // kiểm tra xem có tài nguyên phần cứng phục vụ cho VIDEO có hoạt động không
    if (initResult != 0)
    {
        std::cerr << "không khởi tạo được hệ thống VIDEO: " << SDL_GetError() << std::endl;
        return false;
    }

    // sau khi đã ghi danh với OS là cần dùng hệ thống âm thanh và OS báo lại là dùng được phần cứng của hệ thống , ta cần thỏa hiệp là ta sẽ xử lý âm thanh thế nào (thương lượng) với OS
    int openAudioResult = Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    if (openAudioResult != 0)
    {
        std::cerr << "không mở được âm thanh thành công" << Mix_GetError() << std::endl;
        return false;
    }

    bool loadSoundFileResult = loadSound();

    if (loadSoundFileResult != true)
    {
        std::cerr << "không tải được các file âm thanh" << std::endl;
        return false;
    }

    // tạo một cửa số thật (os quản lý) , trả về một handle (sdl đưa cho bạn) để lát xử lý nó
    window = SDL_CreateWindow(
        "breakout",
        0,
        0,
        1000,
        1000,
        SDL_WINDOW_SHOWN // cai bien nay de lam gi ?
    );
    // kiem tra xem thong so cua so co duoc tao thành công hay không
    if (!window)
    {
        std::cerr << "thông số cửa sổ không được khởi tạo thành công!" << SDL_GetError() << std::endl;
        return false;
    }

    //
    renderer = SDL_CreateRenderer(
        window,
        -1,                                                  // chọn cái backend nào đang hỗ trợ => có thể là Open_GL
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC // cái cờ này có phải nghĩa là chọn GPU Không ?
    );
    // kiểm tra xem là backend này đã được kết nối với SDL chưa ?
    if (!renderer)
    {
        std::cerr << "không khởi tạo được hệ thống backend: " << SDL_GetError() << std::endl;
        return false;
    }

    // khởi tạo hệ thống xử lý hệ thống font
    int initFontSystem = TTF_Init();

    // kiểm tra nếu mà hệ thống xử lý font khởi tạo không thành công trả lại false để thóat sớm
    if (initFontSystem == -1)
    {
        std::cerr << "không khởi tạo hệ thống xử lý font thành công." << TTF_GetError() << std::endl;
        return false;
    }

    // mở font vừa tải về
    font = TTF_OpenFont("../assets/font.ttf", 48);

    // kiểm tra xem có kết nối được với đường dẫn tới font thành công không
    if (font == nullptr)
    {
        std::cerr << "đường dẫn không kết nối thành công." << std::endl;
        return false;
    }

    // sau khi tạo xong tài nguyên của 3 khối chữ thì gọi tạo khởi tạo để không địt nhau với tài nguyên (gọi - phân bổ - dùng xong - xóa) khiến cho Ram không còn chỗ , game tụt trĩ
    createFontResource();

    // sau khi toàn bộ hệ thống của SDL , cửa sổ, backend hoạt động được rồi , ta sẽ trả về true và thiết lập trạng thái cờ running = true để mà cho vòng lặp chạy được (gửi lệnh vẽ cho GPU)
    is_running = true;
    return true;
}

// đọc và copy nội dung của các file âm thanh vào RAM

bool BreakOut::loadSound()
{
    sfxbounce = Mix_LoadWAV("../assets/bounce.wav");
    sfxhitBrick = Mix_LoadWAV("../assets/brick.wav");
    sfxloseHealth = Mix_LoadWAV("../assets/lose.wav");
    sfxwin = Mix_LoadWAV("../assets/win.wav");

    bgm = Mix_LoadMUS("../assets/bgm.mp3");

    if (!sfxbounce || !sfxhitBrick || !sfxloseHealth || !sfxwin || !bgm)
    {

        return false;
    }
    return true;
}

// hàm tạo ảnh trong vram
SDL_Texture *BreakOut::createTextTexture(const std::string &text, SDL_Rect &rect)
{

    // tạo màu của khối bằng struct chứa 4 thành phần : R G B A
    SDL_Color color = {255, 255, 255, 255};

    // tạo bitmap trong RAM
    SDL_Surface *surface = TTF_RenderText_Solid(font, text.c_str(), color);

    // kiểm tra xem con trỏ surface có phải nullptr
    if (surface == nullptr)
    {
        std::cerr << "không tạo được bitmap trong surface" << std::endl;
    }

    // copy ảnh trong ram sang vram
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

    // khối text kích thước và vị trí
    rect.w = surface->w;
    rect.h = surface->h;
    rect.x = 10;
    rect.y = 10;

    // đã copy xong trả tài nguyên cho chương trình (ảnh ram -> vram)
    SDL_FreeSurface(surface);

    // trả lại texture
    return texture;
}

// tạo 3 khối chữ cho 3 trạng thái
void BreakOut::createFontResource()
{
    textureMenu = createTextTexture("MENU wanna suck cock choose return", textMenu);

    textureGameover = createTextTexture("DEFEATED lick pussy to comeback R", textGameover);

    textureWin = createTextTexture("WIN your mom fuck your dad R", textWin);
}

// biến health và point từ khối thành chữ
void BreakOut::updateUIText()
{

    std::string scoreText = "Score: " + std::to_string(points);
    std::string healthText = "Health: " + std::to_string(10 - hitwall); // 10 == maxHealth

    if (textureScore)
    {
        SDL_DestroyTexture(textureScore);
    }

    if (textureHealth)
    {
        SDL_DestroyTexture(textureHealth);
    }

    textureScore = createTextTexture(scoreText, rectScore);
    textureHealth = createTextTexture(healthText, rectHealth);

    rectScore.x = 20;
    rectScore.y = 20;

    rectHealth.x = 600;
    rectHealth.y = 20;
}

void BreakOut::initBall()
{
    this->balls.clear();

    Ball ball{500.0f, 500.0f, 600.0f, 600.0f, 15.0f, true}; // viết thiếu chỉ số

    balls.push_back(ball);
}
// this function draw circle
void BreakOut::DrawFilledCircle(SDL_Renderer *renderer, int ballCenterX, int ballCenterY, int radius)
{
    // top "point" of the circle , always smaller than center and draw from top to center == y++
    for (int y = -radius; y <= radius; y++)
    {
        for (int x = -radius; x <= radius; x++)
        {
            // still not get it , tomorrow spend more time in the day learn game with SDL, and later in the afternoon study cs50x because that's just theory sometime math (3 days left)
            if (x * x + y * y <= radius * radius)
            {
                SDL_RenderDrawPoint(renderer, ballCenterX + x, ballCenterY + y); // tức là cái này vẽ tất cả các điểm từ tâm của hình tròn
            }
        }
    }
}

// vẽ quả bóng
void BreakOut::renderBall()
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);

    // hiện tại là chỉ có 1 quả bóng , mà giờ ta muốn tạo ra 2 quả thì phải vào trong "mảng động" để trích xuất chỉ số ra
    for (auto &ball : balls)
    {
        if (ball.alive == false)
        {
            continue;
        }
        DrawFilledCircle(renderer, ball.x, ball.y, ball.radius); // hàm này do mình tạo ra
    }
}

// tạo bệ đỡ
void BreakOut::renderPlatform()
{
    // tạo một struct của SDL chứa các tham số: vị trí + kích thước của bệ đỡ
    SDL_Rect platform;
    platform.x = static_cast<int>(platformX);
    platform.y = static_cast<int>(platformY);
    platform.w = static_cast<int>(platformWidth);
    platform.h = static_cast<int>(platformHeight);

    // tạo trạng thái màu
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    // tô màu cho "bệ đỡ"
    SDL_RenderFillRect(renderer, &platform);
}

// vẽ khung chứa: điểm , mạng
void BreakOut::renderFrame()
{

    // vẽ khung ngang
    SDL_Rect frame_horizontal;
    frame_horizontal.x = 0;
    frame_horizontal.y = 100;
    frame_horizontal.w = 1000;
    frame_horizontal.h = 4;

    // vẽ khung dọc
    SDL_Rect frame_vertical;
    frame_vertical.x = (1000 / 2) - 2;
    frame_vertical.y = 0;
    frame_vertical.w = 4;
    frame_vertical.h = 100;

    // thiết lập màu
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    // tô màu khung
    SDL_RenderFillRect(renderer, &frame_horizontal);
    SDL_RenderFillRect(renderer, &frame_vertical);

    SDL_RenderCopy(renderer, textureScore, nullptr, &rectScore);
    SDL_RenderCopy(renderer, textureHealth, nullptr, &rectHealth);
}

// tạo gạch
void BreakOut::initBricks()
{

    // tạo kích thước + vị trí cho gạch thay vì hardcode
    Size size{80.0f, 20.0f, 400.0f};
    // vì bricks là object scope nên gọi ở hàm thành viên không cần dùng this cũng được
    // xóa hết gạch bắt đầu lại gạch mới
    this->bricks.clear();

    for (int i = 0; i < 12; i++)
    {

        // tạo từng viên gạch
        Brick brick;
        brick.rect.x = 10 + i * (size.Width + 10);
        brick.rect.y = static_cast<int>(size.Y);
        brick.rect.w = static_cast<int>(size.Width);
        brick.rect.h = static_cast<int>(size.Height);
        brick.alive = true;
        bricks.emplace_back(brick);
    }
}

// vẽ viên gạch và chưa xử logic
void BreakOut::renderBrick()
{
    // thiết lập màu
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    // dùng vòng lặp để đi qua từng viên gạch lấy giá trị của nó để vẽ
    for (auto &brick : this->bricks) // đi vào trong "mảng động" đã được tạo và tồn tại gạch không phải copy
    {
        if (!brick.alive)
        {
            continue; // bỏ qua không vẽ
        }
        SDL_RenderFillRect(renderer, &brick.rect);
    }
}

// xử lý logic va chạm để bóng biến mất
// brickrect chính là brick.rect ()
bool BreakOut::checkCollison(const SDL_Rect &ball, const SDL_Rect &brickrect)
{
    // kích thước của gạch đã được tạo trong initBricks() , còn kích thước của bóng đã có trong constructor
    bool overlapX = ball.x < brickrect.x + brickrect.w && ball.x + ball.w > brickrect.x;

    // thử bỏ 1 điều kiện ở trục Y trên của gạch xem nó không va chạm với cạnh đấy thì sao
    bool overlapY = ball.y < brickrect.y + brickrect.h && ball.y + ball.h > brickrect.y;

    return overlapY && overlapX;
}
// tiếp theo là sẽ vẽ "cửa sổ" sau khi SDL đã kết nối được với backend của OS để nói chuyện với rendering driver
void BreakOut::render()
{
    // vẽ màn hình : thiết lập trạng thái màu sắc, tô màu, hiển thị
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // tạo điều kiện để điều khiển hình vẽ trong từng trang thái màn hình
    if (currentScreen == Screen::MENU)
    {
        SDL_RenderCopy(renderer, textureMenu, nullptr, &textMenu);
    }
    if (currentScreen == Screen::PLAYING)
    {
        // vẽ "bệ đỡ"
        renderPlatform();
        // vẽ bóng
        renderBall();
        // vẽ "gạch"
        renderBrick();
        // vẽ khung chứa : điểm + mạng
        renderFrame();
    }
    if (currentScreen == Screen::WIN)
    {
        SDL_RenderCopy(renderer, textureWin, nullptr, &textWin);
    }

    if (currentScreen == Screen::GAMEOVER)
    {
        SDL_RenderCopy(renderer, textureGameover, nullptr, &textGameover);
    }

    SDL_RenderPresent(renderer);
}

// tạo hàm xử lý các xử kiện từ phím và chuột
void BreakOut::handleEvents()
{
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            is_running = false;
        }
        // xử lý sự kiện: phím gõ 1 lần để chuyển trạng thái game
        if (event.type == SDL_KEYDOWN)
        {
            std::cout << "phím đang được ấn: " << event.key.keysym.scancode << std::endl;
            if (event.key.keysym.scancode == SDL_SCANCODE_RETURN && currentScreen == Screen::MENU)
            {
                Mix_PlayMusic(bgm, -1);
                currentScreen = Screen::PLAYING;
                resetState();
            }

            if (event.key.keysym.scancode == SDL_SCANCODE_R && (currentScreen == Screen::GAMEOVER || currentScreen == Screen::WIN))
            {
                currentScreen = Screen::MENU;

                // sau mà bóng đã có được nhảy về thái : GAMEOVER hoặc WIN
                // thiết lập lại trạng thái của điểm số và cờ
                resetState();
            }
        }
    }
}

// sau khi xử lý nhận phím và xác nhận cờ di chuyển ta sẽ cập nhật vị trí
void BreakOut::update(float delta)
{
    // nếu mà điều kiện dừng chương bóng và bệ đúng bỏ qua update để ball và bệ không thể di chuyển
    if (is_platformFrozen == true && is_ballFrozen == true)
    {
        std::cout << "dừng cập nhật update" << std::endl;
        return;
    }

    if (currentScreen == Screen::PLAYING)
    {
        // kiểm tra trạng thái của key trong "mảng" xem nó là 0 hay 1 rồi từ đó thay đổi logic di chuyển
        // cái trạng thái phím này là phím "giữ"
        // tham số nullptr nghĩa là không cần nó trả lại tổng số lượng key nó xử lý, và inó sẽ trả lại một "mảng" nằm trong bộ nhớ (vị của từng enum)
        const Uint8 *keyState = SDL_GetKeyboardState(nullptr);

        // dùng toán con trỏ để đi vào trong mảng , vì con trỏ luôn trỏ vào vị trí đầu tiên của mảng mà enum tạo ra , nên là khi dùng 1 biến trong enum thì hoàn toàn có thể dùng pointer là vị trí đầu tiên cộng với luật con trỏ để đến được vị của cái biến đó nằm
        if (keyState[SDL_SCANCODE_A])
        {
            platformX -= platformSpeed * delta;
        }
        if (keyState[SDL_SCANCODE_D])
        {
            platformX += platformSpeed * delta;
        }
        if (keyState[SDL_SCANCODE_LEFT])
        {
            platformX -= platformSpeed * delta;
        }
        if (keyState[SDL_SCANCODE_RIGHT])
        {
            platformX += platformSpeed * delta;
        }

        // DỪNG "bệ" KHI VA CHẠM VỚI TƯỜNG (Left or Right)
        if (platformX <= windowLeft)
        {
            platformX = windowLeft;
        }
        if (platformX >= windowRight - platformWidth)
        {
            platformX = windowRight - platformWidth; // 1000 - 100 = 900 dừng ở đây
        }

        // lúc trước là ta không có sử dụng vector để tạo bóng với struct , mà là trực tiếp viết sau đó khởi tạo trong constructor nhưng giờ đã nằm trong struct rồi thì giờ ta phải đi vào trong vector đó để đọc các chỉ số để mà có thể cập nhật (x, y , velX, velY) để tính toán va chạm
        for (auto &ball : this->balls)
        {
            // làm bóng di chuyển
            ball.x += ball.velX * delta;
            ball.y += ball.velY * delta;

            // va chạm với tường
            if (ball.x - ball.radius <= windowLeft && ball.alive)
            {
                Mix_PlayChannel(-1, sfxbounce, 0);
                ball.x = windowLeft + ball.radius;
                ball.velX = -ball.velX;
            }
            if (ball.x >= windowRight - ball.radius && ball.alive)
            {
                Mix_PlayChannel(-1, sfxbounce, 0);
                ball.x = windowRight - ball.radius;
                ball.velX = -ball.velX;
            }
            // cần chỉnh sửa đoạn này vì nó va chạm với cả khung chứa điểm
            // độ cao của khung là 104  ghi tạm nhưng này vậy (vì thanh ngang cao 4 , thanh dọc 100)
            frameHeight = 100;
            if (ball.y - ball.radius <= windowUp + frameHeight + 4 && ball.alive)
            {
                Mix_PlayChannel(-1, sfxbounce, 0);
                ball.y = windowUp + frameHeight + 4 + ball.radius;
                ball.velY = -ball.velY;
            }
            // va chạm với đáy
            if (ball.y >= windowDown - ball.radius && ball.alive) // vì điều kiện va chạm này không quan tâm bóng còn sống không vẫn tính va chạm với đáy lên là vẫn trừ điểm bình thường
            {
                Mix_PlayChannel(-1, sfxloseHealth, 0);
                std::cout << "-1 mạng" << std::endl;
                hitwall += 1;
                updateUIText();
                // bong ve giua man hinh

                ball.y = windowDown - ball.radius;
                ball.velY = -ball.velY;
            }

            // bóng va chạm với bệ đỡ , có độ lệch để thay đổi X nhiều hay ít , Y giật ngược lại
            bool overlapX = ball.x <= platformX + platformWidth && ball.x + ball.radius >= platformX;
            bool overlapY = ball.y + ball.radius >= platformY;

            if (overlapX && overlapY && ball.velY > 0)
            {
                Mix_PlayChannel(-1, sfxbounce, 0);
                ball.y = (platformY)-ball.radius;
                ball.velY = -ball.velY;

                float middleBall = ball.x;
                float middlePlatform = platformX + (platformWidth / 2);
                // chuẩn hóa độ lệch : độ lệch thật sự giữa tâm vợt tâm bóng/ độ lệch tối đa khoảng cách tâm vợt và tâm bóng
                float normalize_offset = (middleBall - middlePlatform) / ((platformWidth / 2) + (ball.radius));
                // toc do co dinh
                const float fix_speed = 600.0f;
                ball.velX = fix_speed * normalize_offset;
            }

            // va chạm với gạch , đổi tâm 0,0 middle sang top-left 0,0
            SDL_Rect ballRect;
            ballRect.x = static_cast<int>(ball.x - ball.radius);
            ballRect.y = static_cast<int>(ball.y - ball.radius);
            ballRect.w = static_cast<int>(ball.radius * 2);
            ballRect.h = static_cast<int>(ball.radius * 2);

            for (auto &brick : bricks)
            {
                if (!brick.alive || !ball.alive) // nếu mà bóng chết rồi thì không so sánh với gạch nữa
                    continue;

                if (checkCollison(ballRect, brick.rect))
                {
                    Mix_PlayChannel(-1, sfxhitBrick, 0);
                    brick.alive = false;    // da va cham voi gach => chet
                    ball.velY = -ball.velY; // dao chieu bong
                    points += 1;            // cong diem
                    updateUIText();
                }
            }

            if (points > 5 && ball.y >= windowDown - ball.radius && ball.alive && balls.size() == 2)
            {
                updateUIText();
                ball.alive = false;

                auto newEnd = std::remove_if(
                    balls.begin(),
                    balls.end(),
                    [](const auto &ball)
                    {
                        return !ball.alive; // trả lại trạng thái true / hoặc false , nếu mà trạng thái là true tức bóng chết thì cho xuống dưới đáy , nếu mà còn sống tức là !true == false xếp lên trên
                    });                     // hỏi lại chatGPT giải thích

                balls.erase(newEnd, balls.end()); // hỏi lại chatGPT giải thích
            }
        }

        // nếu mà 10 điểm thì chiến thắng dừng game
        if (points == 10)
        {
            Mix_PlayChannel(-1, sfxwin, 0);
            std::cout << "bạn đã thắng" << std::endl;
            is_platformFrozen = true;
            is_ballFrozen = true;

            // sau khi đã chiến thắng nhảy về màn chiến thắng
            currentScreen = Screen::WIN;
            Mix_HaltMusic();
        }

        // nếu mà 0 mạng thì thua dừng game
        if (hitwall == 10)
        {

            std::cout << "bạn đã thua" << std::endl;
            is_platformFrozen = true;
            is_ballFrozen = true;
            currentScreen = Screen::GAMEOVER;
            Mix_HaltMusic();
        }

        if (points >= 5 && is_multiplied == false)
        {

            Ball newball = balls[0];
            balls.push_back(newball);
            newball.velY = -newball.velY;
            is_multiplied = true;
        }
    }
}

// thiết lập lại toàn bộ điểm số và cờ
void BreakOut::resetState()
{
    Ball ball;
    points = 0;
    hitwall = 0;
    is_platformFrozen = false;
    is_ballFrozen = false;
    is_multiplied = false; // đưa về trạng thái chưa x2 bóng
    ball.x = 500;
    ball.y = 500;
    platformX = 500;

    // Tạo tài nguyên gạch lúc đầu và tạo lại khi chơi state mới
    initBricks();

    // tạo bóng mỗi ván mới (thua , thắng , vừa vào game)
    initBall();

    updateUIText();
}
// giờ chạy vòng lặp để gửi lệnh vẽ liên tiếp
void BreakOut::run()
{
    // tạo ra thời gian chên lệch giữa 2 frame (tức thời gian di chuyển)
    Uint32 previousTime = SDL_GetTicks();
    while (is_running == true)
    {
        Uint32 now = SDL_GetTicks();

        float delta = (now - previousTime) / 1000.0f;
        // gắn thời gian hiện tại thành thời gian vừa nãy để tiếp tục đo độ lệch 2 frame mới
        previousTime = now;
        handleEvents();
        update(delta);
        render();
    }
    cleanUp();
}

// dọn dẹp tài nguyên hỏi SDL tạo
void BreakOut::cleanUp()
{
    if (sfxbounce)
    {
        Mix_FreeChunk(sfxbounce);
    }
    if (sfxhitBrick)
    {
        Mix_FreeChunk(sfxhitBrick);
    }
    if (sfxloseHealth)
    {
        Mix_FreeChunk(sfxloseHealth);
    }
    if (sfxwin)
    {
        Mix_FreeChunk(sfxwin);
    }
    if (bgm)
    {

        Mix_FreeMusic(bgm);
    }
    SDL_CloseAudio();

    if (textureMenu)
    {
        SDL_DestroyTexture(textureMenu);
    }
    if (textureGameover)
    {
        SDL_DestroyTexture(textureGameover);
    }
    if (textureWin)
    {
        SDL_DestroyTexture(textureWin);
    }

    if (font)
    {
        TTF_CloseFont(font);
    }
    if (renderer)
    {
        SDL_DestroyRenderer(renderer);
    }
    if (window)
    {
        SDL_DestroyWindow(window);
    }
    TTF_Quit();
    SDL_Quit();
    std::cout << "hoàn thành trả lại tài nguyên" << std::endl;
}

// dọng tài nguyên của C++
BreakOut::~BreakOut()
{
}