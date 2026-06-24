# Keyboard and Mouse Input

SDL delivers input as **events**. Common types:

| Event | When |
|-------|------|
| `SDL_KEYDOWN` / `SDL_KEYUP` | Key pressed or released |
| `SDL_MOUSEMOTION` | Mouse moved |
| `SDL_MOUSEBUTTONDOWN` / `UP` | Button pressed or released |
| `SDL_QUIT` | Close window |

## Keyboard movement

```sdl2
#include <SDL2/SDL.h>

int main(int, char**)
{
    SDL_SetHint(SDL_HINT_EMSCRIPTEN_KEYBOARD_ELEMENT, "#canvas");
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

## Mouse position and clicks

```cpp
if (event.type == SDL_MOUSEMOTION)
{
    int mx = event.motion.x;
    int my = event.motion.y;
}

if (event.type == SDL_MOUSEBUTTONDOWN)
{
    if (event.button.button == SDL_BUTTON_LEFT)
    {
        // click at event.button.x, event.button.y
    }
}
```

Or poll current position:

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
    SDL_SetHint(SDL_HINT_EMSCRIPTEN_KEYBOARD_ELEMENT, "#canvas");
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
