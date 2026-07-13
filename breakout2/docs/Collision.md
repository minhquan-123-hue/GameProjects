# Collision

## Status

**Collision detection is not yet implemented in breakout2.**

The codebase contains no collision shapes, bounding box calculations, or collision checks. The project currently focuses on the state machine framework, input handling, and rendering.

## Expected Structure (Placeholder)

When collision detection is added, it would likely follow this pattern:

### Collision Shapes

Define basic shapes for game objects:
- **AABB (Axis-Aligned Bounding Box)** – For paddle, ball, bricks
- Represented as: `struct BoundingBox { x, y, width, height }`

### Collision Detection Point

Likely in `GameplayState::update()` (to be implemented):
```cpp
void GameplayState::update() {
    // Update ball position
    ball.update();
    
    // Check collisions
    if (ball.getBounds().collidesWith(paddle.getBounds())) {
        // Handle paddle hit
    }
    
    // Check brick collisions, wall collisions, etc.
}
```

### Current Game Objects (Not Implemented)

When the `GameplayState` is created, it would need:
- **Ball** – Rectangular object with position and velocity
- **Paddle** – Player-controlled rectangular object
- **Bricks** – Grid of destructible rectangular objects
- **Walls** – Screen boundaries

## Next Steps

1. Define collision shapes/bounding boxes
2. Implement AABB intersection tests
3. Add collision callbacks or response logic
4. Integrate into `GameplayState::update()`
5. Test ball-paddle, ball-brick, and ball-wall interactions
