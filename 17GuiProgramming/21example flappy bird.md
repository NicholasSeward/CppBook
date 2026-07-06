# Example: Flappy Bird Clone

A rough **Flappy Bird**–style clone: tap **Space** or **click** to flap, dodge **scrolling pipes**, score when you pass a pair. The bird is half-scale **`dude.png`**, rotated smoothly with **`birdVy`**.

**New here:** even **pipe spacing**, difficulty that **ramps** (faster scroll, smaller gaps), logged **speed** / **gap** values, and **`SDL_RenderCopyEx`** tilt.

```sdl2
// @asset: assets/dude.png
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <cmath>

struct Pipe
{
    float x{0.0f};
    int gapY{200};
    int gapH{120};
    bool scored{false};
};

class FlappyGame
{
public:
    static constexpr float kBirdX{120.0f};
    static constexpr float kPipeSpacing{240.0f};

    void setSpriteSize(int texW, int texH)
    {
        drawW = texW / 2;
        drawH = texH / 2;
        hitRadius = static_cast<int>(0.7f * static_cast<float>(std::min(drawW, drawH)) * 0.5f);
    }

    void reset()
    {
        birdY = 240.0f;
        birdVy = 0.0f;
        birdAngle = 75.0f;
        score = 0;
        alive = true;
        gameTime = 0.0f;
        logTimer = 0.0f;
        scrollSpeed = 55.0f;
        gapH = 200;
        pipes.clear();
        for (int i{0}; i < 3; ++i)
        {
            spawnPipe(640.0f + i * kPipeSpacing);
        }
    }

    void flap()
    {
        if (alive)
        {
            birdVy = -280.0f;
        }
        else
        {
            reset();
        }
    }

    void update(float dt)
    {
        if (!alive)
        {
            return;
        }

        gameTime += dt;
        scrollSpeed = std::min(220.0f, 55.0f + gameTime * 12.0f + static_cast<float>(score) * 6.0f);
        gapH = std::max(72, 200 - static_cast<int>(gameTime * 10.0f) - score * 8);

        logTimer += dt;
        if (logTimer >= 1.0f)
        {
            SDL_Log("speed %.0f gap %d", scrollSpeed, gapH);
            logTimer = 0.0f;
        }

        const float gravity{620.0f};
        birdVy += gravity * dt;
        birdY += birdVy * dt;

        const float vyFlap{-280.0f};
        const float vyShort{120.0f};
        float t{(birdVy - vyFlap) / (vyShort - vyFlap)};
        t = std::max(0.0f, std::min(1.0f, t));
        const float targetAngle{60.0f + t * 30.0f};
        birdAngle += (targetAngle - birdAngle) * std::min(1.0f, dt * 10.0f);

        if (birdY - static_cast<float>(hitRadius) < 0.0f)
        {
            birdY = static_cast<float>(hitRadius);
            birdVy = 0.0f;
        }
        if (birdY + static_cast<float>(hitRadius) > 480.0f)
        {
            alive = false;
        }

        for (Pipe& pipe : pipes)
        {
            pipe.x -= scrollSpeed * dt;

            SDL_Rect top{static_cast<int>(pipe.x), 0, 52, pipe.gapY};
            SDL_Rect bottom{
                static_cast<int>(pipe.x),
                pipe.gapY + pipe.gapH,
                52,
                480 - (pipe.gapY + pipe.gapH)};

            if (hits(top) || hits(bottom))
            {
                alive = false;
            }

            if (!pipe.scored && pipe.x + 52 < kBirdX)
            {
                pipe.scored = true;
                ++score;
            }
        }

        pipes.erase(
            std::remove_if(pipes.begin(), pipes.end(), [](const Pipe& p) { return p.x < -60.0f; }),
            pipes.end());

        spawnPipeIfNeeded();
    }

    void draw(SDL_Renderer* renderer, SDL_Texture* dude) const
    {
        for (const Pipe& pipe : pipes)
        {
            SDL_SetRenderDrawColor(renderer, 50, 180, 90, 255);
            SDL_Rect top{static_cast<int>(pipe.x), 0, 52, pipe.gapY};
            SDL_Rect bottom{
                static_cast<int>(pipe.x),
                pipe.gapY + pipe.gapH,
                52,
                480 - (pipe.gapY + pipe.gapH)};
            SDL_RenderFillRect(renderer, &top);
            SDL_RenderFillRect(renderer, &bottom);
        }

        SDL_Rect dest{
            static_cast<int>(kBirdX) - drawW / 2,
            static_cast<int>(birdY) - drawH / 2,
            drawW,
            drawH};
        SDL_Point pivot{drawW / 2, drawH / 2};
        SDL_RenderCopyEx(renderer, dude, nullptr, &dest, birdAngle, &pivot, SDL_FLIP_NONE);

        char label[32];
        SDL_snprintf(label, sizeof(label), "Score: %d", score);
        stringRGBA(renderer, 20, 20, label, 240, 240, 250, 255);

        if (!alive)
        {
            stringRGBA(renderer, 180, 220, "Crashed! Space to retry", 255, 120, 120, 255);
        }
    }

    int getScore() const
    {
        return score;
    }

private:
    float birdY{240.0f};
    float birdVy{0.0f};
    float birdAngle{100.0f};
    int drawW{16};
    int drawH{24};
    int hitRadius{8};
    int score{0};
    bool alive{true};
    float gameTime{0.0f};
    float logTimer{0.0f};
    float scrollSpeed{55.0f};
    int gapH{200};
    std::vector<Pipe> pipes;

    void spawnPipe(float startX)
    {
        Pipe pipe{};
        pipe.x = startX;
        pipe.gapH = gapH;
        const int margin{40};
        const int maxGapY{480 - pipe.gapH - margin};
        pipe.gapY = margin + std::rand() % std::max(1, maxGapY - margin);
        pipes.push_back(pipe);
    }

    void spawnPipeIfNeeded()
    {
        float rightmost{-kPipeSpacing};
        for (const Pipe& pipe : pipes)
        {
            rightmost = std::max(rightmost, pipe.x);
        }

        if (pipes.empty() || rightmost < 640.0f - kPipeSpacing)
        {
            const float spawnX{pipes.empty() ? 640.0f : rightmost + kPipeSpacing};
            spawnPipe(spawnX);
        }
    }

    bool hits(SDL_Rect r) const
    {
        const float bx{kBirdX};
        const float by{birdY};
        const float hr{static_cast<float>(hitRadius)};
        const float closestX{
            std::max(static_cast<float>(r.x), std::min(bx, static_cast<float>(r.x + r.w)))};
        const float closestY{
            std::max(static_cast<float>(r.y), std::min(by, static_cast<float>(r.y + r.h)))};
        const float dx{bx - closestX};
        const float dy{by - closestY};
        return dx * dx + dy * dy < hr * hr;
    }
};

int main(int, char**)
{
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);

    SDL_Window* window = SDL_CreateWindow(
        "Flappy",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        640,
        480,
        SDL_WINDOW_SHOWN);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_Texture* dude = IMG_LoadTexture(renderer, "assets/dude.png");
    if (dude == nullptr)
    {
        SDL_Log("IMG_LoadTexture: %s", IMG_GetError());
        return 1;
    }

    int texW{0};
    int texH{0};
    SDL_QueryTexture(dude, nullptr, nullptr, &texW, &texH);

    FlappyGame game{};
    game.setSpriteSize(texW, texH);
    game.reset();

    bool running{true};
    SDL_Event event{};
    Uint32 lastTicks{SDL_GetTicks()};

    while (running)
    {
        Uint32 now{SDL_GetTicks()};
        float dt = static_cast<float>(now - lastTicks) / 1000.0f;
        lastTicks = now;

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = false;
            }
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE)
            {
                game.flap();
            }
            if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                game.flap();
            }
        }

        game.update(dt);

        SDL_SetRenderDrawColor(renderer, 120, 200, 235, 255);
        SDL_RenderClear(renderer);

        game.draw(renderer, dude);

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    return 0;
}
```

**Highlighted pieces:**

- **`FlappyGame::draw(renderer)`** — game owns pipes, bird, and HUD.
- **`SDL_RenderCopyEx`** — half-scale **`dude.png`**; angle **60°** right after flap → **90°** after a short fall, smoothed each frame.
- **Hit circle** — **70%** of half-sprite radius; pipe collision uses circle-vs-rect test.
- **Pipe spacing** — spawn at **`rightmost + kPipeSpacing`** when the last pipe scrolls far enough left (fixed **240 px** gaps).
- **Difficulty** — new pipes use a smaller **`gapH`** over time; values logged each second.

This finishes the chapter examples. Review the [SDL2 Cheat Sheet](17sdl2%20cheat%20sheet.md) or build a desktop copy with [CMake and vcpkg](18cmake%20vcpkg%20and%20links.md).

## Try it now

### Exercise 1: Score trigger

Prompt: When does `score` increment in the code above?

:::details Answer

When a pipe's right edge passes the bird (`pipe.x + 52 < kBirdX`) and that pipe has not been scored yet.

:::

### Exercise 2: Extend it

Prompt: Name one feature you would add first to make this feel more like the original game.

:::details Answer

Any reasonable idea: **pipe cap** sprites, **ground** collision strip, or **high score** saved to a file (ties to the Files chapter).

:::
