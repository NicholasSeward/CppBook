# Double Buffering and Coordinates

## Double buffering

If you drew directly to the visible screen while the user watched, you would see **flicker** and **torn** frames (half-old, half-new image).

**Double buffering** keeps two buffers:

1. **Back buffer** — where you draw this frame (hidden).
2. **Front buffer** — what the user currently sees.

Each frame you draw on the back buffer, then **`SDL_RenderPresent`** **flips** (swaps) them. The old front becomes the new back. That swap is fast and avoids showing half-finished work.

Because you are always drawing on top of whatever was in the back buffer last frame, **stale pixels can linger** if you only update part of the screen. That can look like flicker when the two buffers disagree.

## When buffers fight

SDL's renderer keeps **two buffers** in play. After each **`SDL_RenderPresent`**, the buffer you just finished drawing becomes visible, and the other buffer becomes your new draw target — but it still holds **whatever image was shown two frames ago**. If you skip **`SDL_RenderClear`** or only repaint part of the screen, the two buffers drift out of sync. Each present **flips** between mismatched images and the result **flickers**.

The demo below does that on purpose. **Before the loop**, we build two different images — one with a full clear, one drawn on top of the old back buffer without clearing. After two **`SDL_RenderPresent`** calls, each buffer holds a different picture. The loop then **only presents** (flips) between them; no new drawing. **`SDL_Delay(500)`** slows the swap so you can see it without rapid flashing.

```sdl2
#include <SDL2/SDL.h>

int main(int, char**)
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow(
        "Fighting buffers",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        640,
        480,
        SDL_WINDOW_SHOWN);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_SetRenderDrawColor(renderer, 35, 40, 90, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 220, 80, 255);
    SDL_Rect yellow{220, 180, 200, 200};
    SDL_RenderFillRect(renderer, &yellow);
    SDL_RenderPresent(renderer);

    SDL_SetRenderDrawColor(renderer, 80, 255, 120, 255);
    SDL_Rect green{280, 220, 200, 200};
    SDL_RenderFillRect(renderer, &green);
    SDL_RenderPresent(renderer);

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

        SDL_RenderPresent(renderer);
        SDL_Delay(500);
    }

    return 0;
}
```

Each present **flips** to the other pre-built buffer — blue with yellow square vs. the smeared green-on-old-image version. Press the window close button to quit.

## The fix: redraw everything

For now, the usual approach is simple and works well:

1. **`SDL_RenderClear`** — wipe the back buffer (often a solid background color).
2. Draw **everything** for this frame.
3. **`SDL_RenderPresent`** — show it.

Modern CPUs — even without GPU acceleration — can redraw hundreds of simple items at 60 FPS. **Partial updates** (only redraw what changed) save work but need careful design; games often skip that until they need it.

See [SDL2 wiki — SDL_RenderPresent](https://wiki.libsdl.org/SDL2/SDL_RenderPresent).

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
    float markerX{10.0f};
    float markerY{10.0f};

    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = false;
            }
        }

        markerX += 1.5f;
        markerY += 0.8f;
        if (markerX > 590.0f)
        {
            markerX = 10.0f;
        }
        if (markerY > 430.0f)
        {
            markerY = 10.0f;
        }

        SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 80, 80, 255);
        SDL_Rect topLeft{10, 10, 40, 40};
        SDL_RenderFillRect(renderer, &topLeft);

        SDL_SetRenderDrawColor(renderer, 80, 255, 80, 255);
        SDL_Rect bottomRight{590, 430, 40, 40};
        SDL_RenderFillRect(renderer, &bottomRight);

        SDL_SetRenderDrawColor(renderer, 255, 255, 100, 255);
        SDL_Rect moving{
            static_cast<int>(markerX),
            static_cast<int>(markerY),
            40,
            40};
        SDL_RenderFillRect(renderer, &moving);

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    return 0;
}
```

Red square: small **x**, small **y** (top-left). Green square: large **x**, large **y** (bottom-right). Yellow square moves each frame so you can see the loop running.

## Float positions, int pixels

Screens use **integer** pixel coordinates, but game logic often stores **`float` or `double`** positions. Example: slide 10 pixels in one second at 60 FPS — about **0.166 pixels per frame**. If you only tracked `int` position, you would round to zero every frame and **never move**. Accumulate in floats, **cast to `int`** when building `SDL_Rect` or calling draw functions.

## Try it now

### Exercise 1: Move down

Prompt: You want a sprite to move toward the bottom of the window. Do you increase or decrease `y`?

:::details Answer

**Increase** `y` (down is positive Y).

:::

Prompt: In the fighting-buffers demo, the loop only calls `SDL_RenderPresent`. Why does the image still change?

:::details Answer

The two buffers were set up **before** the loop with different pictures. Each present **swaps** front and back, so you alternate between them even with no new drawing.

:::

### Exercise 3: Clearing every frame

Prompt: Why does flicker go away if you call `SDL_RenderClear` on **every** frame before drawing?

:::details Answer

**`SDL_RenderClear`** wipes the back buffer so both buffers stay in sync. Each present flips a **complete** frame instead of a mix of old and new pixels.

:::
