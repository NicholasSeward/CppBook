# A Simple Engine and Delta Time

Scattering `SDL_PollEvent`, update logic, and draw code across `main` gets messy. A small **Engine** class can own the loop pieces:

- Process events
- Update **GameObject** instances using **`deltaTime`**
- Draw everything
- Track frame timing

## `deltaTime` movement

Instead of `x += 4` per frame, use **units per second**:

```
x += speedX * deltaTimeSeconds;
```

Same speed whether the machine runs 60 or 144 FPS.

## Engine with GameObjects

Each object stores **float** position, gets a random nudge in **`update`**, and draws a circle in **`draw`**:

```sdl2
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <vector>
#include <cstdlib>

struct GameObject
{
    float x{0.0f};
    float y{0.0f};

    GameObject(float startX, float startY)
        : x{startX}, y{startY}
    {
    }

    void update(float dt)
    {
        x += (static_cast<float>(std::rand() % 21) - 10.0f) * dt * 8.0f;
        y += (static_cast<float>(std::rand() % 21) - 10.0f) * dt * 8.0f;

        if (x < 20.0f)
        {
            x = 20.0f;
        }
        if (x > 620.0f)
        {
            x = 620.0f;
        }
        if (y < 20.0f)
        {
            y = 20.0f;
        }
        if (y > 460.0f)
        {
            y = 460.0f;
        }
    }

    void draw(SDL_Renderer* renderer) const
    {
        filledCircleRGBA(
            renderer,
            static_cast<Sint16>(x),
            static_cast<Sint16>(y),
            14,
            100 + static_cast<Uint8>(x) % 155,
            180,
            255,
            255);
    }
};

class Engine
{
public:
    bool init()
    {
        if (SDL_Init(SDL_INIT_VIDEO) != 0)
        {
            return false;
        }

        window = SDL_CreateWindow(
            "Engine",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            640,
            480,
            SDL_WINDOW_SHOWN);

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        lastTicks = SDL_GetTicks();

        for (int i{0}; i < 12; ++i)
        {
            objects.emplace_back(
                static_cast<float>(80 + (i * 47) % 500),
                static_cast<float>(60 + (i * 31) % 360));
        }

        return renderer != nullptr;
    }

    void step()
    {
        Uint32 now{SDL_GetTicks()};
        deltaTime = static_cast<float>(now - lastTicks) / 1000.0f;
        lastTicks = now;

        SDL_Event event{};
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = false;
            }
        }

        for (GameObject& obj : objects)
        {
            obj.update(deltaTime);
        }

        SDL_SetRenderDrawColor(renderer, 20, 20, 30, 255);
        SDL_RenderClear(renderer);

        for (const GameObject& obj : objects)
        {
            obj.draw(renderer);
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    bool running{true};
    float deltaTime{0.0f};

private:
    SDL_Window* window{nullptr};
    SDL_Renderer* renderer{nullptr};
    Uint32 lastTicks{0};
    std::vector<GameObject> objects;
};

int main(int, char**)
{
    Engine engine{};
    if (!engine.init())
    {
        return 1;
    }

    while (engine.running)
    {
        engine.step();
    }

    return 0;
}
```

Circles drift randomly each frame — **`update`** uses floats; **`draw`** casts to integers for gfx calls.

> PREFERENCE: One **`engine.step()`** per frame keeps `main` readable. Grow the engine only as far as the project needs.

## Try it now

### Exercise 1: Why delta time?

Prompt: At 30 FPS vs 120 FPS, why is `x += 100 * deltaTime` better than `x += 2`?

:::details Answer

**`100 * deltaTime`** moves ~100 units per **second** regardless of frame count. **`x += 2`** moves faster when more frames run per second.

:::

### Exercise 2: Who draws?

Prompt: In the engine above, who calls `SDL_RenderPresent`?

:::details Answer

**`Engine::step()`** — once per frame after every object draws.

:::
