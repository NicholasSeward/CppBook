# Double Buffering and Coordinates

## Double buffering

While you are drawing, the user should not see half-finished work. **Double buffering** means drawing to a hidden **back buffer**, then showing the finished picture in one step.

With **`SDL_Renderer`**, SDL handles the two buffers for you. Your job each frame is:

1. **`SDL_RenderClear`** — start with a clean back buffer (usually a solid color).
2. **Draw** everything for this frame.
3. **`SDL_RenderPresent`** — show it.

Draw calls update the back buffer only. Nothing reaches the window until **`SDL_RenderPresent`**.

After each present, SDL treats the back buffer as **empty/undefined** for the next frame. Do not skip **`SDL_RenderClear`** hoping old pixels are still there — [SDL's docs](https://wiki.libsdl.org/SDL2/SDL_RenderPresent) tell you to clear every frame even if you redraw the whole screen.

That three-step pattern is enough for this course. Optimizing away full redraws is possible later; most 2D games just clear and draw everything each frame.

## Coordinate system

SDL uses a **screen-style** origin, not the Y-up graph from algebra class.

```
(0,0) ──────────────► +X
  │
  ▼
 +Y
```

- **(0, 0)** is the **top-left** of the window.
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
        SDL_RenderFillRect(renderer, &SDL_Rect{10, 10, 40, 40});

        SDL_SetRenderDrawColor(renderer, 80, 255, 80, 255);
        SDL_RenderFillRect(renderer, &SDL_Rect{590, 430, 40, 40});

        SDL_SetRenderDrawColor(renderer, 255, 255, 100, 255);
        SDL_RenderFillRect(renderer, &SDL_Rect{
            static_cast<int>(markerX),
            static_cast<int>(markerY),
            40,
            40});

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    return 0;
}
```

Red: top-left. Green: bottom-right. Yellow: moves each frame.

## Float positions, int pixels

Screens use **integer** pixels, but game logic often uses **`float`** positions. Moving 10 pixels in one second at 60 FPS is about **0.17 pixels per frame** — an `int` would stay at 0 every frame. Store **`float`**, **cast to `int`** when you build an `SDL_Rect`.

## Try it now

### Exercise 1: Move down

Prompt: You want a sprite to move toward the bottom of the window. Do you increase or decrease `y`?

:::details Answer

**Increase** `y` (down is positive Y).

:::

### Exercise 2: Clear every frame

Prompt: Why call `SDL_RenderClear` at the start of each frame?

:::details Answer

It gives you a known starting state. SDL does not guarantee the back buffer still holds last frame's pixels after **`SDL_RenderPresent`**.

:::
