# Frame Timing and Delta Time

`SDL_Delay(16)` is a blunt instrument. Better approach:

1. Record time at start of frame (`SDL_GetTicks`).
2. Do work.
3. Compute elapsed ms.
4. Delay only the **remainder** to hit a target FPS.
5. Store **delta time** for movement: `position += velocity * dt`.

## Measured frame limiter

```sdl2
#include <SDL2/SDL.h>

int main(int, char**)
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow(
        "FPS",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        640,
        480,
        SDL_WINDOW_SHOWN);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    const int targetFps{60};
    const float targetFrameMs{1000.0f / static_cast<float>(targetFps)};

    Uint32 lastTicks{SDL_GetTicks()};
    int frameCount{0};
    Uint32 fpsTimer{lastTicks};

    bool running{true};
    SDL_Event event{};

    while (running)
    {
        Uint32 frameStart{SDL_GetTicks()};

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = false;
            }
        }

        SDL_SetRenderDrawColor(renderer, 30, 30, 40, 255);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);

        Uint32 frameEnd{SDL_GetTicks()};
        float frameMs{static_cast<float>(frameEnd - frameStart)};
        float delayMs{targetFrameMs - frameMs};
        if (delayMs > 0.0f)
        {
            SDL_Delay(static_cast<Uint32>(delayMs));
        }

        ++frameCount;
        if (frameEnd - fpsTimer >= 1000)
        {
            SDL_Log("FPS: %d", frameCount);
            frameCount = 0;
            fpsTimer = frameEnd;
        }
    }

    return 0;
}
```

## Why delta time matters

Moving **4 pixels per frame** feels fine at 60 FPS and too fast at 120 FPS. Instead:

```
x += speedX * deltaTimeSeconds;
```

Same speed in **units per second** on any frame rate. A simple engine exposes `deltaTime` each step (see section 15).

## Try it now

### Exercise 1: Heavy frame

Prompt: One frame takes 25 ms but your target is 16.7 ms. Should `SDL_Delay` add more delay that frame?

:::details Answer

**No.** Work already exceeded the budget. `delayMs` would be negative; skip extra delay (and consider optimizing that frame).

:::
