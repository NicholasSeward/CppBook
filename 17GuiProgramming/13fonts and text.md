# Fonts and Text

**SDL2_ttf** loads a **`.ttf`** font file, renders a string to a **surface**, then you upload to a **texture** for drawing.

Load the font **once**. Do not call `TTF_OpenFont` every frame.

```sdl2
// @asset: assets/font.ttf
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

int main(int, char**)
{
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    SDL_Window* window = SDL_CreateWindow(
        "Text",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        640,
        480,
        SDL_WINDOW_SHOWN);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    TTF_Font* font = TTF_OpenFont("assets/font.ttf", 28);
    if (font == nullptr)
    {
        SDL_Log("TTF_OpenFont: %s", TTF_GetError());
        return 1;
    }

    SDL_Color white{255, 255, 255, 255};
    SDL_Surface* surface = TTF_RenderUTF8_Blended(font, "Hello SDL2", white);
    SDL_Texture* textTex = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect textRect{20, 20, surface->w, surface->h};
    SDL_FreeSurface(surface);

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

Small projects often redraw the same text texture every frame (cheap enough). If the score or label changes rarely, render a **new texture only when the string changes** and reuse it until the next change.

> PREFERENCE: Do not reload the font file per frame. Do not re-render unchanged strings every frame if you have hundreds of labels.

## Try it now

### Exercise 1: Surface vs texture

Prompt: After `TTF_RenderUTF8_Blended`, why call `SDL_CreateTextureFromSurface`?

:::details Answer

The renderer draws **textures**, not surfaces. The texture is the GPU-friendly version for `SDL_RenderCopy`.

:::
