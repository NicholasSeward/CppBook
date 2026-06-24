# Audio With SDL2_mixer

**SDL2_mixer** handles sound effects and music. Load files **once** at startup.

| Type | Typical API | File example |
|------|-------------|--------------|
| Sound effect | `Mix_LoadWAV`, `Mix_PlayChannel` | `.wav` |
| Music | `Mix_LoadMUS`, `Mix_PlayMusic` | `.ogg` |

Chapter assets: `assets/boing.wav` (sound effect), `assets/music.ogg` (background music).

## Sound effect on click

```sdl2
// @asset: assets/boing.wav
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

int main(int, char**)
{
    SDL_SetHint(SDL_HINT_EMSCRIPTEN_KEYBOARD_ELEMENT, "#canvas");
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 512);

    SDL_Window* window = SDL_CreateWindow(
        "Audio",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        640,
        480,
        SDL_WINDOW_SHOWN);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    Mix_Chunk* boing = Mix_LoadWAV("assets/boing.wav");
    if (boing == nullptr)
    {
        SDL_Log("Mix_LoadWAV: %s", Mix_GetError());
        return 1;
    }

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
                Mix_PlayChannel(-1, boing, 0);
            }
        }

        SDL_SetRenderDrawColor(renderer, 50, 50, 60, 255);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    return 0;
}
```

Click the canvas to play the sound.

## Background music pattern

Load music once, loop with `Mix_PlayMusic(music, -1)` (`-1` = loop forever). Use a separate `.ogg` in your own projects; same rules: load at init, not per frame.

```cpp
Mix_Music* bgm = Mix_LoadMUS("assets/music.ogg");
Mix_PlayMusic(bgm, -1);
// Mix_HaltMusic() on quit
```

> NOTE: Do not call `Mix_LoadWAV` or `Mix_LoadMUS` inside the game loop.

## Try it now

### Exercise 1: Channel vs music

Prompt: Short coin sound: `Mix_PlayChannel` or `Mix_PlayMusic`?

:::details Answer

**`Mix_PlayChannel`** (one-shot effect on a channel). **`Mix_PlayMusic`** is for longer background tracks.

:::
