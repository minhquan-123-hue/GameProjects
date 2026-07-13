# Rendering

## Overview

The breakout2 project uses **SDL2** for window management and 2D rendering. The rendering pipeline is straightforward: clear, draw, present.

## Initialization

### Window & Renderer Setup

Located in [lib/systems/sdl_manager.h](../lib/systems/sdl_manager.h) and [src/systems/sdl_manager.cpp](../src/systems/sdl_manager.cpp):

```cpp
bool SDLManager::create_Window();    // Creates an 800x600 window titled "Breakout 2"
bool SDLManager::create_Renderer();  // Creates a renderer attached to the window
```

**Window dimensions:** 800 × 600 pixels

**Initialization sequence** (in [src/game.cpp](../src/game.cpp)):

1. `SDLManager::init()` – Initialize SDL2 video subsystem
2. `create_Window()` – Create 800×600 window
3. `create_Renderer()` – Create SDL renderer
4. Load managers (FontManager, GraphicManager, SoundManager)
5. Load assets (fonts, background images, sounds)

## Render Loop

The main render cycle is defined in `Game::render_frame()` ([src/game.cpp](../src/game.cpp#L209)):

```cpp
void Game::render_frame() {
    sdl_manager.setup_Window();     // Clear and prepare
    
    State *cur = state_machine.getCurrent();
    if (cur)
        cur->render(sdl_manager.renderer);  // Delegate to active state
    
    sdl_manager.draw_Everything();  // Present framebuffer
}
```

### Setup & Present

- **setup_Window()** – Clears the renderer (typically fills with black/dark color)
- **draw_Everything()** – Calls `SDL_RenderPresent()` to display the framebuffer

## Draw Order

The active state controls draw order. Currently, the **Menu** state ([src/states/menu.cpp](../src/states/menu.cpp#L79)) draws in this order:

1. **Background image** – Loaded via `GraphicManager::loadBackground()`, rendered full-window
2. **Title text** ("Breakass") – Centered, yellow, 2× scaled
3. **Menu items** (Play / High Score) – Centered vertically below title, color varies:
   - Yellow if selected
   - White if not selected

## Textures & Text Rendering

### Text Rendering (FontManager)

Located in [lib/systems/font_manager.h](../lib/systems/font_manager.h):

```cpp
class FontManager {
    bool loadFont(const std::string &path, int size);
    SDL_Texture *createTextTexture(SDL_Renderer *renderer, 
                                   const std::string &text, 
                                   SDL_Color color);
    void clean();
};
```

**Flow:**
1. `FontManager::init()` – Initialize SDL_ttf (font library)
2. `loadFont()` – Load a `.ttf` file at a specified size (e.g., 48pt)
3. `createTextTexture()` – Render text string with a color to an SDL_Texture
4. States cache these textures and reuse them each frame (e.g., Menu pre-creates light/selected variants)

### Image Rendering (GraphicManager)

Located in [lib/systems/graphic_manager.h](../lib/systems/graphic_manager.h):

```cpp
class GraphicManager {
    bool loadBackground(SDL_Renderer *renderer, const std::string &path);
    SDL_Texture *getBackground() const;
    void clean();
};
```

**Flow:**
1. `GraphicManager::init()` – Initialize SDL_image (image library)
2. `loadBackground()` – Load a PNG/JPEG from disk as an SDL_Texture
3. `getBackground()` – Retrieve the loaded background texture (read-only)

Currently loads a single background at [assets/graphics/background.png](../assets/graphics/background.png).

## Drawing Textures

Textures are drawn using SDL's standard API:

```cpp
SDL_Rect rect;
SDL_QueryTexture(texture, nullptr, nullptr, &rect.w, &rect.h);  // Get dimensions
rect.x = x_position;
rect.y = y_position;
SDL_RenderCopy(renderer, texture, nullptr, &rect);  // Draw to renderer
```

**Note:** The Menu state manually positions and scales text for centering and emphasis.

## Cleanup

When the game shuts down (in `Game::clean()`, [src/game.cpp](../src/game.cpp)):

1. `GraphicManager::clean()` – Destroy background texture
2. `FontManager::clean()` – Destroy font and associated textures
3. `SDLManager::destroy()` – Destroy renderer and window, quit SDL

## Asset Locations

- **Fonts:** [assets/fonts/font.ttf](../assets/fonts/)
- **Graphics:** [assets/graphics/background.png](../assets/graphics/)
