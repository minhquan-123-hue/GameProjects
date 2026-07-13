# State Machine

## Overview

The breakout2 project uses a classic **State Pattern** to manage discrete game states. Only one state is active at a time (stored as `current` in `StateMachine`). The pattern allows clean separation of behavior for different game modes (menu, gameplay, high scores, etc.).

## Architecture

### State Interface

All states inherit from the abstract `State` class defined in [lib/states/statemachine.h](../lib/states/statemachine.h):

```cpp
class State {
public:
    virtual ~State() {}
    virtual void onEnter() {}      // Called when state becomes active
    virtual void onExit() {}       // Called when leaving this state
    virtual void handleInput(const SDL_Event &ev) = 0;  // Process input
    virtual void update() = 0;                          // Logic update
    virtual void render(SDL_Renderer *renderer) = 0;    // Draw frame
};
```

### StateMachine Class

Located in [lib/states/statemachine.h](../lib/states/statemachine.h) and [src/states/statemachine.cpp](../src/states/statemachine.cpp):

```cpp
class StateMachine {
public:
    void changeState(State *newState);      // Switch to a new state
    State *getCurrent() const;              // Get active state (read-only)
private:
    State *current;                         // Currently active state
};
```

### State Lifecycle

When `changeState()` is called:

1. If a state is already active, call its `onExit()` method
2. Delete the old state from memory
3. Set `current` to the new state
4. If the new state is not null, call its `onEnter()` method

This ensures clean initialization and cleanup of resources.

## Current States

### Menu State

**File:** [lib/states/menu.h](../lib/states/menu.h) / [src/states/menu.cpp](../src/states/menu.cpp)

A simple menu with two selectable options:
- **Play** – Currently exits the app (placeholder)
- **High Score** – Currently exits the app (placeholder)

**Key features:**
- Two-item menu with up/down arrow navigation
- Selected item changes text color (yellow for selected, white for normal)
- Supports Enter/Return to confirm selection
- Plays sounds on navigation ("no-select") and confirmation ("select")
- Renders a background image and pre-rendered text textures

**Constructor and setup:**
- Menu state requires pointers to be set before entering:
  - `setRenderer(SDL_Renderer *r)`
  - `setManagers(FontManager *fm, GraphicManager *gm)`
  - `setSoundManager(SoundManager *sm)`

**Result tracking:**
- `getResult()` returns `-1` if no selection yet, `0` for Play, `1` for High Score

## Adding a New State

To add a new state (e.g., `GameplayState`):

1. **Create the header** ([lib/states/gameplay.h](../lib/states/gameplay.h)):
   ```cpp
   #pragma once
   #include <states/statemachine.h>
   
   class GameplayState : public State {
   public:
       GameplayState();
       ~GameplayState();
       void onEnter() override;
       void onExit() override;
       void handleInput(const SDL_Event &ev) override;
       void update() override;
       void render(SDL_Renderer *renderer) override;
   };
   ```

2. **Implement the class** ([src/states/gameplay.cpp](../src/states/gameplay.cpp)):
   - `onEnter()`: Initialize game objects, load resources, set up managers
   - `update()`: Handle game logic, collisions, scoring
   - `handleInput()`: Process gameplay controls
   - `render()`: Draw all game objects
   - `onExit()`: Clean up allocated memory and resources

3. **Transition to it** from another state (e.g., from Menu):
   ```cpp
   GameplayState *game = new GameplayState();
   game->setRenderer(renderer);
   game->setManagers(fontMgr, gfxMgr);
   state_machine.changeState(game);
   ```

4. **The main game loop** in [src/game.cpp](../src/game.cpp) will automatically call your state's methods:
   ```cpp
   State *cur = state_machine.getCurrent();
   if (cur) {
       cur->handleInput(ev);    // In handle_Input()
       cur->update();           // In process_Logic()
       cur->render(renderer);   // In render_frame()
   }
   ```

## Integration with Game Loop

The `Game` class in [src/game.cpp](../src/game.cpp) drives the state machine:

- **handle_Input()** – Polls SDL events and passes them to the active state
- **process_Logic()** – Calls `update()` on the active state
- **render_frame()** – Calls `render()` on the active state

The loop continues until `running` is set to false (e.g., when a state decision like "Play" or "Quit" is triggered).
