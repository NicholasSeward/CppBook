# Example: Simple Platformer

A minimal side-view platformer: **gravity**, **platforms**, the **`dude.png`** sprite, a **jump sound**, and **looping background music**. Arrow keys move; **Space** jumps.

Concepts from earlier sections appear together — **float physics**, **texture draw**, **audio**, and **`SDL_Rect`** collision.

```sdl2
// @asset: assets/dude.png
// @asset: assets/boing.wav
// @asset: assets/music.ogg
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <vector>

struct Platform
{
    SDL_Rect rect;
};

bool overlaps(const SDL_Rect& a, const SDL_Rect& b)
{
    return a.x < b.x + b.w && a.x + a.w > b.x && a.y < b.y + b.h && a.y + a.h > b.y;
}

class Player
{
public:
    float x{100.0f};
    float y{300.0f};
    float vx{0.0f};
    float vy{0.0f};
    bool onGround{false};
    bool jumped{false};
    int texW{32};
    int texH{48};
    int hitW{24};
    int hitH{36};
    int hitOffX{4};
    int hitOffY{6};

    void setTextureSize(int w, int h)
    {
        texW = w;
        texH = h;
        hitW = static_cast<int>(texW * 0.75f);
        hitH = static_cast<int>(texH * 0.75f);
        hitOffX = (texW - hitW) / 2;
        hitOffY = (texH - hitH) / 2;
    }

    SDL_Rect drawRect() const
    {
        return SDL_Rect{
            static_cast<int>(x),
            static_cast<int>(y),
            texW,
            texH};
    }

    SDL_Rect hitBox() const
    {
        return SDL_Rect{
            static_cast<int>(x) + hitOffX,
            static_cast<int>(y) + hitOffY,
            hitW,
            hitH};
    }

    void update(float dt, const std::vector<Platform>& platforms, bool jumpPressed)
    {
        const float moveSpeed{220.0f};
        const float gravity{900.0f};
        const float jumpSpeed{-450.0f};

        jumped = false;
        vx = 0.0f;
        const Uint8* keys = SDL_GetKeyboardState(nullptr);
        if (keys[SDL_SCANCODE_LEFT])
        {
            vx = -moveSpeed;
        }
        if (keys[SDL_SCANCODE_RIGHT])
        {
            vx = moveSpeed;
        }

        if (jumpPressed && onGround)
        {
            vy = jumpSpeed;
            onGround = false;
            jumped = true;
        }

        vy += gravity * dt;
        x += vx * dt;
        y += vy * dt;

        if (x < 0.0f)
        {
            x = 0.0f;
        }
        if (x > 640.0f - texW)
        {
            x = 640.0f - texW;
        }

        onGround = false;
        SDL_Rect box = hitBox();

        for (const Platform& plat : platforms)
        {
            if (!overlaps(box, plat.rect))
            {
                continue;
            }

            if (vy > 0.0f && box.y + box.h - static_cast<int>(vy * dt) <= plat.rect.y + 4)
            {
                y = static_cast<float>(plat.rect.y - hitOffY - hitH);
                vy = 0.0f;
                onGround = true;
            }
        }
    }

    void draw(SDL_Renderer* renderer, SDL_Texture* tex) const
    {
        SDL_Rect dest = drawRect();
        SDL_RenderCopy(renderer, tex, nullptr, &dest);
    }
};

int main(int, char**)
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    IMG_Init(IMG_INIT_PNG);
    Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 512);
    Mix_Init(MIX_INIT_OGG);

    SDL_Window* window = SDL_CreateWindow(
        "Platformer",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        640,
        480,
        SDL_WINDOW_SHOWN);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_Texture* dude = IMG_LoadTexture(renderer, "assets/dude.png");
    Mix_Chunk* boing = Mix_LoadWAV("assets/boing.wav");
    Mix_Music* music = Mix_LoadMUS("assets/music.ogg");
    if (!dude || !boing || !music)
    {
        return 1;
    }

    Player player{};
    int texW{0};
    int texH{0};
    SDL_QueryTexture(dude, nullptr, nullptr, &texW, &texH);
    player.setTextureSize(texW, texH);

    std::vector<Platform> platforms{
        Platform{SDL_Rect{0, 440, 640, 40}},
        Platform{SDL_Rect{120, 340, 140, 16}},
        Platform{SDL_Rect{360, 260, 160, 16}}};

    Mix_PlayMusic(music, -1);
    Mix_VolumeMusic(20);

    bool running{true};
    bool jumpQueued{false};
    SDL_Event event{};
    Uint32 lastTicks{SDL_GetTicks()};

    while (running)
    {
        Uint32 now{SDL_GetTicks()};
        float dt = static_cast<float>(now - lastTicks) / 1000.0f;
        lastTicks = now;
        if (dt > 0.05f)
        {
            dt = 0.05f;
        }

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = false;
            }
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE)
            {
                jumpQueued = true;
            }
        }

        player.update(dt, platforms, jumpQueued);
        jumpQueued = false;

        if (player.jumped)
        {
            Mix_PlayChannel(-1, boing, 0);
        }

        SDL_SetRenderDrawColor(renderer, 70, 130, 180, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 60, 120, 70, 255);
        for (const Platform& plat : platforms)
        {
            SDL_RenderFillRect(renderer, &plat.rect);
        }

        player.draw(renderer, dude);

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    return 0;
}
```

**Highlighted pieces:**

- **`Player::update`** — float **`vy`**, gravity, **`SDL_GetKeyboardState`** for held keys (section 10).
- **`Mix_PlayMusic(..., -1)`** — background loop at low volume (section 14).
- **`Mix_PlayChannel`** on jump — one-shot sfx.
- **`hitBox()`** — collision at **75%** of sprite size, centered; **`drawRect()`** draws the full texture.
- **`player.draw(renderer, dude)`** — same **`draw(renderer)`** pattern as tic-tac-toe.

Next: [Example: Flappy Bird Clone](21example%20flappy%20bird.md).

## Try it now

### Exercise 1: Scan code vs sym

Prompt: This example uses `SDL_SCANCODE_LEFT` instead of `SDLK_LEFT`. Why is that OK?

:::details Answer

**`SDL_GetKeyboardState`** returns an array indexed by **scancode** (physical key position), not key sym (which may vary with layout). Both work; pick one API per input style.

:::
