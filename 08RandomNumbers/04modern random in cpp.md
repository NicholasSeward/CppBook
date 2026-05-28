# Modern Random in C++

Modern C++ random numbers live in the `<random>` header.

The main idea is to separate two jobs:

- The generator produces raw pseudorandom values.
- The distribution turns those values into the range and shape you want.

That separation looks more complex than `rand()` at first, but it gives you much better control.

## A Generator

One common generator is `std::mt19937`. It is an implementation of the Mersenne Twister algorithm.

```cpp
#include <iostream>
#include <random>

int main()
{
    std::mt19937 rng{12345};

    for (int count{0}; count < 5; ++count)
    {
        std::cout << rng() << "\n";
    }

    return 0;
}
```

Calling `rng()` produces the next raw value and advances the generator's internal state.

Run the program more than once. Because the seed is fixed, the output should repeat.

HISTORY: Mersenne Twister is older now, but it is still the strongest general-purpose generator provided by C++17's standard library. For security work, use a security-focused library instead.

## A Distribution

Raw generator values are not usually what you want to print. If you want a die roll, ask for a die roll directly.

```cpp
#include <iostream>
#include <random>

int main()
{
    std::mt19937 rng{12345};
    std::uniform_int_distribution<int> die{1, 6};

    for (int roll{1}; roll <= 10; ++roll)
    {
        std::cout << die(rng) << "\n";
    }

    return 0;
}
```

The distribution is inclusive for integers. `std::uniform_int_distribution<int> die{1, 6};` can produce both `1` and `6`.

## Different Ranges

Once you understand the pattern, changing the range is easy.

```cpp
#include <iostream>
#include <random>

int main()
{
    std::mt19937 rng{12345};
    std::uniform_int_distribution<int> d20{1, 20};

    for (int roll{1}; roll <= 5; ++roll)
    {
        std::cout << "d20 roll: " << d20(rng) << "\n";
    }

    return 0;
}
```

You can make multiple distributions and use them with the same generator.

```cpp
#include <iostream>
#include <random>

int main()
{
    std::mt19937 rng{12345};
    std::uniform_int_distribution<int> coin{0, 1};
    std::uniform_int_distribution<int> die{1, 6};
    std::uniform_int_distribution<int> d20{1, 20};

    std::cout << "coin: " << coin(rng) << "\n";
    std::cout << "die: " << die(rng) << "\n";
    std::cout << "d20: " << d20(rng) << "\n";

    return 0;
}
```

The generator owns the sequence. Each distribution call consumes from that same sequence.

## Real-Valued Random Numbers

For decimal values, use `std::uniform_real_distribution`.

```cpp
#include <iostream>
#include <random>

int main()
{
    std::mt19937 rng{12345};
    std::uniform_real_distribution<double> unit{0.0, 1.0};

    for (int count{0}; count < 5; ++count)
    {
        std::cout << unit(rng) << "\n";
    }

    return 0;
}
```

This is useful when you want a random percentage, a probability check, or a position between two limits.

## Choosing Randomly

Here is a small program that chooses a random direction for a game enemy.

```cpp
#include <iostream>
#include <random>
#include <string>
#include <vector>

int main()
{
    std::vector<std::string> directions{"north", "south", "east", "west"};

    std::mt19937 rng{12345};
    std::uniform_int_distribution<int> index{0, static_cast<int>(directions.size()) - 1};

    std::cout << "The enemy moves " << directions.at(index(rng)) << ".\n";

    return 0;
}
```

The range uses the valid vector indexes: `0` through `directions.size() - 1`.

NOTE: The cast is there because `directions.size()` returns an unsigned size type, while this distribution is using `int`. In larger programs, be thoughtful about signed and unsigned values.

Try changing the seed and the list of directions. Then add a fifth direction and make sure the distribution still covers the whole vector.
