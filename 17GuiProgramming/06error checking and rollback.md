# Error Checking and Rollback

SDL functions return **0 or a null pointer** on failure. Check each step. If something fails after partial setup, **undo** what you already created before exiting.

## Pattern

```
if (SDL_Init(SDL_INIT_VIDEO) != 0)
{
    SDL_Log("SDL_Init: %s", SDL_GetError());
    return 1;
}

SDL_Window* window = SDL_CreateWindow(/* ... */);
if (window == nullptr)
{
    SDL_Log("SDL_CreateWindow: %s", SDL_GetError());
    SDL_Quit();
    return 1;
}

SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
if (renderer == nullptr)
{
    SDL_Log("SDL_CreateRenderer: %s", SDL_GetError());
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
}
```

Each failure path cleans up **only what was created so far**. That is **rollback**.

## Error strings

| API family | Error function |
|------------|----------------|
| SDL core | `SDL_GetError()` |
| SDL2_image | `IMG_GetError()` |
| SDL2_ttf | `TTF_GetError()` |
| SDL2_mixer | `Mix_GetError()` |

Use `SDL_Log("message: %s", SDL_GetError());` so TxtBook and desktop both show readable output.

## Load failures

Texture and font loads fail at runtime if the path is wrong or the asset was not copied into the build (or wasm filesystem):

```
SDL_Texture* tex = IMG_LoadTexture(renderer, "assets/dude.png");
if (tex == nullptr)
{
    SDL_Log("IMG_LoadTexture: %s", IMG_GetError());
    // rollback renderer, window, SDL_Quit...
    return 1;
}
```

> PREFERENCE: **Fail fast** at startup for missing assets. Do not run the game loop with null textures.

## Try it now

### Exercise 1: Rollback

Prompt: `SDL_CreateRenderer` fails after the window was created. Name two cleanup calls before `return 1`.

:::details Answer

**`SDL_DestroyWindow(window)`** and **`SDL_Quit()`**.

:::
