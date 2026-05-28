# Pseudorandom Generators

Computers are very good at following instructions. That makes true randomness awkward.

Most random numbers in normal programs are not truly random. They are pseudorandom. A pseudorandom number generator, or PRNG, uses a deterministic rule to produce values that look random enough for the job.

The important word is deterministic. If the generator starts from the same state, it produces the same sequence.

## Seeds and State

A PRNG has state. The state is the generator's current internal value.

A seed is the starting value used to initialize that state.

If two generators use the same seed and the same algorithm, they produce the same sequence.

That may sound like a flaw, but it is often useful:

- You can reproduce a bug.
- You can replay the same random level.
- You can write tests that use random-looking data but still behave the same every run.

## A Tiny Generator

Here is a simple linear congruential generator, often shortened to LCG.

This is not a recommendation. It is just small enough to understand.

```cpp
#include <iostream>

int main()
{
    unsigned int state{7};

    for (int count{0}; count < 10; ++count)
    {
        state = (state * 5 + 1) % 16;
        std::cout << state << "\n";
    }

    return 0;
}
```

Each new state comes from the old state:

```
state = (state * 5 + 1) % 16;
```

That is the whole trick. Multiply, add, take the remainder, repeat.

Run the program a few times. You should see the same sequence every time. Then change the seed from `7` to another number and run it again.

NOTE: Do not use this LCG in real programs. It is tiny and predictable on purpose, so that the idea is visible.

## Turning State Into a Die Roll

A raw generator state is not usually what we want. Most of the time, we want a value in a specific range.

For a die roll, we want values from `1` through `6`.

```cpp
#include <iostream>

int main()
{
    unsigned int state{7};

    for (int roll{1}; roll <= 10; ++roll)
    {
        state = (state * 5 + 1) % 16;
        int die{static_cast<int>(state % 6) + 1};

        std::cout << die << "\n";
    }

    return 0;
}
```

The expression `state % 6` gives a value from `0` through `5`. Adding `1` shifts that to `1` through `6`.

This is easy, but it is not always statistically clean. Some ranges can make certain answers slightly more likely than others. Modern C++ distributions handle that problem for us.

## What Makes a Good PRNG

A useful PRNG usually has several qualities:

- It is fast enough for the program.
- It has a long period.
- Its values are well distributed.
- It has enough internal state.
- It is hard to predict for the intended use.

The period is how long the sequence can go before it repeats. A tiny generator with only 16 possible states cannot have a long period. A modern generator can have an enormous period.

Uniformity means the values are spread out well. If a die roller gives `6` half the time, something is wrong.

Predictability depends on the purpose. Predictable randomness is fine for debugging a game level. It is not fine for cryptography, gambling, passwords, or anything involving money.

PREFERENCE: Use the tiny generator only as a teaching model. For actual C++ programs, use `<random>`.

## True Randomness

True randomness has to come from outside the deterministic rules of the program. A system might sample things like hardware random number instructions, device timing, interrupt timing, or operating system entropy pools.

In C++, `std::random_device` is the standard library tool that asks the implementation for nondeterministic random data if it can.

We usually use that kind of value to seed a PRNG. The PRNG then produces the long sequence quickly.

Try changing the LCG numbers in this chapter. What happens if you change `% 16` to `% 8`? What happens if the seed is `0`?
