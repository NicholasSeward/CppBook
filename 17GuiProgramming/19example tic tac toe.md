# Example: Tic-Tac-Toe

This demo combines ideas from earlier sections: **mouse hit tests**, a **board class** with **`draw(SDL_Renderer*)`**, and a full **clear → draw → present** loop each frame.

**Click** an empty cell to place X or O. **R** resets after a win or draw.

```sdl2
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <array>
#include <string>

class TicTacToeBoard
{
public:
    static constexpr int kCellSize{120};
    static constexpr int kOriginX{80};
    static constexpr int kOriginY{60};

    void reset()
    {
        cells.fill(0);
        currentPlayer = 1;
        winner = 0;
    }

    bool isRunning() const
    {
        return winner == 0 && !boardFull();
    }

    int current() const
    {
        return currentPlayer;
    }

    int winState() const
    {
        return winner;
    }

    void tryClick(int px, int py)
    {
        if (winner != 0)
        {
            return;
        }

        const int col = (px - kOriginX) / kCellSize;
        const int row = (py - kOriginY) / kCellSize;
        if (row < 0 || row > 2 || col < 0 || col > 2)
        {
            return;
        }

        const int index = row * 3 + col;
        if (cells[index] != 0)
        {
            return;
        }

        cells[index] = currentPlayer;
        winner = checkWinner();
        if (winner == 0 && !boardFull())
        {
            currentPlayer = currentPlayer == 1 ? 2 : 1;
        }
    }

    void draw(SDL_Renderer* renderer) const
    {
        for (int i{1}; i < 3; ++i)
        {
            const int x = kOriginX + i * kCellSize;
            lineRGBA(renderer, x, kOriginY, x, kOriginY + 3 * kCellSize, 220, 220, 230, 255);
            const int y = kOriginY + i * kCellSize;
            lineRGBA(renderer, kOriginX, y, kOriginX + 3 * kCellSize, y, 220, 220, 230, 255);
        }

        for (int row{0}; row < 3; ++row)
        {
            for (int col{0}; col < 3; ++col)
            {
                const int cx = kOriginX + col * kCellSize + kCellSize / 2;
                const int cy = kOriginY + row * kCellSize + kCellSize / 2;
                const int piece = cells[row * 3 + col];

                if (piece == 1)
                {
                    lineRGBA(renderer, cx - 30, cy - 30, cx + 30, cy + 30, 255, 90, 90, 255);
                    lineRGBA(renderer, cx + 30, cy - 30, cx - 30, cy + 30, 255, 90, 90, 255);
                }
                else if (piece == 2)
                {
                    circleRGBA(renderer, cx, cy, 34, 90, 180, 255, 255);
                }
            }
        }
    }

private:
    std::array<int, 9> cells{};
    int currentPlayer{1};
    int winner{0};

    bool boardFull() const
    {
        for (int c : cells)
        {
            if (c == 0)
            {
                return false;
            }
        }
        return true;
    }

    int checkWinner() const
    {
        static constexpr int lines[8][3] = {
            {0, 1, 2}, {3, 4, 5}, {6, 7, 8},
            {0, 3, 6}, {1, 4, 7}, {2, 5, 8},
            {0, 4, 8}, {2, 4, 6}};

        for (const auto& line : lines)
        {
            const int a = cells[line[0]];
            if (a != 0 && a == cells[line[1]] && a == cells[line[2]])
            {
                return a;
            }
        }
        return 0;
    }
};

int main(int, char**)
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow(
        "Tic-Tac-Toe",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        640,
        480,
        SDL_WINDOW_SHOWN);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    TicTacToeBoard board{};
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
            if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
            {
                board.tryClick(event.button.x, event.button.y);
            }
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_r)
            {
                board.reset();
            }
        }

        SDL_SetRenderDrawColor(renderer, 28, 30, 40, 255);
        SDL_RenderClear(renderer);

        board.draw(renderer);

        std::string status;
        if (board.winState() == 1)
        {
            status = "X wins! Press R";
        }
        else if (board.winState() == 2)
        {
            status = "O wins! Press R";
        }
        else if (!board.isRunning())
        {
            status = "Draw! Press R";
        }
        else
        {
            status = board.current() == 1 ? "Turn: X" : "Turn: O";
        }
        stringRGBA(renderer, 20, 430, status.c_str(), 230, 230, 240, 255);

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    return 0;
}
```

**New ideas highlighted:** `TicTacToeBoard::draw(renderer)` owns all grid drawing; `main` only clears, delegates, and presents. Cell picking uses integer division on click coordinates — same **`pointInRect`** idea as the button demo, on a grid.

Next: [Example: Simple Platformer](20example%20simple%20platformer.md).

## Try it now

### Exercise 1: Separation

Prompt: What would you move into `TicTacToeBoard` if you added AI for a one-player mode?

:::details Answer

**Move selection** and **board evaluation** — keep **`draw`** and **`tryClick`** on the board; AI picks a cell index the same way a human click would.

:::
