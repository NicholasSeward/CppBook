# Doctest

[doctest](https://github.com/doctest/doctest) is a small, header-only C++ test framework. You write test cases as normal C++ code, compile a test program, and run it like any executable.

This book uses doctest because it is easy to add to a project and reads clearly in examples.

## The header and `main`

doctest ships as a single header: `doctest/doctest.h`.

By default, doctest does **not** define `main`. You add one line in exactly **one** `.cpp` file in your test build:

```
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"
```

That macro tells the header to compile a `main` function that runs all `TEST_CASE` blocks and reports results.

| Macro placement | Effect |
|-----------------|--------|
| In your test `.cpp` only | Test binary has `main`, runs doctest |
| Not defined anywhere | You must write your own `main` that calls `doctest::Context` |
| In more than one file | Link error: multiple definitions of `main` |

> NOTE: In TxtBook playgrounds, the doctest header is fetched automatically. On your machine, download the header into a `doctest/` folder or point the compiler at it with `-I`.

## Basic equality checks

A **test case** is a named group of checks. **`CHECK`** compares an expression to what you expect. If it fails, doctest prints the file, line, and values.

```cpp
// @file: doctest/doctest.h from:https://raw.githubusercontent.com/doctest/doctest/refs/heads/master/doctest/doctest.h hidden
// @file: main.cpp
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

int add(int a, int b)
{
    return a + b;
}

TEST_CASE("add combines integers")
{
    CHECK(add(2, 3) == 5);
    CHECK(add(-1, 1) == 0);
    CHECK(add(0, 0) == 0);
}
```

**`REQUIRE`** is like `CHECK`, but the current test case stops on the first `REQUIRE` failure. Use `CHECK` when you want to see every failure in one run; use `REQUIRE` when later checks depend on earlier ones.

## Testing exceptions

Some functions signal failure by **throwing**. doctest can verify that an exception is thrown and optionally that it has a specific type.

```cpp
// @file: doctest/doctest.h from:https://raw.githubusercontent.com/doctest/doctest/refs/heads/master/doctest/doctest.h hidden
// @file: main.cpp
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"
#include <stdexcept>

double divide(double a, double b)
{
    if (b == 0.0)
    {
        throw std::invalid_argument("divide by zero");
    }

    return a / b;
}

TEST_CASE("divide works for normal values")
{
    CHECK(divide(10.0, 2.0) == 5.0);
}

TEST_CASE("divide rejects zero denominator")
{
    CHECK_THROWS(divide(1.0, 0.0));
    CHECK_THROWS_AS(divide(1.0, 0.0), std::invalid_argument);
}
```

| Macro | Meaning |
|-------|---------|
| `CHECK_THROWS(expr)` | `expr` must throw some exception |
| `CHECK_THROWS_AS(expr, Type)` | `expr` must throw `Type` (or a derived type) |
| `CHECK_NOTHROW(expr)` | `expr` must not throw |

The throwing expression is evaluated inside the macro. Write the full call you want to test: `divide(1.0, 0.0)`, not just `divide`.

## Why not test a file that already has `main`?

A C++ program can have only **one** `main` function across all linked `.cpp` files.

If your application is one file:

```cpp
#include <iostream>

int square(int x)
{
    return x * x;
}

int main()
{
    std::cout << square(4) << '\n';
    return 0;
}
```

you cannot add doctest's `main` in the same build. The linker will report multiple definitions of `main`.

That is not a doctest limitation. It is how C++ linking works.

## Separate the app from the code under test

Put reusable logic in files **without** `main`. Use `main.cpp` only to wire pieces together: read input, call helpers, print output.

```
project/
  math.h
  math.cpp      // implementations, no main
  main.cpp      // application entry point
  math_test.cpp // doctest entry point
```

**math.h**

```cpp
#pragma once

int add(int a, int b);
double divide(double a, double b);
```

**math.cpp**

```cpp
#include "math.h"
#include <stdexcept>

int add(int a, int b)
{
    return a + b;
}

double divide(double a, double b)
{
    if (b == 0.0)
    {
        throw std::invalid_argument("divide by zero");
    }

    return a / b;
}
```

**main.cpp** (run the program)

```cpp
#include <iostream>
#include "math.h"

int main()
{
    std::cout << add(2, 3) << '\n';
    return 0;
}
```

**math_test.cpp** (run the tests)

```cpp
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"
#include "math.h"

TEST_CASE("add")
{
    CHECK(add(2, 3) == 5);
}

TEST_CASE("divide by zero throws")
{
    CHECK_THROWS_AS(divide(1.0, 0.0), std::invalid_argument);
}
```

Same `math.cpp` is linked into both executables. Different entry files supply different `main` functions.

## Two compile commands

Build and run the **application**:

```
g++ -std=c++17 -I path/to/doctest main.cpp math.cpp -o app
./app
```

Build and run the **tests** (only the test file defines `DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN`):

```
g++ -std=c++17 -I path/to/doctest math_test.cpp math.cpp -o math_test
./math_test
```

You compile `math_test.cpp` + `math.cpp`, not `main.cpp`. The test binary never includes the application's `main`.

| Goal | Source files | Output |
|------|----------------|--------|
| Run the program | `main.cpp`, helpers | `app` |
| Run unit tests | `*_test.cpp`, helpers | `math_test` |

> PROTIP: Name test files `something_test.cpp` so they are easy to spot. Some projects put them in a `tests/` folder with the same layout.

## What belongs in `main.cpp`

`main` should stay thin:

- parse or read input
- call functions that do the real work
- print or save results

Heavy logic in `main` is hard to reuse and hard to test without running the whole program. Move that logic into named functions in other `.cpp` files, then unit test those functions directly.

See [Unit Test Principles](07unit%20test%20principles.md) for how to write tests that are worth maintaining.

## Try it now

### Exercise 1: Add `CHECK` tests for `maxOf`

Prompt: `maxOf` is implemented below. Add `CHECK` lines for equal values, negatives, and swapped argument order.

```cpp
// @file: doctest/doctest.h from:https://raw.githubusercontent.com/doctest/doctest/refs/heads/master/doctest/doctest.h hidden
// @file: main.cpp
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

int maxOf(int a, int b)
{
    return a > b ? a : b;
}

TEST_CASE("maxOf returns the larger of two values")
{
    // TODO: CHECK maxOf(3, 7) == 7
    // TODO: CHECK equal arguments
    // TODO: CHECK negative numbers
    // TODO: CHECK swapped order
}
```

### Exercise 2: Test an exception with `CHECK_THROWS_AS`

Prompt: Finish `parsePositive` so it throws `std::invalid_argument` for zero or negative values. Add the `CHECK_THROWS_AS` test.

```cpp
// @file: doctest/doctest.h from:https://raw.githubusercontent.com/doctest/doctest/refs/heads/master/doctest/doctest.h hidden
// @file: main.cpp
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"
#include <stdexcept>

int parsePositive(int value)
{
    if (value <= 0)
    {
        throw std::invalid_argument("value must be positive");
    }

    return value;
}

TEST_CASE("parsePositive accepts valid input")
{
    CHECK(parsePositive(5) == 5);
}

TEST_CASE("parsePositive rejects non-positive input")
{
    // TODO: CHECK_THROWS_AS(parsePositive(0), std::invalid_argument)
    // TODO: CHECK_THROWS_AS(parsePositive(-3), std::invalid_argument)
}
```

### Exercise 3: Split code and test a helper file

Prompt: Finish `triple` in `calc.cpp`, then add a `TEST_CASE` with at least two `CHECK` lines.

```cpp
// @file: doctest/doctest.h from:https://raw.githubusercontent.com/doctest/doctest/refs/heads/master/doctest/doctest.h hidden
// @file: main.cpp
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"
#include "calc.h"

TEST_CASE("triple scales a value")
{
    // TODO: CHECK triple(2) == 6
    // TODO: CHECK triple(-1) == -3
}

// @file: calc.h
#pragma once

int triple(int value);

// @file: calc.cpp
#include "calc.h"

int triple(int value)
{
    // TODO: return value * 3
    return 0;
}
```
