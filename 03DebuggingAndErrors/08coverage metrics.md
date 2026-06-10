# Coverage Metrics

Tests give confidence. **Coverage metrics** ask a follow-up question: how much of your code did those tests actually run?

High coverage is useful. It is not the same as "no bugs."

## Why coverage matters

Untested code is code you are guessing about. Coverage highlights functions, branches, and loops your tests never reached.

Use coverage to find gaps in your test plan, not as a score to game.

## Statement coverage

**Statement coverage** is the percentage of executable statements that ran at least once during tests.

If you never call a helper function, its statements count as uncovered.

## Branch coverage

**Branch coverage** tracks whether each side of a decision was taken.

```cpp
#include <iostream>

std::string gradeLabel(int score)
{
    if (score >= 60)
    {
        return "pass";
    }
    else
    {
        return "fail";
    }
}

bool testGradeLabel()
{
    bool passBranch{gradeLabel(75) == "pass"};
    bool failBranch{gradeLabel(40) == "fail"};
    return passBranch && failBranch;
}

int main()
{
    if (testGradeLabel())
    {
        std::cout << "gradeLabel tests passed (both branches)\n";
    }
    else
    {
        std::cout << "gradeLabel tests failed\n";
    }

    return 0;
}
```

Testing only `score = 75` covers the `if` branch but not the `else`. Add a second test case with a failing score to get full **branch coverage**.

## Loop coverage

Loops behave differently when they run **zero**, **one**, or **many** times. Good tests often hit all three when it matters.

```cpp
#include <iostream>
#include <vector>

int sumVector(const std::vector<int>& values)
{
    int total{0};

    for (int value : values)
    {
        total += value;
    }

    return total;
}

bool testSumVector()
{
    std::vector<int> empty{};
    std::vector<int> one{5};
    std::vector<int> many{1, 2, 3};

    return sumVector(empty) == 0
        && sumVector(one) == 5
        && sumVector(many) == 6;
}

int main()
{
    std::cout << (testSumVector() ? "sum tests passed\n" : "sum tests failed\n");
    return 0;
}
```

## Type and category coverage

If a function should work for both `int` and `double`, test both. If it handles empty and non-empty input, test both.

Think in **categories** of input, not every possible value.

## Limits of 100% coverage

You can execute every line and still miss bugs:

- wrong formula on a line you did hit
- untested combinations of branches across functions
- behavior that depends on timing or external systems

> NOTE: Aim for **high coverage with meaningful tests**. Add tests when you find real bugs. Quantity alone does not replace thinking about edge cases.

## Regression testing

The practical loop (from [Testing](05testing.md)):

1. Find a bug in production or manual testing.
2. Reproduce it.
3. Add a test that fails before the fix.
4. Fix the bug.
5. Run the full suite (regression run).

Old tests protect old behavior. The new test protects the specific fix.

## Try it now

### Exercise 1: Branch coverage

Prompt: `ticketPrice` has two branches. The starter test covers only the discount path. Add a second `TEST_CASE` so both the `if` and `else` branches run.

```cpp
// @file: doctest/doctest.h from:https://raw.githubusercontent.com/doctest/doctest/refs/heads/master/doctest/doctest.h hidden
// @file: main.cpp
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

double ticketPrice(int age)
{
    if (age < 13)
    {
        return 8.0;
    }
    else
    {
        return 12.0;
    }
}

TEST_CASE("child ticket uses discount branch")
{
    CHECK(ticketPrice(10) == 8.0);
}

// TODO: TEST_CASE for the else branch (age 13 or older)
// TODO: CHECK adult ticket price is 12.0
```

Run the tests after adding only the first case. Then add the second case and run again. You should have two passing tests and both branches exercised.

### Exercise 2: Loop coverage

Prompt: `countAbove` loops over a vector. Add `TEST_CASE` blocks for zero iterations (empty), one iteration, and many iterations.

```cpp
// @file: doctest/doctest.h from:https://raw.githubusercontent.com/doctest/doctest/refs/heads/master/doctest/doctest.h hidden
// @file: main.cpp
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"
#include <vector>

int countAbove(const std::vector<int>& values, int threshold)
{
    int count{0};

    for (int value : values)
    {
        if (value > threshold)
        {
            ++count;
        }
    }

    return count;
}

// TODO: TEST_CASE with an empty vector (loop runs 0 times) -> countAbove == 0
// TODO: TEST_CASE with one value above threshold (loop runs 1 time)
// TODO: TEST_CASE with several values, some above threshold (loop runs many times)
```
