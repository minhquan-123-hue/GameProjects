# Input

## Overview

Input is captured via SDL2 events and routed through the active state. Currently, the game supports **keyboard input only**.

## Input Pipeline

### Event Polling

In [src/systems/sdl_manager.cpp](../src/systems/sdl_manager.cpp):

```cpp
bool SDLManager::pollEvent(SDL_Event &outEvent);
```

Polls one SDL event from the queue. Called repeatedly in the game loop to drain all pending events.

### Input Dispatch

In `Game::handle_Input()` ([src/game.cpp](../src/game.cpp#L165)):

```cpp
void Game::handle_Input() {
    SDL_Event ev;
    while (sdl_manager.pollEvent(ev)) {
        if (ev.type == SDL_QUIT) {
            running = false;
            return;
        }
        
        State *cur = state_machine.getCurrent();
        if (cur)
            cur->handleInput(ev);  // Delegate to active state
    }
}
```

**Flow:**
1. Poll events from SDL
2. Check for window close (`SDL_QUIT`)
3. Pass all other events to the active state's `handleInput()` method

### State Input Handling

Each state implements `handleInput(const SDL_Event &ev)`. Example from Menu ([src/states/menu.cpp](../src/states/menu.cpp#L66)):

```cpp
void Menu::handleInput(const SDL_Event &ev) {
    if (ev.type == SDL_KEYDOWN) {
        if (ev.key.keysym.sym == SDLK_UP) {
            selectedIndex = (selectedIndex == 0) ? 1 : 0;
            if (soundMgr)
                soundMgr->playSound("no-select");
        } 
        else if (ev.key.keysym.sym == SDLK_DOWN) {
            selectedIndex = (selectedIndex == 1) ? 0 : 1;
            if (soundMgr)
                soundMgr->playSound("no-select");
        } 
        else if (ev.key.keysym.sym == SDLK_RETURN || 
                 ev.key.keysym.sym == SDLK_KP_ENTER) {
            result = selectedIndex;
            if (soundMgr)
                soundMgr->playSound("select");
        }
    }
}
```

## Current Controls

### Menu State

| Key | Action |
|-----|--------|
| **UP** | Move selection up (High Score → Play) |
| **DOWN** | Move selection down (Play → High Score) |
| **RETURN** / **KP_ENTER** | Confirm selection |
| **ESC** (window close) | Exit game |

### Sound Feedback

- **"no-select"** sound plays when navigating
- **"select"** sound plays when confirming

Located in [assets/sounds/](../assets/sounds/):
- [no-select.wav](../assets/sounds/no-select.wav)
- [select.wav](../assets/sounds/select.wav)

## Adding Input to a New State

When creating a new state (e.g., `GameplayState`), implement `handleInput()`:

```cpp
void GameplayState::handleInput(const SDL_Event &ev) {
    if (ev.type == SDL_KEYDOWN) {
        switch (ev.key.keysym.sym) {
            case SDLK_LEFT:
                // Move paddle left
                break;
            case SDLK_RIGHT:
                // Move paddle right
                break;
            case SDLK_SPACE:
                // Launch ball / pause / etc.
                break;
        }
    }
}
```

## Future Input Types

Currently not implemented:
- **Mouse input** – Could be useful for menu clicking or paddle control
- **Controller input** – SDL2 supports joysticks/gamepads via `SDL_JOYAXIS`, `SDL_JOYBUTTONDOWN`, etc.
- **Touch input** – Mobile support via `SDL_FINGERDOWN`, `SDL_FINGERMOTION`, etc.

These can be added by extending the SDL event polling and dispatching mechanism.
