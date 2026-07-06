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

SDL2_gfx functions ending in **`Color`** (not **`RGBA`**) take one packed **`Uint32`**:

```
filledCircleColor(renderer, x, y, radius, 0xFF0000FF); // opaque red
```

## Circles with SDL2_gfx

Same colors, two styles: top row uses packed **`Uint32`** (`*Color`); bottom row uses separate **RGBA bytes** (`*RGBA`).

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

    const Uint32 red{0xFF0000FF};
    const Uint32 blue{0xFFFF0000};
    const Uint32 green{0xFF00FF00};
    const Uint32 white{0xFFFFFFFF};

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

        filledCircleColor(renderer, 160, 150, 50, red);
        filledCircleColor(renderer, 320, 150, 50, blue);
        filledCircleColor(renderer, 480, 150, 50, green);
        circleColor(renderer, 320, 150, 58, white);

        filledCircleRGBA(renderer, 160, 330, 50, 255, 0, 0, 255);
        filledCircleRGBA(renderer, 320, 330, 50, 0, 0, 255, 255);
        filledCircleRGBA(renderer, 480, 330, 50, 0, 255, 0, 255);
        circleRGBA(renderer, 320, 330, 58, 255, 255, 255, 255);

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    return 0;
}
```

Top: **`filledCircleColor`** / **`circleColor`**. Bottom: **`filledCircleRGBA`** / **`circleRGBA`** with matching red, blue, and green.

Other gfx pairs: `lineRGBA` / `lineColor`, `boxRGBA` / `boxColor`, `roundedBoxRGBA`.

## Falling circles with bounce count

Store **`float`** `y` and velocity so motion stays smooth; cast when drawing. Count bounces when the circle hits the floor:

```sdl2
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <cmath>
#include <cstdio>

int main(int, char**)
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow(
        "Bouncing circles",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        640,
        480,
        SDL_WINDOW_SHOWN);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    float y{40.0f};
    float vy{0.0f};
    const float gravity{0.35f};
    const int radius{24};
    int bounces{0};

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

        vy += gravity;
        y += vy;

        const float floorY{480.0f - radius};
        if (y >= floorY)
        {
            y = floorY;
            vy = -vy * 0.82f;
            if (std::abs(vy) > 0.5f)
            {
                ++bounces;
            }
            else
            {
                vy = 0.0f;
            }
        }

        SDL_SetRenderDrawColor(renderer, 18, 20, 28, 255);
        SDL_RenderClear(renderer);

        filledCircleRGBA(renderer, 320, static_cast<Sint16>(y), radius, 255, 120, 80, 255);

        char label[32];
        SDL_snprintf(label, sizeof(label), "Bounces: %d", bounces);
        stringRGBA(renderer, 20, 20, label, 220, 220, 230, 255);

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    return 0;
}
```

## Try it now

### Exercise 1: Blue packed color

Prompt: In `0xAABBGGRR`, which hex value is full opaque blue?

:::details Answer

**`0xFFFF0000`**

:::

### Exercise 2: Float vs int

Prompt: Why track `y` as `float` but pass `static_cast<int>(y)` to `filledCircleRGBA`?

:::details Answer

**Float** accumulates fractional motion each frame (smooth fall). **Draw APIs** need integer pixel centers.

:::
