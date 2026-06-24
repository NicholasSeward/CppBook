# A Simple Engine and Delta Time

Scattering `SDL_PollEvent`, update logic, and draw code across `main` gets messy. A small **engine** struct can own the loop pieces:

- Process events
- Update game objects using **`deltaTime`**
- Draw everything
- Track frame timing

## `deltaTime` movement

Instead of `x += 4` per frame, use **units per second**:

```
x += speedX * deltaTimeSeconds;
```

Same speed whether the machine runs 60 or 144 FPS.

## Minimal engine sketch

```sdl2
#include <SDL2/SDL.h>

struct Engine
{
    SDL_Window* window{nullptr};
    SDL_Renderer* renderer{nullptr};
    bool running{true};
    float deltaTime{0.0f};
    Uint32 lastTicks{0};

    bool init()
    {
        SDL_SetHint(SDL_HINT_EMSCRIPTEN_KEYBOARD_ELEMENT, "#canvas");
        if (SDL_Init(SDL_INIT_VIDEO) != 0)
        {
            return false;
        }

        window = SDL_CreateWindow(
            "Engine",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            640,
            480,
            SDL_WINDOW_SHOWN);

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        lastTicks = SDL_GetTicks();
        return renderer != nullptr;
    }

    void step()
    {
        Uint32 now{SDL_GetTicks()};
        deltaTime = static_cast<float>(now - lastTicks) / 1000.0f;
        lastTicks = now;

        SDL_Event event{};
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = false;
            }
        }

        SDL_SetRenderDrawColor(renderer, 20, 20, 30, 255);
        SDL_RenderClear(renderer);

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }
};

int main(int, char**)
{
    Engine engine{};
    if (!engine.init())
    {
        return 1;
    }

    while (engine.running)
    {
        engine.step();
    }

    return 0;
}
```

Extend `step()` with your sprite list, input handling, and `deltaTime` updates. Anything that moves can read `engine.deltaTime` each frame.

> PREFERENCE: One **`engine.step()`** per frame keeps `main` readable. Grow the engine only as far as the project needs.

## Try it now

### Exercise 1: Why delta time?

Prompt: At 30 FPS vs 120 FPS, why is `x += 100 * deltaTime` better than `x += 2`?

:::details Answer

**`100 * deltaTime`** moves ~100 units per **second** regardless of frame count. **`x += 2`** moves faster when more frames run per second.

:::
