# Unit Test Principles

A unit test checks one small piece of code, usually a single function, in isolation.

Frameworks like [doctest](06doctest.md) make tests easy to run. Good tests still need thought about **what** to check.

## Test one thing

Each test case should have a clear purpose. When it fails, you should know which behavior broke.

Prefer several focused cases over one giant case that checks everything at once.

```cpp
// @file: doctest/doctest.h from:https://raw.githubusercontent.com/doctest/doctest/refs/heads/master/doctest/doctest.h hidden
// @file: main.cpp
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

bool isPassing(int score)
{
    return score >= 60;
}

TEST_CASE("passing score at boundary")
{
    CHECK(isPassing(60));
}

TEST_CASE("failing score just below boundary")
{
    CHECK(!isPassing(59));
}
```

If `isPassing(60)` breaks, the case name tells you it was about the boundary, not some unrelated rule.

That does not mean only one `CHECK` per file. It means one **idea** per `TEST_CASE`: boundary pass, boundary fail, negative input, and so on.

> PREFERENCE: Name `TEST_CASE` strings like short bug reports: `"empty vector returns zero"`, not `"test1"`.

## Enough tests for good coverage

You cannot test every input. You also should not ship a function with zero tests.

Aim for **enough** tests that:

- every branch you care about runs at least once
- typical use works
- known risky spots have explicit cases

For `int clamp(int value, int minValue, int maxValue)` that keeps a value in range, representative tests might include:

- value already inside the range (unchanged)
- value below min (clamped up)
- value above max (clamped down)
- value exactly equal to min or max (boundaries)

You do not need every integer from `min` to `max`. You need categories that exercise different paths.

See [Coverage Metrics](08coverage%20metrics.md) for statement, branch, and loop coverage. Coverage tools show gaps; judgment picks which gaps matter.

## Edge cases

An **edge case** sits at the boundary of valid input or behavior.

Common edges for numeric code:

- zero
- one
- negative vs positive
- minimum and maximum representable values (when relevant)

```cpp
// @file: doctest/doctest.h from:https://raw.githubusercontent.com/doctest/doctest/refs/heads/master/doctest/doctest.h hidden
// @file: main.cpp
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

int factorial(int n)
{
    int product{1};

    for (int i{2}; i <= n; ++i)
    {
        product *= i;
    }

    return product;
}

TEST_CASE("factorial of zero")
{
    CHECK(factorial(0) == 1);
}

TEST_CASE("factorial of one")
{
    CHECK(factorial(1) == 1);
}

TEST_CASE("factorial of small positive")
{
    CHECK(factorial(5) == 120);
}
```

Empty containers, first element, last element, and "exactly at the limit" are edge cases for loops and collections.

## Corner cases

A **corner case** is where two or more edge conditions meet. They are easy to miss because each rule alone looks fine.

Examples:

- divide when the numerator is also zero
- format a string that is empty **and** the only field on the line
- sort a vector of size 0 or 1

When you fix a bug from real use, add a test that would have caught it. That often lands in corner-case territory.

## Arrange, act, assert

A readable test has three phases:

1. **Arrange** set up inputs and state.
2. **Act** call the function under test.
3. **Assert** check the outcome with `CHECK` or `REQUIRE`.

```cpp
// @file: doctest/doctest.h from:https://raw.githubusercontent.com/doctest/doctest/refs/heads/master/doctest/doctest.h hidden
// @file: main.cpp
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"
#include <string>

std::string greet(const std::string& name)
{
    return "Hello, " + name;
}

TEST_CASE("greet includes name")
{
    const std::string name{"Ada"};           // arrange

    const std::string message{greet(name)};  // act

    CHECK(message == "Hello, Ada");          // assert
}
```

Keeping that order makes tests scannable in code review.

## What not to unit test

Unit tests are a poor fit for:

- entire `main` flows (use a small manual or integration test instead)
- code that only prints with no return value (refactor to return a string or status first)
- timing, threading, or hardware unless you isolate them

If something is hard to test, that is often a hint to split responsibilities.

## Regression tests

When you find a bug:

1. Write a test that fails with the current code.
2. Fix the code.
3. Keep the test forever.

That test documents the bug and stops it from coming back. The best unit tests are both specification and safety net.

## Summary

| Principle | Practice |
|-----------|----------|
| One thing | One clear behavior per `TEST_CASE` |
| Enough coverage | Exercise each branch and category that matters |
| Edge cases | Boundaries, zero, empty, min, max |
| Corner cases | Combinations of edges; add when bugs appear |
| Thin `main` | Test functions in `.cpp` files without `main` |

## Try it now

### Exercise 1: One idea per `TEST_CASE`

Prompt: `isTeen` returns true for ages 13 through 19 inclusive. Add two separate `TEST_CASE` blocks (one for a passing teen age, one for a failing age) with `CHECK` lines.

```cpp
// @file: doctest/doctest.h from:https://raw.githubusercontent.com/doctest/doctest/refs/heads/master/doctest/doctest.h hidden
// @file: main.cpp
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

bool isTeen(int age)
{
    return age >= 13 && age <= 19;
}

// TODO: TEST_CASE for a teen age that should pass, e.g. 15
// TODO: TEST_CASE for an age that should fail, e.g. 12
```

### Exercise 2: Edge and boundary tests for `clamp`

Prompt: Finish `clamp`, then add `TEST_CASE` blocks that cover: value inside range, below min, above max, and exactly on a boundary.

```cpp
// @file: doctest/doctest.h from:https://raw.githubusercontent.com/doctest/doctest/refs/heads/master/doctest/doctest.h hidden
// @file: main.cpp
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

int clamp(int value, int minValue, int maxValue)
{
    if (value < minValue)
    {
        return minValue;
    }

    if (value > maxValue)
    {
        return maxValue;
    }

    return value;
}

// TODO: TEST_CASE when value is inside range, e.g. clamp(5, 0, 10) == 5
// TODO: TEST_CASE when value is below min
// TODO: TEST_CASE when value is above max
// TODO: TEST_CASE when value equals min or max
```

### Exercise 3: Regression test for a bug

Prompt: `countPositive` should count only values greater than zero. The version below wrongly counts zero too. Add the `CHECK`, run, then fix the function so the test passes.

```cpp
// @file: doctest/doctest.h from:https://raw.githubusercontent.com/doctest/doctest/refs/heads/master/doctest/doctest.h hidden
// @file: main.cpp
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"
#include <vector>

int countPositive(const std::vector<int>& values)
{
    int count{0};

    for (int value : values)
    {
        if (value >= 0)  // bug: zero should not count as positive
        {
            ++count;
        }
    }

    return count;
}

TEST_CASE("countPositive ignores zero and negatives")
{
    const std::vector<int> values{3, 0, -2, 5};

    // TODO: CHECK countPositive(values) == 2
    // After the CHECK fails, fix countPositive so only values > 0 are counted.
}
```
