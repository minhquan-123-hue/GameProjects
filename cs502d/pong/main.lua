WINDOW_WIDTH = 1280 -- constant thôi 
WINDOW_HEIGHT = 720

VIRTUAL_WIDTH = 432
VIRTUAL_HEIGHT = 243


push = require 'push'

function love.load() 
    love.graphics.setDefaultFilter("nearest", "nearest")
    love.window.setMode(
        WINDOW_WIDTH, WINDOW_HEIGHT,
        {
        resizable = false;
        vsync = true;
        fullscreen = false;
    })

    push.setupScreen(VIRTUAL_WIDTH, VIRTUAL_HEIGHT, {upscale = 'normal'})
end


function love.keypressed(key)
    if key == "espaced" then
        love.event.quit()
    end
end


function love.draw()
    push.begin() 
    love.graphics.printf(
        "Hello, Pong!", 
        0,
        VIRTUAL_HEIGHT/2 -6,
        VIRTUAL_WIDTH,
        "center")
    push.finish()
end