# Keyboard and Mouse Input

SDL delivers input as **events**. Common types:

| Event | When |
|-------|------|
| `SDL_KEYDOWN` / `SDL_KEYUP` | Key pressed or released |
| `SDL_MOUSEMOTION` | Mouse moved |
| `SDL_MOUSEBUTTONDOWN` / `UP` | Button pressed or released |
| `SDL_QUIT` | Close window |

Key symbols use names like **`SDLK_LEFT`**, **`SDLK_SPACE`**, **`SDLK_a`**. Full list: [SDL_KeyCode](https://wiki.libsdl.org/SDL2/SDL_KeyCode) and [CategoryKeycode](https://wiki.libsdl.org/SDL2/CategoryKeycode).

## Keyboard movement (per key press)

```sdl2
#include <SDL2/SDL.h>

int main(int, char**)
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow(
        "Input",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        640,
        480,
        SDL_WINDOW_SHOWN);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    const int size{32};
    int x{300};
    int y{220};
    const int step{8};

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
            if (event.type == SDL_KEYDOWN)
            {
                switch (event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        running = false;
                        break;
                    case SDLK_LEFT:
                        x -= step;
                        break;
                    case SDLK_RIGHT:
                        x += step;
                        break;
                    case SDLK_UP:
                        y -= step;
                        break;
                    case SDLK_DOWN:
                        y += step;
                        break;
                    default:
                        break;
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 35, 35, 45, 255);
        SDL_RenderClear(renderer);

        SDL_Rect player{x, y, size, size};
        SDL_SetRenderDrawColor(renderer, 100, 220, 255, 255);
        SDL_RenderFillRect(renderer, &player);

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    return 0;
}
```

Key symbol: `event.key.keysym.sym` (for example `SDLK_LEFT`).

## Held keys with a set

`SDL_KEYDOWN` fires once per physical press. For **smooth movement while holding** a key, track which keys are down:

```cpp
#include <unordered_set>

std::unordered_set<SDL_Keycode> keysDown;

// In the event loop:
if (event.type == SDL_KEYDOWN)
{
    keysDown.insert(event.key.keysym.sym);
}
if (event.type == SDL_KEYUP)
{
    keysDown.erase(event.key.keysym.sym);
}

// Later in update logic:
if (keysDown.count(SDLK_LEFT))
{
    x -= step;
}
```

## Mouse motion

```sdl2
#include <SDL2/SDL.h>

int main(int, char**)
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow(
        "Mouse motion",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        640,
        480,
        SDL_WINDOW_SHOWN);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    int mx{320};
    int my{240};
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
            if (event.type == SDL_MOUSEMOTION)
            {
                mx = event.motion.x;
                my = event.motion.y;
            }
        }

        SDL_SetRenderDrawColor(renderer, 25, 28, 38, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 180, 60, 255);
        SDL_Rect cursor{mx - 8, my - 8, 16, 16};
        SDL_RenderFillRect(renderer, &cursor);

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    return 0;
}
```

Move the mouse — the orange square follows **`event.motion.x`** and **`event.motion.y`**.

You can also poll current position without waiting for motion events:

```cpp
int mx{};
int my{};
Uint32 buttons = SDL_GetMouseState(&mx, &my);
```

## Clickable button (rectangle hit test)

```sdl2
#include <SDL2/SDL.h>

bool pointInRect(int px, int py, SDL_Rect r)
{
    return px >= r.x && px < r.x + r.w && py >= r.y && py < r.y + r.h;
}

int main(int, char**)
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow(
        "Button",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        640,
        480,
        SDL_WINDOW_SHOWN);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_Rect button{240, 200, 160, 60};
    bool lit{false};

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
            if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                if (pointInRect(event.button.x, event.button.y, button))
                {
                    lit = !lit;
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 30, 30, 40, 255);
        SDL_RenderClear(renderer);

        if (lit)
        {
            SDL_SetRenderDrawColor(renderer, 80, 200, 120, 255);
        }
        else
        {
            SDL_SetRenderDrawColor(renderer, 120, 120, 140, 255);
        }
        SDL_RenderFillRect(renderer, &button);

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    return 0;
}
```

Click inside the rectangle to toggle color.

## Try it now

### Exercise 1: Mouse vs motion

Prompt: Which event type fires continuously while the mouse moves?

:::details Answer

**`SDL_MOUSEMOTION`**

:::

### Exercise 2: Held vs tap

Prompt: Why is a `keysDown` set better than only handling `SDL_KEYDOWN` for continuous player movement?

:::details Answer

**`SDL_KEYDOWN`** repeats slowly on some systems and only fires on press. A **set** updated on down/up lets you check every frame whether a key is **still held**.

:::
