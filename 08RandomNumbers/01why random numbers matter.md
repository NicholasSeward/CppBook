# Why Random Numbers Matter

So far, most of our programs have been deterministic. If you give the program the same input, you get the same output every time.

That is usually a good thing. If a grade calculator gives a different answer every time you run it, something is wrong.

Sometimes, though, we want a program to feel less predictable. A little randomness can make software more useful, more realistic, or more fun.

## Where Randomness Shows Up

Randomness is useful in many kinds of programs:

- A game enemy chooses between several possible movements.
- A dungeon generator builds a different map each time.
- A card game shuffles a deck.
- A simulation estimates what might happen over many trials.
- A test program generates many possible inputs.
- A security program creates values that attackers should not be able to guess.

A simulation that uses randomness is often called a Monte Carlo simulation. The name sounds fancy, but the basic idea is simple: run a random experiment many times and use the results to estimate something.

Here is a tiny example. We can estimate the chance of rolling a 6 on a die by rolling many fake dice and counting how often 6 appears.

```cpp
#include <iostream>
#include <random>

int main()
{
    std::mt19937 rng{12345};
    std::uniform_int_distribution<int> die{1, 6};

    int sixes{0};
    int rolls{1000};

    for (int count{0}; count < rolls; ++count)
    {
        int value{die(rng)};

        if (value == 6)
        {
            ++sixes;
        }
    }

    std::cout << "Rolled a 6 " << sixes << " times out of " << rolls << ".\n";
    return 0;
}
```

The answer will not be exactly `1 / 6` every time. Random experiments wiggle around. If you increase `rolls`, the result should usually get closer to what you expect.

## Random Does Not Mean Uncontrolled

Randomness does not mean a program is out of control. You still decide:

- what range of values can appear
- how often each value should appear
- when the next value is generated
- whether the sequence should repeat for testing

That last point matters. During development, repeatability is often helpful. If a bug happens only on one random run, you want a way to make that same run happen again.

NOTE: Randomness is not one topic. There is game randomness, simulation randomness, testing randomness, and security randomness. They do not all have the same requirements.

## A Simple Range Example

The most common beginner use case is choosing an integer in a range.

```cpp
#include <iostream>
#include <random>

int main()
{
    std::mt19937 rng{54321};
    std::uniform_int_distribution<int> die{1, 6};

    std::cout << "Rolling five dice:\n";

    for (int roll{1}; roll <= 5; ++roll)
    {
        std::cout << die(rng) << "\n";
    }

    return 0;
}
```

The distribution object controls the range. In this example, `die` can produce `1`, `2`, `3`, `4`, `5`, or `6`.

The generator object, `rng`, stores the current state of the random sequence.
