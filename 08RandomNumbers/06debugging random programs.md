# Debugging Random Programs

Randomness can make bugs harder to chase.

If a program behaves differently every run, a bug might appear once and then disappear. That does not mean the bug is gone. It means you lost the exact situation that revealed it.

The goal is to make random behavior reproducible when you need to debug it.

## Print the Seed

If you seed from `std::random_device`, save and print the seed.

```cpp
#include <iostream>
#include <random>

int main()
{
    std::random_device rd;
    unsigned int seed{rd()};

    std::mt19937 rng{seed};
    std::uniform_int_distribution<int> damage{1, 10};

    std::cout << "Seed: " << seed << "\n";

    int playerHealth{20};

    for (int hit{1}; hit <= 5; ++hit)
    {
        playerHealth -= damage(rng);
        std::cout << "Health: " << playerHealth << "\n";
    }

    return 0;
}
```

If a weird run happens, copy the printed seed into the program temporarily.

```cpp
#include <iostream>
#include <random>

int main()
{
    unsigned int seed{123456789};

    std::mt19937 rng{seed};
    std::uniform_int_distribution<int> damage{1, 10};

    std::cout << "Seed: " << seed << "\n";

    int playerHealth{20};

    for (int hit{1}; hit <= 5; ++hit)
    {
        playerHealth -= damage(rng);
        std::cout << "Health: " << playerHealth << "\n";
    }

    return 0;
}
```

Now that run is repeatable.

## A Sometimes Bug

Here is a tiny program with a bug that depends on random values.

```cpp
#include <iostream>
#include <random>
#include <vector>

int main()
{
    unsigned int seed{2026};

    std::mt19937 rng{seed};
    std::uniform_int_distribution<int> index{0, 4};

    std::vector<int> scores{10, 20, 30, 40};

    std::cout << "Seed: " << seed << "\n";

    for (int count{0}; count < 10; ++count)
    {
        int chosen{index(rng)};
        std::cout << scores.at(chosen) << "\n";
    }

    return 0;
}
```

The vector has valid indexes `0`, `1`, `2`, and `3`.

The distribution can produce `4`.

Because the code uses `scores.at(chosen)`, C++ will throw an exception when `chosen` is out of range.

The fix is to make the random range match the vector.

```cpp
#include <iostream>
#include <random>
#include <vector>

int main()
{
    unsigned int seed{2026};

    std::mt19937 rng{seed};

    std::vector<int> scores{10, 20, 30, 40};
    std::uniform_int_distribution<int> index{0, static_cast<int>(scores.size()) - 1};

    std::cout << "Seed: " << seed << "\n";

    for (int count{0}; count < 10; ++count)
    {
        int chosen{index(rng)};
        std::cout << scores.at(chosen) << "\n";
    }

    return 0;
}
```

The random range now grows or shrinks with the vector.

## Watch for Hidden State Changes

Every time you call a distribution with a generator, the generator advances.

That means this code:

```
int first{die(rng)};
int second{die(rng)};
```

does not produce the same value twice. It consumes two values from the sequence.

This can surprise you when debugging. Adding an extra random call for logging or testing can change every later random result.

## Common Random Bugs

Watch for these:

- The generator is seeded inside a loop.
- The distribution range does not match the container indexes.
- A fixed seed is accidentally left in code that should vary.
- A random seed is used in a test that should be repeatable.
- A security-sensitive program uses a general-purpose PRNG.

AI: LLMs were trained on lots of existing C++ code, most of it written before modern style was common. The code you get will usually be correct and usable, but it may be subtly wrong: you’ll see examples that use `rand()`, `%`, fixed seeds, or repeated seeding inside a function.

