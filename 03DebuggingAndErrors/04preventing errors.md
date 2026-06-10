# Preventing Errors

Debugging fixes mistakes after they exist. Prevention reduces how many mistakes you make in the first place.

You cannot prevent every bug. You can lower the rate and catch problems earlier when they do appear.

## Habits that help

1. **Follow common patterns** you have seen in course examples (clear names, braces on `if`, small functions).
2. **Do not program while exhausted.** Typos and wrong operators show up more when you are tired.
3. **Learn common pitfalls** (integer division, `=` vs `==`, off-by-one loops). Many chapters in this book call these out on purpose.
4. **Keep functions short.** One job per function is easier to read and test.
5. **Use library code** (`std::vector`, `std::string`, algorithms) instead of reinventing fragile versions.
6. **Comment complex logic** when you cannot simplify it further.
7. **Prefer readability over micro-optimizations** until measurement says speed matters.
8. **Refactor and clean as you go.** Small cleanups are cheaper than one giant rewrite.

## Defensive programming

**Defensive programming** assumes things *will* go wrong: bad input, missing files, empty containers.

Goals:

- **Find errors fast and early** (close to the cause).
- **Test** assumptions before relying on them.
- **Fail clearly** rather than silently continuing with garbage data.

```cpp
#include <iostream>

bool divide(int numerator, int denominator, int& outQuotient)
{
    if (denominator == 0)
    {
        std::cout << "Error: division by zero\n";
        return false;
    }

    outQuotient = numerator / denominator;
    return true;
}

int main()
{
    int result{};

    if (divide(10, 2, result))
    {
        std::cout << "Result: " << result << '\n';
    }

    if (!divide(10, 0, result))
    {
        std::cout << "Could not divide.\n";
    }

    return 0;
}
```

The `cout` messages are informal checks. In later chapters you will use return values, exceptions, and test frameworks more systematically.

This simple "call the function and check the result" pattern is a stepping stone toward **unit tests** ([Testing](05testing.md)).

## Assertions (preview)

For conditions that **must** be true if your code is correct (programmer mistakes, not bad user input), C++ provides `assert`. A failed `assert` stops the program with a message.

```cpp
#include <cassert>
#include <cmath>
#include <iostream>

double dist(double x1, double y1, double x2, double y2)
{
    double dx{x2 - x1};
    double dy{y2 - y1};
    double result{std::sqrt(dx * dx + dy * dy)};

    assert(result > 0.0 && "distance must be positive for distinct points");

    return result;
}

int main()
{
    std::cout << dist(0.0, 0.0, 3.0, 4.0) << '\n';
    return 0;
}
```

`assert` is for bugs in *your* logic, not for "user typed letters instead of a number." [Assert and `static_assert`](12assert%20and%20static%20assert.md) goes deeper.

## Static analysis

**Static analysis** tools read your source without running the full program and flag likely problems: unused variables, suspicious conversions, memory issues, style violations.

| Tool | Typical use |
|------|-------------|
| Compiler warnings (`-Wall -Wextra`) | First line of defense; enable and heed warnings |
| [clang-tidy](https://clang.llvm.org/extra/clang-tidy/) | Fixes and checks via LLVM tooling |
| [Cppcheck](https://cppcheck.sourceforge.io/) | Lightweight open-source checker |
| IDE built-in analysis | Squiggles and hints while you type |

Turn warnings on and treat them seriously. A warning is often a future bug.

> PREFERENCE: Fix new warnings before adding more code. Warning noise hides real problems.

## Try it now

### Exercise 1: Return `false` when input is invalid

Prompt: Finish `setHealth` so it returns `false` when `health` is outside 0..100. Print different messages from `main` for success and failure.

```cpp
// @file: main.cpp
#include <iostream>

bool setHealth(int health, int& outHealth)
{
    // TODO: return false when health is < 0 or > 100
    // TODO: otherwise set outHealth and return true
    return false;
}

int main()
{
    int health{};

    if (setHealth(75, health))
    {
        std::cout << "Health: " << health << '\n';
    }
    else
    {
        std::cout << "Could not set health.\n";
    }

    if (!setHealth(150, health))
    {
        std::cout << "Correctly rejected out-of-range health.\n";
    }

    return 0;
}
```

### Exercise 2: Guard before you compute

Prompt: Finish `averageThree` so it returns `false` when any score is outside 0..100. Test one valid and one invalid set from `main`.

```cpp
// @file: main.cpp
#include <iostream>

bool averageThree(int a, int b, int c, double& outAverage)
{
    // TODO: return false if any score is < 0 or > 100

    outAverage = (a + b + c) / 3.0;
    return true;
}

int main()
{
    double avg{};

    if (averageThree(80, 90, 70, avg))
    {
        std::cout << "Average: " << avg << '\n';
    }

    if (!averageThree(80, 150, 70, avg))
    {
        std::cout << "Invalid score rejected.\n";
    }

    return 0;
}
```
