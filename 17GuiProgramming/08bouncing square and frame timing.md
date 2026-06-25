# Bouncing Square and Frame Timing

Put init, loop, and draw together: a square moves each frame and bounces off the walls.

```sdl2
#include <SDL2/SDL.h>

int main(int, char**)
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow(
        "Bounce",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        640,
        480,
        SDL_WINDOW_SHOWN);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    const int squareSize{40};
    int x{100};
    int y{100};
    int speedX{4};
    int speedY{3};

    bool running{true};
    SDL_Event event{};

    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = false;
            }
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
            {
                running = false;
            }
        }

        x += speedX;
        y += speedY;

        if (x < 0 || x > 640 - squareSize)
        {
            speedX = -speedX;
        }
        if (y < 0 || y > 480 - squareSize)
        {
            speedY = -speedY;
        }

        SDL_SetRenderDrawColor(renderer, 25, 25, 35, 255);
        SDL_RenderClear(renderer);

        SDL_Rect square{x, y, squareSize, squareSize};
        SDL_SetRenderDrawColor(renderer, 255, 200, 50, 255);
        SDL_RenderFillRect(renderer, &square);

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    return 0;
}
```

## `SDL_Delay(16)`

Roughly **60 frames per second** if each frame's work is cheap: 1000 ms / 60 ≈ 16 ms per frame.

That is fine for learning and light demos. It assumes every frame costs ~0 ms besides the delay. Real games measure **how long the frame actually took** (next section).

> NOTE: Removing **`SDL_Delay`** in the browser can spin the loop as fast as possible and **freeze the tab**. Keep a delay or proper frame limiter in TxtBook playgrounds.

## Try it now

### Exercise 1: Wall bounce

Prompt: The square hits the right edge (`x > 640 - squareSize`). What line reverses horizontal motion?

:::details Answer

**`speedX = -speedX;`**

:::
