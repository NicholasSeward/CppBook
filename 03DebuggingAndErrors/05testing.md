# Testing

**Testing** means running code and checking that results match expectations.

A program that compiles is not finished. You still need evidence that it does the right thing.

## Why testing is hard

Real programs have branches, loops, and input. Different inputs can follow different paths.

You rarely prove a program has **zero** bugs. You aim to find most problems and set up **regression tests** so fixed bugs stay fixed.

### Combinatorial explosion

Suppose a function takes one `int`. In principle you could test billions of values. That is already impractical.

Two `int` parameters mean on the order of 10^19 combinations. No computer will exhaust that space.

The practical approach:

- Test **representative** values (zero, negative, large, boundary cases).
- Test **small pieces** (functions) before wiring everything together.
- Automate tests so you can rerun them cheaply after every change.

This course starts with testing **functions**. Later chapters test **classes** and larger systems.

## Informal testing

The simplest test is extra code in `main` (or a helper) that prints whether a result looks right.

```cpp
#include <iostream>

int add(int a, int b)
{
    return a + b;
}

int main()
{
    std::cout << "add(2, 3) = " << add(2, 3) << '\n';

    if (add(2, 3) == 5)
    {
        std::cout << "add test passed\n";
    }
    else
    {
        std::cout << "add test FAILED\n";
    }

    return 0;
}
```

You can wrap checks in a function that returns `true` or `false`:

```cpp
#include <iostream>

int add(int a, int b)
{
    return a + b;
}

bool testAdd()
{
    return add(2, 3) == 5 && add(-1, 1) == 0;
}

int main()
{
    if (testAdd())
    {
        std::cout << "All add tests passed\n";
    }
    else
    {
        std::cout << "Some add tests failed\n";
    }

    return 0;
}
```

That is the seed of what test frameworks do, with better reporting and organization.

## Test frameworks

Many C++ **test frameworks** exist. Common ones:

| Framework | Notes |
|-----------|--------|
| [doctest](https://github.com/doctest/doctest) | Header-only, fast compile, simple syntax |
| [Catch2](https://github.com/catchorg/Catch2) | Popular, expressive macros |
| [Google Test](https://github.com/google/googletest) | Widely used in industry |

This book uses **doctest** for examples because it is easy to drop into a single file or small project. See [Doctest](06doctest.md) for setup, `CHECK`, exception tests, and how to compile a separate test binary.

## Integration testing

**Unit tests** focus on one function or small module in isolation.

**Integration tests** check that pieces work **together**: reading a file, parsing it, and storing results in a structure, for example.

Passing every unit test does not guarantee the whole program fits. Add a few end-to-end tests for critical workflows.

## Regression workflow

When you find a bug in the wild:

1. **Reproduce** it reliably.
2. **Write a test** that fails but should pass (captures the bug).
3. **Fix** the code.
4. **Run all tests** and confirm the new test and old tests pass.

That failing-then-passing test is a **regression test**. It guards against the same bug coming back.

See [Unit Test Principles](07unit%20test%20principles.md) for what makes a good test case, and [Coverage Metrics](08coverage%20metrics.md) for how much of your code tests actually exercise.

## Try it now

### Exercise 1: Write informal tests in `main`

Prompt: Implement `maxOf` and print whether three manual checks pass or fail.

```cpp
// @file: main.cpp
#include <iostream>

int maxOf(int a, int b)
{
    // TODO: return the larger of a and b
    return a;
}

int main()
{
    // TODO: test maxOf(3, 7), maxOf(4, 4), and maxOf(-1, -5)
    // Print "pass" or "fail" for each.

    return 0;
}
```

### Exercise 2: Move to doctest

Prompt: Continue in [Doctest](06doctest.md) Exercise 1. Same `maxOf` idea, but use `CHECK` in a test case with doctest already set up.
