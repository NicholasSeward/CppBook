**Arrow keys** move the sprite; **click** randomizes the background and plays a sound; **Esc** to quit.

```sdl2
// @asset: assets/dude.png
// @asset: assets/font.ttf
// @asset: assets/boing.wav
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <cstdlib>

int main(int, char**) {
    SDL_SetHint(SDL_HINT_EMSCRIPTEN_KEYBOARD_ELEMENT, "#canvas");
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();
    Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 1, 512);
    if ((Mix_Init(MIX_INIT_OGG) & MIX_INIT_OGG) != MIX_INIT_OGG) {
        SDL_Log("Mix_Init OGG: %s", Mix_GetError());
    }

    SDL_Window* window = SDL_CreateWindow(
        "TxtBook SDL2",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        640,
        480,
        SDL_WINDOW_SHOWN);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_Texture* playerTex = IMG_LoadTexture(renderer, "assets/dude.png");
    if (!playerTex) {
        SDL_Log("IMG_LoadTexture: %s", IMG_GetError());
        return 1;
    }

    TTF_Font* font = TTF_OpenFont("assets/font.ttf", 22);
    if (!font) {
        SDL_Log("TTF_OpenFont: %s", TTF_GetError());
        return 1;
    }

    Mix_Chunk* boing = Mix_LoadWAV("assets/boing.wav");
    if (!boing) {
        SDL_Log("Mix_LoadWAV: %s", Mix_GetError());
        return 1;
    }

    SDL_Color white = {255, 255, 255, 255};
    SDL_Surface* titleSurf = TTF_RenderUTF8_Blended(font, "TxtBook SDL2 — assets demo", white);
    SDL_Texture* titleTex = SDL_CreateTextureFromSurface(renderer, titleSurf);
    SDL_Rect titleRect = {16, 12, titleSurf->w, titleSurf->h};
    SDL_FreeSurface(titleSurf);

    int texW = 0;
    int texH = 0;
    SDL_QueryTexture(playerTex, nullptr, nullptr, &texW, &texH);

    Uint8 bgR = 70;
    Uint8 bgG = 130;
    Uint8 bgB = 220;
    int playerX = 304;
    int playerY = 224;
    const int moveStep = 10;

    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        running = false;
                        break;
                    case SDLK_LEFT:
                        playerX -= moveStep;
                        break;
                    case SDLK_RIGHT:
                        playerX += moveStep;
                        break;
                    case SDLK_UP:
                        playerY -= moveStep;
                        break;
                    case SDLK_DOWN:
                        playerY += moveStep;
                        break;
                    default:
                        break;
                }
            }
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                bgR = static_cast<Uint8>(std::rand() % 256);
                bgG = static_cast<Uint8>(std::rand() % 256);
                bgB = static_cast<Uint8>(std::rand() % 256);
                Mix_PlayChannel(-1, boing, 0);
            }
        }

        if (playerX < 0) {
            playerX = 0;
        }
        if (playerY < 0) {
            playerY = 0;
        }
        if (playerX > 640 - texW) {
            playerX = 640 - texW;
        }
        if (playerY > 480 - texH) {
            playerY = 480 - texH;
        }

        SDL_SetRenderDrawColor(renderer, bgR, bgG, bgB, 255);
        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer, titleTex, nullptr, &titleRect);

        roundedBoxRGBA(renderer, playerX - 6, playerY - 6, playerX + texW + 5, playerY + texH + 5, 8, 255, 255, 255, 90);
        SDL_Rect dest = {playerX, playerY, texW, texH};
        SDL_RenderCopy(renderer, playerTex, nullptr, &dest);

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    // Skip SDL_Destroy* so TxtBook can freeze the last presented frame.
    return 0;
}
```
