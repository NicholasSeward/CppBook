# Window, Renderer, and Game Loop

A minimal SDL2 interactive program has five steps:

1. Init SDL
2. Create **window**
3. Create **renderer**
4. **Game loop** (events + draw)
5. Cleanup

This section shows steps 2–4 without rollback on failure (error checking comes next).

## Window and renderer

```sdl2
#include <SDL2/SDL.h>

int main(int, char**)
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow(
        "Hello SDL2",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        640,
        480,
        SDL_WINDOW_SHOWN);

    SDL_Renderer* renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED);

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

        SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
        SDL_RenderClear(renderer);

        static int slide{0};
        slide = (slide + 2) % 440;
        SDL_Rect bar{slide, 200, 200, 80};
        SDL_SetRenderDrawColor(renderer, 0, 180, 255, 255);
        SDL_RenderFillRect(renderer, &bar);

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    return 0;
}
```

## The renderer as paintbrush

Think of **`SDL_Renderer*`** as a **paintbrush** tied to one window. Whoever holds the pointer can draw for that frame. You typically pass it to helper functions:

```cpp
void drawBar(SDL_Renderer* renderer, SDL_Rect rect)
{
    SDL_SetRenderDrawColor(renderer, 0, 180, 255, 255);
    SDL_RenderFillRect(renderer, &rect);
}
```

One renderer, one window, one frame at a time: clear, draw everything, then `SDL_RenderPresent`.

For a board game class (tic-tac-toe, Connect Four), a common pattern is:

```cpp
class Board
{
public:
    void draw(SDL_Renderer* renderer) const
    {
        // draw grid, pieces, highlights
    }
};
```

`main` clears the screen, calls `board.draw(renderer)`, then presents — the board owns how it looks.

## Frame steps inside the loop

| Step | API |
|------|-----|
| Handle events | `SDL_PollEvent` |
| Update game state | Your variables |
| Clear back buffer | `SDL_RenderClear` |
| Draw | rects, textures, gfx |
| Show frame | `SDL_RenderPresent` |
| Yield / cap FPS | `SDL_Delay(16)` |

## Try it now

### Exercise 1: Present

Prompt: What happens if you draw but never call `SDL_RenderPresent`?

:::details Answer

Nothing visible updates on screen (or you keep seeing an old frame). **`SDL_RenderPresent`** swaps/shows the buffer you drew into.

:::
