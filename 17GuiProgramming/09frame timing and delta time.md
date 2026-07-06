# Frame Timing and Delta Time

`SDL_Delay(16)` is a blunt instrument. Better approach:

1. Record time at start of frame (`SDL_GetTicks`).
2. Do work (input, update, draw).
3. Compute elapsed ms.
4. Delay only the **remainder** to hit a target FPS.
5. Use **delta time** for movement: `position += velocity * deltaTimeSeconds`.

## Bouncing ball with adjustable FPS

A ball starts near the **top** with **`vx` about 10 pixels per frame at 60 FPS** (600 units per second with delta time). Vertical motion uses **`y = f(t)`** — a periodic function of elapsed time — so the bounce height never fades. **Up/Down** arrows raise or lower the target FPS by 5 (minimum **5**). Once per second the log prints **target** and **actual** FPS.

```sdl2
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <cmath>

float bounceY(float t, float yTop, float yFloor)
{
    const float omega{2.0f * 3.14159265f * 0.75f};
    const float s{std::sin(omega * t)};
    return yTop + (yFloor - yTop) * s * s;
}

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

    const int ballRadius{14};
    const float yTop{static_cast<float>(ballRadius + 8)};
    const float yFloor{480.0f - static_cast<float>(ballRadius)};

    float ballX{120.0f};
    float ballY{yTop};
    float vx{600.0f};
    float t{0.0f};

    int targetFps{60};
    int frameCount{0};
    Uint32 fpsTimer{SDL_GetTicks()};
    Uint32 lastFrameTicks{fpsTimer};

    bool running{true};
    SDL_Event event{};

    while (running)
    {
        Uint32 frameStart{SDL_GetTicks()};
        float dt{static_cast<float>(frameStart - lastFrameTicks) / 1000.0f};
        lastFrameTicks = frameStart;
        if (dt > 0.1f)
        {
            dt = 0.1f;
        }

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = false;
            }
            if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_UP)
                {
                    targetFps += 5;
                }
                if (event.key.keysym.sym == SDLK_DOWN)
                {
                    targetFps -= 5;
                }
                if (targetFps < 5)
                {
                    targetFps = 5;
                }
            }
        }

        t += dt;
        ballX += vx * dt;
        ballY = bounceY(t, yTop, yFloor);

        if (ballX - ballRadius < 0.0f)
        {
            ballX = static_cast<float>(ballRadius);
            vx = -vx;
        }
        if (ballX + ballRadius > 640.0f)
        {
            ballX = 640.0f - static_cast<float>(ballRadius);
            vx = -vx;
        }

        SDL_SetRenderDrawColor(renderer, 30, 30, 40, 255);
        SDL_RenderClear(renderer);

        filledCircleRGBA(
            renderer,
            static_cast<Sint16>(ballX),
            static_cast<Sint16>(ballY),
            ballRadius,
            255,
            200,
            80,
            255);

        SDL_RenderPresent(renderer);

        Uint32 frameEnd{SDL_GetTicks()};
        float targetFrameMs{1000.0f / static_cast<float>(targetFps)};
        float frameMs{static_cast<float>(frameEnd - frameStart)};
        float delayMs{targetFrameMs - frameMs};
        if (delayMs > 0.0f)
        {
            SDL_Delay(static_cast<Uint32>(delayMs));
        }

        ++frameCount;
        if (frameEnd - fpsTimer >= 1000)
        {
            SDL_Log("target %d FPS, actual %d FPS", targetFps, frameCount);
            frameCount = 0;
            fpsTimer = frameEnd;
        }
    }

    return 0;
}
```

**`f(t)`** here is `yTop + (yFloor - yTop) * sin²(ωt)`. At `t = 0` the ball is at the top with zero vertical speed; at the bottom `sin²(ωt) = 1` and vertical speed is zero again — a lossless bounce. **`t += dt`** each frame, so the arc keeps the same timing even when FPS changes.

Click the canvas, then use **Up/Down** to change the cap. Horizontal speed still uses **`vx * dt`**; vertical motion follows **`f(t)`** instead of integrating velocity with damping.

## Why delta time matters

Moving **4 pixels per frame** feels fine at 60 FPS and too fast at 120 FPS. Instead:

```
x += speedX * deltaTimeSeconds;
```

Same speed in **units per second** on any frame rate. A simple engine exposes `deltaTime` each step (see [section 16](16simple%20engine%20and%20delta%20time.md)).

## Try it now

### Exercise 1: Heavy frame

Prompt: One frame takes 25 ms but your target is 16.7 ms (60 FPS). Should `SDL_Delay` add more delay that frame?

:::details Answer

**No.** Work already exceeded the budget. `delayMs` would be negative; skip extra delay (and consider optimizing that frame).

:::

### Exercise 2: Target vs actual

Prompt: You set target FPS to 30 with Down arrow, but the log says `actual 28`. Is that necessarily a bug?

:::details Answer

**Not always.** **Target** is what you aim for with the limiter; **actual** is counted over a real second of wall-clock time and can differ slightly due to timer granularity and work time per frame.

:::
