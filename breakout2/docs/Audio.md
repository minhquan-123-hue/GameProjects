# Audio

## Overview

The breakout2 project uses **SDL2_mixer** to handle sound effects. Currently, the system is minimal, supporting only short sound effects triggered by menu navigation and selection.

## SoundManager Class

Located in [lib/systems/sound_manager.h](../lib/systems/sound_manager.h) and [src/systems/sound_manager.cpp](../src/systems/sound_manager.cpp):

```cpp
class SoundManager {
public:
    bool init();                                  // Initialize SDL_mixer
    bool loadSound(const std::string &name, 
                   const std::string &path);      // Load .wav file from disk
    void playSound(const std::string &name);      // Play a loaded sound
    void clean();                                 // Free all resources
    
private:
    bool initialized;
    std::map<std::string, Mix_Chunk *> sounds;    // Sound cache
};
```

## Initialization

In `Game::initializeSoundManager()` ([src/game.cpp](../src/game.cpp#L93)):

```cpp
bool Game::initializeSoundManager() {
    if (!sound_manager.init())
        return false;

    const std::string assets_dir = BREAKOUT2_ASSETS_DIR;
    return sound_manager.loadSound("no-select", assets_dir + "/sounds/no-select.wav")
        && sound_manager.loadSound("select", assets_dir + "/sounds/select.wav");
}
```

**Sequence:**
1. Call `SoundManager::init()` to initialize SDL_mixer
2. Load sounds by name and file path
3. Sounds are stored in a map for quick lookup

## Currently Loaded Sounds

### "no-select"
- **File:** [assets/sounds/no-select.wav](../assets/sounds/no-select.wav)
- **Usage:** Played when menu navigation occurs (UP/DOWN arrow keys)
- **Triggered in:** [src/states/menu.cpp](../src/states/menu.cpp#L73), line 73 (UP) and line 79 (DOWN)

### "select"
- **File:** [assets/sounds/select.wav](../assets/sounds/select.wav)
- **Usage:** Played when confirming a menu selection (RETURN key)
- **Triggered in:** [src/states/menu.cpp](../src/states/menu.cpp#L85), line 85

## Playback

Sounds are played synchronously using the name key:

```cpp
soundManager->playSound("no-select");  // Plays immediately, no waiting
soundManager->playSound("select");
```

The `Mix_Chunk` pointer is looked up in the internal `sounds` map and played on the first available channel.

## Cleanup

In `Game::clean()` ([src/game.cpp](../src/game.cpp#L142)):

```cpp
sound_manager.clean();  // Destroy all Mix_Chunk pointers and close SDL_mixer
```

## Limitations & Future Enhancements

**Current limitations:**
- **No music** – Only sound effects supported
- **No volume control** – Sounds play at default mixer volume
- **No channel management** – All sounds play on auto-assigned channels; collision with gameplay sounds possible
- **No sound events** – Sounds only trigger from Menu state; gameplay sounds not yet implemented

**Potential additions:**
- Background music for menu and gameplay
- Volume/mute controls
- Sound priority system (UI sounds vs. game sounds)
- Looping sounds for continuous audio
- Audio state transitions (fade in/out) between states

## Asset Locations

All audio files are in [assets/sounds/](../assets/sounds/):
- `no-select.wav`
- `select.wav`

To add new sounds:

1. Place `.wav` file in `assets/sounds/`
2. Load in initialization: `sound_manager.loadSound("name", path)`
3. Play when needed: `soundManager->playSound("name")`
