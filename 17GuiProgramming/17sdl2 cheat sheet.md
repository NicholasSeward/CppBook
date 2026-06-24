# SDL2 Cheat Sheet

Quick reference for the libraries used in this chapter.

## SDL2 (core)

**Structs:** `SDL_Window`, `SDL_Renderer`, `SDL_Event`, `SDL_Rect`, `SDL_Texture`, `SDL_Surface`, `SDL_Color`

| Task | Functions |
|------|-----------|
| Init / quit | `SDL_Init`, `SDL_Quit`, `SDL_GetError`, `SDL_Log` |
| Window | `SDL_CreateWindow`, `SDL_DestroyWindow` |
| Renderer | `SDL_CreateRenderer`, `SDL_DestroyRenderer` |
| Draw color | `SDL_SetRenderDrawColor` |
| Clear / present | `SDL_RenderClear`, `SDL_RenderPresent` |
| Rectangles | `SDL_RenderFillRect`, `SDL_RenderDrawRect` |
| Textures | `SDL_CreateTextureFromSurface`, `SDL_QueryTexture`, `SDL_RenderCopy`, `SDL_DestroyTexture` |
| Events | `SDL_PollEvent`, `SDL_WaitEvent` |
| Keyboard hint (browser) | `SDL_SetHint(SDL_HINT_EMSCRIPTEN_KEYBOARD_ELEMENT, "#canvas")` |
| Mouse | `SDL_GetMouseState` |
| Time | `SDL_GetTicks`, `SDL_Delay` |

**Common event types:** `SDL_QUIT`, `SDL_KEYDOWN`, `SDL_KEYUP`, `SDL_MOUSEMOTION`, `SDL_MOUSEBUTTONDOWN`, `SDL_MOUSEBUTTONUP`

**Init flags:** `SDL_INIT_VIDEO`, `SDL_INIT_AUDIO`

## SDL2_image

| Task | Functions |
|------|-----------|
| Init / quit | `IMG_Init`, `IMG_Quit`, `IMG_GetError` |
| Load | `IMG_Load`, `IMG_LoadTexture` |
| Init flags | `IMG_INIT_PNG`, `IMG_INIT_JPG` |

## SDL2_ttf

| Task | Functions |
|------|-----------|
| Init / quit | `TTF_Init`, `TTF_Quit`, `TTF_GetError` |
| Font | `TTF_OpenFont`, `TTF_CloseFont` |
| Render | `TTF_RenderUTF8_Blended`, `TTF_RenderText_Solid` |

## SDL2_mixer

| Task | Functions |
|------|-----------|
| Audio device | `Mix_OpenAudio`, `Mix_CloseAudio` |
| Init codecs | `Mix_Init`, `Mix_Quit`, `Mix_GetError` |
| Effects | `Mix_LoadWAV`, `Mix_FreeChunk`, `Mix_PlayChannel`, `Mix_HaltChannel` |
| Music | `Mix_LoadMUS`, `Mix_FreeMusic`, `Mix_PlayMusic`, `Mix_HaltMusic`, `Mix_PauseMusic` |
| Volume | `Mix_Volume`, `Mix_VolumeMusic` |

## SDL2_gfx

| Task | Functions |
|------|-----------|
| Lines / boxes | `lineRGBA`, `boxRGBA`, `filledBoxRGBA`, `roundedBoxRGBA` |
| Circles | `circleRGBA`, `filledCircleRGBA` |
| Other | `polygonRGBA`, `rotozoomSurface` (see docs) |

Colors: separate `Uint8` RGBA args or packed `Uint32` **`0xAABBGGRR`** depending on function.

## Extension summary

| Library | Purpose |
|---------|---------|
| SDL2 | Window, events, input, 2D renderer |
| SDL2_image | Load PNG/JPG/etc. |
| SDL2_ttf | TrueType text |
| SDL2_mixer | WAV/OGG audio |
| SDL2_gfx | Extra primitives |

## Try it now

### Exercise 1: Present draw

Prompt: Which function shows the finished frame after drawing?

:::details Answer

**`SDL_RenderPresent`**

:::
