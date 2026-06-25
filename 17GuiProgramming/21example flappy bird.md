# Example: Flappy Bird Clone

A rough **Flappy Bird**–style clone: tap **Space** or **click** to flap, dodge **scrolling pipes**, score when you pass a pair. No assets required — the bird is a circle, pipes are rectangles.

**New here:** simple **scrolling** world coordinates, **reset on crash**, and on-screen **score**.

```sdl2
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <vector>
#include <cstdlib>
#include <algorithm>

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
    static constexpr int kBirdRadius{16};
    static constexpr float kScrollSpeed{140.0f};

    void reset()
    {
        birdY = 240.0f;
        birdVy = 0.0f;
        score = 0;
        alive = true;
        pipes.clear();
        spawnTimer = 0.0f;
        for (int i{0}; i < 3; ++i)
        {
            spawnPipe(640.0f + i * 220.0f);
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

        const float gravity{620.0f};
        birdVy += gravity * dt;
        birdY += birdVy * dt;

        if (birdY - kBirdRadius < 0.0f)
        {
            birdY = static_cast<float>(kBirdRadius);
            birdVy = 0.0f;
        }
        if (birdY + kBirdRadius > 480.0f)
        {
            alive = false;
        }

        spawnTimer += dt;
        if (spawnTimer > 1.8f)
        {
            spawnTimer = 0.0f;
            spawnPipe(640.0f);
        }

        for (Pipe& pipe : pipes)
        {
            pipe.x -= kScrollSpeed * dt;

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

            if (!pipe.scored && pipe.x + 52 < 120.0f)
            {
                pipe.scored = true;
                ++score;
            }
        }

        pipes.erase(
            std::remove_if(pipes.begin(), pipes.end(), [](const Pipe& p) { return p.x < -60.0f; }),
            pipes.end());
    }

    void draw(SDL_Renderer* renderer) const
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

        filledCircleRGBA(renderer, 120, static_cast<Sint16>(birdY), kBirdRadius, 255, 220, 80, 255);

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
    int score{0};
    bool alive{true};
    float spawnTimer{0.0f};
    std::vector<Pipe> pipes;

    void spawnPipe(float startX)
    {
        Pipe pipe{};
        pipe.x = startX;
        pipe.gapY = 80 + std::rand() % 220;
        pipes.push_back(pipe);
    }

    bool hits(SDL_Rect r) const
    {
        const int bx = 120;
        const int by = static_cast<int>(birdY);
        return bx + kBirdRadius > r.x && bx - kBirdRadius < r.x + r.w && by + kBirdRadius > r.y
            && by - kBirdRadius < r.y + r.h;
    }
};

int main(int, char**)
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow(
        "Flappy",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        640,
        480,
        SDL_WINDOW_SHOWN);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    FlappyGame game{};
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

        game.draw(renderer);

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    return 0;
}
```

**Highlighted pieces:**

- **`FlappyGame::draw(renderer)`** — game owns pipes, bird, and HUD.
- **Scrolling** — subtract from `pipe.x` each frame; erase off-screen pipes.
- **`deltaTime`** — multiply speeds so physics stay consistent (section 09/16).

This finishes the chapter examples. Review the [SDL2 Cheat Sheet](17sdl2%20cheat%20sheet.md) or build a desktop copy with [CMake and vcpkg](18cmake%20vcpkg%20and%20links.md).

## Try it now

### Exercise 1: Score trigger

Prompt: When does `score` increment in the code above?

:::details Answer

When a pipe's right edge passes the bird (`pipe.x + 52 < 120`) and that pipe has not been scored yet.

:::

### Exercise 2: Extend it

Prompt: Name one feature you would add first to make this feel more like the original game.

:::details Answer

Any reasonable idea: **pipe cap** sprites, **ground** collision strip, **rotation** on the bird based on `birdVy`, or **high score** saved to a file (ties to the Files chapter).

:::
