# Audio With SDL2_mixer

**SDL2_mixer** handles sound effects and music. Load files **once** at startup.

| Type | Typical API | File example |
|------|-------------|--------------|
| Sound effect | `Mix_LoadWAV`, `Mix_PlayChannel` | `.wav` |
| Music | `Mix_LoadMUS`, `Mix_PlayMusic` | `.ogg` |

Chapter assets: `assets/boing.wav` (sound effect), `assets/music.ogg` (background music).

Docs: [SDL2_mixer wiki](https://wiki.libsdl.org/SDL2_mixer/FrontPage).

## Sound effect on click

```sdl2
// @asset: assets/boing.wav
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

int main(int, char**)
{
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
    int flash{0};

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
                flash = 12;
            }
        }

        if (flash > 0)
        {
            --flash;
        }

        int bg = flash > 0 ? 90 : 50;
        SDL_SetRenderDrawColor(renderer, bg, bg, 60, 255);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    return 0;
}
```

Click the canvas to play the sound; background flashes briefly so you see the event fired.

## Background music

Load music once, loop with **`Mix_PlayMusic(music, -1)`** (`-1` = loop forever). Stop with **`Mix_HaltMusic()`** on quit.

```sdl2
// @asset: assets/music.ogg
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

int main(int, char**)
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 512);
    if ((Mix_Init(MIX_INIT_OGG) & MIX_INIT_OGG) != MIX_INIT_OGG)
    {
        SDL_Log("Mix_Init: %s", Mix_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow(
        "Music",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        640,
        480,
        SDL_WINDOW_SHOWN);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    Mix_Music* bgm = Mix_LoadMUS("assets/music.ogg");
    if (bgm == nullptr)
    {
        SDL_Log("Mix_LoadMUS: %s", Mix_GetError());
        return 1;
    }

    Mix_PlayMusic(bgm, -1);

    bool running{true};
    SDL_Event event{};
    int bar{0};

    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = false;
            }
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_m)
            {
                if (Mix_PausedMusic())
                {
                    Mix_ResumeMusic();
                }
                else
                {
                    Mix_PauseMusic();
                }
            }
        }

        bar = (bar + 3) % 600;

        SDL_SetRenderDrawColor(renderer, 30, 32, 48, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 120, 200, 255, 255);
        SDL_Rect visualizer{bar, 220, 40, 40};
        SDL_RenderFillRect(renderer, &visualizer);

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    Mix_HaltMusic();
    return 0;
}
```

Music starts automatically. Press **`M`** to pause/resume. The moving bar shows the loop is alive.

> NOTE: Do not call `Mix_LoadWAV` or `Mix_LoadMUS` inside the game loop.

## Try it now

### Exercise 1: Channel vs music

Prompt: Short coin sound: `Mix_PlayChannel` or `Mix_PlayMusic`?

:::details Answer

**`Mix_PlayChannel`** (one-shot effect on a channel). **`Mix_PlayMusic`** is for longer background tracks.

:::

### Exercise 2: Loop flag

Prompt: What does the second argument `-1` mean in `Mix_PlayMusic(bgm, -1)`?

:::details Answer

**Loop forever** until you halt or replace the music.

:::
