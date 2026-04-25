WINDOW_WIDTH = 1280 -- constant thôi 
WINDOW_HEIGHT = 720

--API love sẽ tự động nói chuyện với hệ điều hành , và yêu cầu kết nối với cách chương trình để xử lý phần âm thanh , đồ họa , font, ...

function love.load() -- hàm này là hàm con của love , và nó sẽ tự động được gọi khi dùng lệnh love . trong terminal 
    -- thiết lập trạng thái cho của sổ 
    love.window.setMode(
        WINDOW_WIDTH, WINDOW_HEIGHT,
        {
            
        resizable = false;
        vsync = true;
        fullscreen = false;
    })
end  

function love.draw() -- hàm con 
    -- graphics là một object trong object love , và nó chứa hàm con là graphics 
    -- không cần hết tham số của API chỉ cần biết nó làm gì , và dùng thế nào là được
    love.graphics.printf(
        "Hello, Pong!", 
        0,
        WINDOW_HEIGHT/2 -6, 
        WINDOW_WIDTH,
        "center")
end