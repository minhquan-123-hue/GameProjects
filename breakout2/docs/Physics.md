# Physics

## Status

**Physics simulation is not yet implemented in breakout2.**

The codebase contains no movement vectors, velocity, acceleration, gravity, or physics-based behavior. The project is currently in the foundation phase, with state management, input, and rendering infrastructure in place.

## What Exists

The only motion-like behavior currently is **menu navigation** – the `selectedIndex` variable changes when UP/DOWN keys are pressed, causing visual feedback (text color change). This is pure state management, not physics.

## Expected Physics Components (Not Implemented)

When breakout gameplay is added, the following will likely be needed:

### Ball Physics
- **Position** – `{x, y}` coordinates
- **Velocity** – `{vx, vy}` direction and speed
- **Update loop:**
  ```cpp
  ball.x += ball.vx * deltaTime;
  ball.y += ball.vy * deltaTime;
  ```
- **Boundary behavior** – Reflect off walls, reset if out of bounds

### Paddle Physics
- **Position** – `{x, y}` for top-left corner
- **Input-driven movement** – Move left/right based on player input
- **Boundary clamping** – Keep paddle within screen

### Collision Response
- **Ball-Paddle** – Reflect ball upward
- **Ball-Brick** – Destroy brick, reflect ball
- **Ball-Wall** – Reflect ball in opposite direction
- **Ball-Floor** – Lose life or end game

### Frame-Rate Independence
To ensure consistent physics across devices:
```cpp
float deltaTime = frameTime / 1000.0f;  // Convert to seconds
ball.update(deltaTime);
```

## Next Steps

1. Define game object classes (Ball, Paddle, Brick, etc.) with position/velocity
2. Implement a simple integration method (Euler integration is fine for breakout)
3. Add collision response logic
4. Implement delta-time in the update loop for frame-rate independence
5. Test ball movement and reflection behavior

## References

- A GameplayState would likely live in [src/states/gameplay.cpp](../src/states/gameplay.cpp) (to be created)
- Ball and Paddle classes could live in [lib/](../lib/) as separate files
- Physics updates happen in the active state's `update()` method
