# The Game Loop and Events

Interactive GUI and game programs share the same skeleton:

1. **Initialize** once (SDL, window, assets).
2. **Loop** until quit: read input, update state, draw frame.
3. **Cleanup** (destroy in reverse order).

Each pass through the loop is one **frame** (roughly one screen refresh).

## The game loop

```sdl2
#include <SDL2/SDL.h>

int main(int, char**)
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow(
        "Loop demo",
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

        static int frame{0};
        ++frame;
        int pulse = 40 + (frame % 60);
        SDL_SetRenderDrawColor(renderer, pulse, 44, 52, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 220, 80, 255);
        SDL_Rect dot{frame % (640 - 20), 230, 20, 20};
        SDL_RenderFillRect(renderer, &dot);

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    return 0;
}
```

Without the loop, the window would flash and close. The loop is why GUI `main` feels "infinite" compared to homework programs.

## Event-driven programming

GUI code is **event-driven**. The OS (or SDL) puts messages in a **queue**: key pressed, mouse moved, window closed. Your code **polls** or waits for events and reacts.

You do not usually spin in `while (keyPressed())` like a tight console hack. You handle events **when they arrive**:

- Press left arrow → move sprite
- Click → play sound or toggle a button
- Close window → set `running = false`

The inner `while (SDL_PollEvent(&event))` drains the queue each frame so no input is stuck waiting.

## Try it now

### Exercise 1: What ends the loop?

Prompt: In the example above, what two event types set `running` to false? (One is shown explicitly; add the other common way users close a window on desktop.)

:::details Answer

**`SDL_QUIT`** (window close / request to quit). On desktop, the user clicking the window's close button generates **`SDL_QUIT`**.

:::
