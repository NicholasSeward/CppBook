# `rand` and `srand`

Before using modern C++ random tools, it helps to recognize the old C-style tools: `rand` and `srand`.

You will still see them in old examples, quick demos, and beginner code online.

PREFERENCE: Do not use `rand` and `srand` for new C++ programs. Learn to recognize them, then prefer `<random>`. However, I do use them from time to time.

## Using `rand`

The function `rand()` returns a pseudorandom integer.

It comes from `<cstdlib>`.

```cpp
#include <cstdlib>
#include <iostream>

int main()
{
    for (int count{0}; count < 5; ++count)
    {
        std::cout << std::rand() << "\n";
    }

    return 0;
}
```

Run this program more than once. On many systems, you will see the same numbers each run because the generator starts from the same default seed.

## Rolling a Die With `rand`

To force `rand()` into a range, old code often uses the remainder operator.

```cpp
#include <cstdlib>
#include <iostream>

int main()
{
    for (int roll{1}; roll <= 10; ++roll)
    {
        int die{std::rand() % 6 + 1};
        std::cout << die << "\n";
    }

    return 0;
}
```

This gives numbers from `1` through `6`, but it has weaknesses:

- The quality of `rand()` depends on the implementation.
- The range of possible values may be smaller than you expect.
- Using `%` can make some values slightly more likely than others.
- The code makes it easy to forget about better tools later.

For a toy program, this may look fine. The danger is using it in a program where the randomness matters.

## Seeding With `srand`

The function `srand()` sets the seed used by `rand()`.

```cpp
#include <cstdlib>
#include <iostream>

int main()
{
    std::srand(12345);

    for (int roll{1}; roll <= 10; ++roll)
    {
        int die{std::rand() % 6 + 1};
        std::cout << die << "\n";
    }

    return 0;
}
```

The same seed gives the same sequence.

Change `12345` to another number and run the program again. The sequence should change.

## The Clock Seed Pattern

You may see code that seeds `rand()` with the current time:

```cpp
#include <cstdlib>
#include <ctime>
#include <iostream>

int main()
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    for (int roll{1}; roll <= 10; ++roll)
    {
        int die{std::rand() % 6 + 1};
        std::cout << die << "\n";
    }

    return 0;
}
```

This makes the output change from one run to another, but the seed is still guessable. If someone knows roughly when the program started, they can try likely seed values.

That does not matter for a classroom die roller. It matters a lot for a casino, password reset token, loot box, or money-related program.

NOTE: A 32-bit seed has about 4 billion possible values. That sounds large to a human, but it is not large to a computer trying seeds quickly.

## Why Move On

The old functions are simple, but modern C++ gives us better tools:

- generator objects that hold their own state
- distribution objects that handle ranges cleanly
- better generator algorithms
- clearer code that says what range you want
