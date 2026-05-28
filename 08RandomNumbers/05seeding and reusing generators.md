# Seeding and Reusing Generators

A seed starts a generator's sequence. After that, the generator's state changes every time you ask for another value.

That means you usually seed once, then reuse the generator.

## Fixed Seeds

A fixed seed gives repeatable output.

```cpp
#include <iostream>
#include <random>

int main()
{
    std::mt19937 rng{12345};
    std::uniform_int_distribution<int> die{1, 6};

    for (int roll{1}; roll <= 5; ++roll)
    {
        std::cout << die(rng) << "\n";
    }

    return 0;
}
```

Repeatable output is good for examples, tests, and debugging.

## `std::random_device`

If you want a different sequence each run, seed the generator with `std::random_device`.

```cpp
#include <iostream>
#include <random>

int main()
{
    std::random_device rd;
    std::mt19937 rng{rd()};
    std::uniform_int_distribution<int> die{1, 6};

    for (int roll{1}; roll <= 5; ++roll)
    {
        std::cout << die(rng) << "\n";
    }

    return 0;
}
```

`std::random_device` asks the operating system for nondeterministic random data if it can provide it.

On many systems, the operating system gathers entropy from real-world or hardware-related sources, such as timing events, hardware random instructions, and other system activity. It mixes those sources into a pool that can be used for seeding.

NOTE: The exact behavior of `std::random_device` depends on the implementation. For normal classroom programs it is fine. For serious security work, use security-specific tools.

## Do Not Seed Every Time

This program works, but it has a bad habit: it creates and seeds a new generator every time the function is called.

```cpp
#include <iostream>
#include <random>

int rollDie()
{
    std::random_device rd;
    std::mt19937 rng{rd()};
    std::uniform_int_distribution<int> die{1, 6};

    return die(rng);
}

int main()
{
    for (int roll{1}; roll <= 5; ++roll)
    {
        std::cout << rollDie() << "\n";
    }

    return 0;
}
```

This is inefficient because setup happens again and again.

More importantly, repeated seeding can cause confusing patterns if the seed source has low resolution or limited data. Seed once. Reuse the generator.

## A Small Reusable Helper

One clean approach is to write a helper that owns the generator and distribution.

```cpp
// @file: main.cpp
#include <iostream>
#include "random_utils.h"

int main()
{
    for (int roll{1}; roll <= 5; ++roll)
    {
        std::cout << random_utils::getInt(1, 6) << "\n";
    }

    return 0;
}

// @file: random_utils.h
#pragma once

#include <random>

namespace random_utils
{
    inline std::mt19937 rng{std::random_device{}()};

    inline int getInt(int min, int max)
    {
        std::uniform_int_distribution<int> dist{min, max};
        return dist(rng);
    }
}
```

The `inline` variable `rng` inside the `random_utils` namespace is initialized once, then reused on later calls.

This design keeps the generator out of `main`, avoids exposing a global variable to every file, and provides a simple, reusable function for generating random numbers.