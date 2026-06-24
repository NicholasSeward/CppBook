# Images and Textures

A **surface** is pixel data in CPU memory. A **texture** is that data (or similar) prepared for the **GPU** through `SDL_Renderer`.

**SDL2_image** loads files (PNG, JPG, etc.) and can build a **texture** directly:

```cpp
SDL_Texture* tex = IMG_LoadTexture(renderer, "assets/dude.png");
```

## Blit / copy

Historically **blit** meant copying a block of pixels. In SDL2 you **`SDL_RenderCopy`** a texture to the screen (or a sub-rectangle):

```cpp
SDL_Rect dest{x, y, w, h};
SDL_RenderCopy(renderer, tex, nullptr, &dest);
```

`nullptr` source uses the full texture.

## Load once, draw every frame

**Never** call `IMG_LoadTexture` inside the game loop. Disk and decode are slow. Load at startup, draw each frame.

```sdl2
// @asset: assets/dude.png
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

int main(int, char**)
{
    SDL_SetHint(SDL_HINT_EMSCRIPTEN_KEYBOARD_ELEMENT, "#canvas");
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);

    SDL_Window* window = SDL_CreateWindow(
        "Texture",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        640,
        480,
        SDL_WINDOW_SHOWN);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_Texture* player = IMG_LoadTexture(renderer, "assets/dude.png");
    if (player == nullptr)
    {
        SDL_Log("IMG_LoadTexture: %s", IMG_GetError());
        return 1;
    }

    int texW{0};
    int texH{0};
    SDL_QueryTexture(player, nullptr, nullptr, &texW, &texH);

    int x{280};
    int y{200};

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
                if (event.key.keysym.sym == SDLK_LEFT)
                {
                    x -= 10;
                }
                if (event.key.keysym.sym == SDLK_RIGHT)
                {
                    x += 10;
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 40, 44, 52, 255);
        SDL_RenderClear(renderer);

        SDL_Rect dest{x, y, texW, texH};
        SDL_RenderCopy(renderer, player, nullptr, &dest);

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    return 0;
}
```

![dude sprite](assets/dude.png)

## Try it now

### Exercise 1: Where to load

Prompt: Should `IMG_LoadTexture` run inside or outside the `while (running)` loop?

:::details Answer

**Outside** (once at startup).

:::
