# Architecture: ECS vs. Object-Oriented

## Current Architecture: Plain Object-Oriented (OOP)

**The breakout2 project does NOT use an Entity-Component-System (ECS) pattern.**

Instead, it uses a straightforward **object-oriented design** with:
- **Concrete classes** for specific game objects and managers
- **State polymorphism** via the State interface
- **Manager objects** for cross-cutting concerns (rendering, input, audio)

## Current Structure

### Core Classes

| Class | Purpose | File |
|-------|---------|------|
| `Game` | Main game loop and initialization | [lib/game.h](../lib/game.h), [src/game.cpp](../src/game.cpp) |
| `State` | Abstract base for all game states | [lib/states/statemachine.h](../lib/states/statemachine.h) |
| `StateMachine` | Manages the active state | [lib/states/statemachine.h](../lib/states/statemachine.h), [src/states/statemachine.cpp](../src/states/statemachine.cpp) |
| `Menu` | Concrete menu state | [lib/states/menu.h](../lib/states/menu.h), [src/states/menu.cpp](../src/states/menu.cpp) |

### Manager Classes (Systems)

| Class | Responsibility | File |
|-------|-----------------|------|
| `SDLManager` | SDL initialization, window, renderer, event polling | [lib/systems/sdl_manager.h](../lib/systems/sdl_manager.h), [src/systems/sdl_manager.cpp](../src/systems/sdl_manager.cpp) |
| `FontManager` | Font loading and text texture creation | [lib/systems/font_manager.h](../lib/systems/font_manager.h) |
| `GraphicManager` | Image/background loading and access | [lib/systems/graphic_manager.h](../lib/systems/graphic_manager.h) |
| `SoundManager` | Sound effect loading and playback | [lib/systems/sound_manager.h](../lib/systems/sound_manager.h) |

### Object Ownership

```
Game
├── StateMachine
│   └── State* (e.g., Menu)
│       ├── references FontManager
│       ├── references GraphicManager
│       └── references SoundManager
├── SDLManager (window, renderer, event handling)
├── FontManager (fonts, text rendering)
├── GraphicManager (backgrounds, images)
└── SoundManager (audio effects)
```

## Design Patterns Used

### 1. State Pattern
- Single active state at a time
- States delegate to specific state implementations
- See [docs/StateMachine.md](StateMachine.md)

### 2. Manager/Singleton Pattern
- `FontManager`, `GraphicManager`, `SoundManager` are instantiated once in `Game`
- Passed to states via setter methods (`setRenderer()`, `setManagers()`, etc.)
- No global singletons; ownership is explicit

### 3. Polymorphism
- `State` is an abstract interface
- `Menu` is a concrete implementation
- Game loop calls virtual methods (`handleInput()`, `update()`, `render()`)

## Why Not ECS?

ECS is most beneficial for:
- Large numbers of similar entities (hundreds of bullets, particles, etc.)
- Rapid composition of behavior at runtime
- Efficient data-oriented processing (cache locality)

Breakout2 currently has:
- Small number of objects (paddle, ball, bricks, menu items)
- Fixed behavior per object type
- Simple initialization and lifecycle

**ECS overhead would be unnecessary at this scale.** As the project grows (more entity types, complex interactions), a migration to ECS could be considered.

## When to Consider ECS

Refactor to ECS if:
- Many game objects with similar but varying behavior
- Entities frequently gain/lose components at runtime
- Performance profiling shows cache misses or too many virtual function calls
- Multiple gameplay states need to share entity data

## Current Advantages

- **Simple and readable** – Class hierarchy is straightforward
- **Low overhead** – No component lookups or systems scheduling
- **Easy to debug** – Object identity and lifecycle are explicit
- **Suitable for prototype** – Good for initial development and design validation

## Proposed GameplayState Structure (Not ECS)

When the gameplay state is added, it would look like:

```cpp
class GameplayState : public State {
private:
    Ball ball;
    Paddle paddle;
    std::vector<Brick> bricks;
    int lives;
    int score;
    
    // Managers (passed in via setManagers)
    FontManager *fontMgr;
    GraphicManager *gfxMgr;
    SoundManager *soundMgr;
    
    void handleCollisions();
    void updateScore();
    void resetRound();
};
```

This is still plain OOP – no components, no entity system. Objects are concrete and self-contained.
