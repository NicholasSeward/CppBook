# SDL2 Init and Cleanup

SDL2 is explicit and a bit **old school**: you **init** each subsystem you need, and on shutdown you **destroy in reverse order**.

## Minimal init and quit

```sdl2
#include <SDL2/SDL.h>

int main(int, char**)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_Log("SDL_Init: %s", SDL_GetError());
        return 1;
    }

    SDL_Log("SDL video initialized\n");

    SDL_Quit();
    return 0;
}
```

`SDL_INIT_VIDEO` is required for window and renderer work. Add `SDL_INIT_AUDIO` when you use SDL2_mixer.

## Extension libraries

Load helpers only when you need them:

| Library | Init | Quit |
|---------|------|------|
| SDL2_image | `IMG_Init(IMG_INIT_PNG)` | `IMG_Quit()` |
| SDL2_ttf | `TTF_Init()` | `TTF_Quit()` |
| SDL2_mixer | `Mix_OpenAudio(...)` then `Mix_Init(flags)` | `Mix_CloseAudio()`, `Mix_Quit()` |

Typical startup order:

1. `SDL_Init`
2. `IMG_Init` / `TTF_Init` / `Mix_OpenAudio` as needed
3. Create window and renderer
4. Load assets

Shutdown (reverse):

1. Free textures, fonts, sounds
2. Destroy renderer, window
3. `Mix_Quit`, `TTF_Quit`, `IMG_Quit`
4. `SDL_Quit`

> NOTE: In TxtBook **`sdl2`** playgrounds you may skip `SDL_Destroy*` at the end so the last frame stays visible. On a **desktop** build, always destroy in reverse order.

## Browser keyboard hint

In TxtBook, arrow keys need focus on the canvas:

```cpp
SDL_SetHint(SDL_HINT_EMSCRIPTEN_KEYBOARD_ELEMENT, "#canvas");
```

Call once after `SDL_Init`.

## Try it now

### Exercise 1: Order

Prompt: You created window, then renderer, then loaded a texture. What do you destroy first on shutdown?

:::details Answer

The **texture** first, then **renderer**, then **window**, then `SDL_Quit` (and extension quits in reverse of their init).

:::
