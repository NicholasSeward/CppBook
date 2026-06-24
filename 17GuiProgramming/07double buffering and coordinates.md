# Double Buffering and Coordinates

## Double buffering

If you drew directly to the visible screen while the user watched, you would see **flicker** and **torn** frames (half-old, half-new image).

**Double buffering**: draw to an off-screen buffer, then show it in one step. SDL's renderer does this for you:

1. `SDL_RenderClear` / draw commands → back buffer
2. `SDL_RenderPresent` → show it

Never rely on partial draws being visible until `SDL_RenderPresent`.

## Coordinate system

SDL uses a **screen-style** origin, not the Y-up graph from algebra class.

```
(0,0) ──────────────► +X
  │
  │
  │
  ▼
 +Y
```

- **(0, 0)** is the **top-left** of the window (or canvas).
- **+X** goes **right**.
- **+Y** goes **down**.

A rectangle at `y = 400` sits near the **bottom** of a 480px-tall window.

```sdl2
#include <SDL2/SDL.h>

int main(int, char**)
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow(
        "Coords",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        640,
        480,
        SDL_WINDOW_SHOWN);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

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
        }

        SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 80, 80, 255);
        SDL_Rect topLeft{10, 10, 40, 40};
        SDL_RenderFillRect(renderer, &topLeft);

        SDL_SetRenderDrawColor(renderer, 80, 255, 80, 255);
        SDL_Rect bottomRight{590, 430, 40, 40};
        SDL_RenderFillRect(renderer, &bottomRight);

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    return 0;
}
```

Red square: small **x**, small **y** (top-left). Green square: large **x**, large **y** (bottom-right).

## Try it now

### Exercise 1: Move down

Prompt: You want a sprite to move toward the bottom of the window. Do you increase or decrease `y`?

:::details Answer

**Increase** `y` (down is positive Y).

:::
