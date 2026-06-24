# Colors and Gfx Primitives

## SDL renderer colors (RGBA bytes)

`SDL_SetRenderDrawColor(renderer, r, g, b, a)` uses **0–255** per channel. **`255`** (`0xFF`) usually means full intensity for that channel.

## Packed `Uint32` colors (SDL2_gfx)

SDL2_gfx often takes a single **`Uint32`** in **`0xAABBGGRR`** order (alpha, blue, green, red in hex):

| Hex | Meaning |
|-----|---------|
| `0xFF0000FF` | Opaque red |
| `0xFFFF0000` | Opaque blue |
| `0xFF00FF00` | Opaque green |
| `0x80FFFFFF` | Half-transparent white |

> NOTE: Other APIs use `0xRRGGBBAA` or floats `0.0–1.0`. **Read the docs** for the library you call.

## Circles with SDL2_gfx

```sdl2
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>

int main(int, char**)
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow(
        "Gfx",
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

        SDL_SetRenderDrawColor(renderer, 25, 25, 30, 255);
        SDL_RenderClear(renderer);

        filledCircleRGBA(renderer, 160, 240, 60, 255, 80, 80, 255);
        filledCircleRGBA(renderer, 320, 240, 60, 80, 200, 255, 255);
        filledCircleRGBA(renderer, 480, 240, 60, 80, 255, 120, 255);

        circleRGBA(renderer, 320, 240, 80, 255, 255, 255, 255);

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    return 0;
}
```

Common SDL2_gfx calls: `lineRGBA`, `boxRGBA`, `filledBoxRGBA`, `circleRGBA`, `filledCircleRGBA`, `roundedBoxRGBA`.

## Try it now

### Exercise 1: Blue packed color

Prompt: In `0xAABBGGRR`, which hex value is full opaque blue?

:::details Answer

**`0xFFFF0000`**

:::
