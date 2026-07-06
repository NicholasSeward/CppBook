# Fonts and Text

**SDL2_ttf** loads a **`.ttf`** font file, renders a string to a **surface**, then you upload to a **texture** for drawing.

Load the font **once**. Do not call `TTF_OpenFont` every frame.

## Clock demo

A simple digital clock — just text centered on screen. The texture is rebuilt **only when the time string changes** (once per second).

```sdl2
// @asset: assets/font.ttf
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <ctime>
#include <string>

int main(int, char**)
{
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    SDL_Window* window = SDL_CreateWindow(
        "Clock",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        640,
        480,
        SDL_WINDOW_SHOWN);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    TTF_Font* font = TTF_OpenFont("assets/font.ttf", 48);
    if (font == nullptr)
    {
        SDL_Log("TTF_OpenFont: %s", TTF_GetError());
        return 1;
    }

    SDL_Texture* textTex{nullptr};
    SDL_Rect textRect{};
    std::string lastTime{};

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

        char timeBuf[16];
        std::time_t now{std::time(nullptr)};
        std::strftime(timeBuf, sizeof(timeBuf), "%H:%M:%S", std::localtime(&now));

        if (lastTime != timeBuf)
        {
            lastTime = timeBuf;

            if (textTex != nullptr)
            {
                SDL_DestroyTexture(textTex);
            }

            SDL_Color white{255, 255, 255, 255};
            SDL_Surface* surface = TTF_RenderUTF8_Blended(font, timeBuf, white);
            textTex = SDL_CreateTextureFromSurface(renderer, surface);
            textRect = SDL_Rect{
                (640 - surface->w) / 2,
                (480 - surface->h) / 2,
                surface->w,
                surface->h};
            SDL_FreeSurface(surface);
        }

        SDL_SetRenderDrawColor(renderer, 30, 30, 40, 255);
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, textTex, nullptr, &textRect);
        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    return 0;
}
```

## Caching text

The clock rebuilds its texture only when **`%H:%M:%S`** changes. Small projects can re-render every frame; with many labels or large fonts, cache textures and refresh on change.

> PREFERENCE: Do not reload the font file per frame. Do not re-render unchanged strings every frame if you have hundreds of labels.

## Try it now

### Exercise 1: Surface vs texture

Prompt: After `TTF_RenderUTF8_Blended`, why call `SDL_CreateTextureFromSurface`?

:::details Answer

The renderer draws **textures**, not surfaces. The texture is the GPU-friendly version for `SDL_RenderCopy`.

:::

### Exercise 2: When to re-render text

Prompt: In the clock demo, why compare `lastTime != timeBuf` before calling `TTF_RenderUTF8_Blended` again?

:::details Answer

The digits only change **once per second**. Re-rendering the same string every frame would waste work; rebuild the texture when the text actually changes.

:::
