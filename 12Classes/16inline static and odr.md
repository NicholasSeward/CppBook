# Static and Inline Members

Some class members belong to the **type as a whole**, not to one object. They are **shared** by every instance (or callable without an instance at all).

Two keywords cover most of that in headers:

| Keyword | On a class member |
|---------|-------------------|
| **`static`** | Shared at class level (one function or one variable for the whole class) |
| **`inline`** | Lets a **static data member** be **assigned in the `.h` file** (C++17) |

## Static member functions

A **`static`** member function is tied to the **class**, not to one object's `this`. Call it with **`ClassName::functionName`**.

```cpp
#include <iostream>

class MathUtil
{
public:
    static int max(int a, int b)
    {
        return a > b ? a : b;
    }
};

int main()
{
    std::cout << MathUtil::max(3, 7) << '\n';
    return 0;
}
```

It cannot use non-`static` data members directly. If it does not need any class data, it could be a plain free function instead. **`static`** is still useful when the helper should live under the type name (`MathUtil::max`).

## Static data members (shared)

A **`static`** data member is **one variable shared by all objects** of the class, not a separate copy per object.

Without **`inline`**, you **declare** it in the header and **define** it once in a `.cpp` file:

```cpp
// Player.h
class Player
{
public:
    static int liveCount;
};
```

```cpp
// Player.cpp
int Player::liveCount = 0;
```

## Inline static data members

**`static inline`** data is still **shared**, but you may **assign the value in the header**:

```cpp
#include <iostream>

class Player
{
public:
    static inline int liveCount = 0;

    Player()
    {
        ++liveCount;
    }
};

int main()
{
    Player a{};
    Player b{};
    std::cout << Player::liveCount << '\n';
    return 0;
}
```

**`static`** = one counter for the whole class. **`inline`** = `= 0` can live in the `.h` file without a separate line in a `.cpp` file.

Putting both ideas in one class:

```cpp
#include <iostream>

class GameStats
{
public:
    static inline int gamesPlayed = 0;

    static void recordGame()
    {
        ++gamesPlayed;
    }
};

int main()
{
    GameStats::recordGame();
    GameStats::recordGame();
    std::cout << GameStats::gamesPlayed << '\n';
    return 0;
}
```

`gamesPlayed` is shared data with an initializer in the header. `recordGame` is a shared function that updates it. No `GameStats` object required.

## Try it now

### Exercise 1: Call static helper

Prompt: Add `static bool isPositive(int n)` to `MathUtil` and print the result of `MathUtil::isPositive(-1)` and `MathUtil::isPositive(5)`.

```cpp
#include <iostream>

class MathUtil
{
public:
    // TODO: static bool isPositive(int n)
};

int main()
{
    // TODO: print two results
    return 0;
}
```

Expected: `0` then `1` (or `false` / `true` with `std::boolalpha`)

:::details Hint

`static` member functions use `ClassName::` to call. Return `n > 0` from `isPositive`.

:::

:::details Solution

**Reasoning:** `isPositive` is a class-level helper. Callers write `MathUtil::isPositive(5)` without creating a `MathUtil` object.

```cpp
static bool isPositive(int n)
{
    return n > 0;
}
```

In `main`:

```cpp
std::cout << MathUtil::isPositive(-1) << ' ' << MathUtil::isPositive(5) << '\n';
```

:::
