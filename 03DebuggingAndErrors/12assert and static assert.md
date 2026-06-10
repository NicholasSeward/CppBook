# Assert and `static_assert`

Some conditions should **always** be true if your program is correct. **Assertions** check those conditions and stop execution when they are violated.

Assertions are for catching **programmer mistakes** during development, not for routine user input failures.

## Contracts: pre, post, and invariants

When you design a function, think about three kinds of promises:

| Term | Meaning | Example |
|------|---------|---------|
| **Precondition** | Must be true before the function runs | Index is less than `size()` |
| **Invariant** | Must stay true during an operation | A sorted vector stays sorted after insert (comes up heavily with classes) |
| **Postcondition** | Must be true when the function finishes | `dist` is positive for distinct points; `sum(a, b)` returns `a + b` |

Assertions often document preconditions and postconditions in code.

## `assert` at runtime

`assert` is a macro from `<cassert>`. If the expression is false, the program aborts with a diagnostic (in debug builds).

```cpp
#include <cassert>
#include <cmath>
#include <iostream>

double dist(double x1, double y1, double x2, double y2)
{
    double dx{x2 - x1};
    double dy{y2 - y1};
    double result{std::sqrt(dx * dx + dy * dy)};

    assert(result > 0.0 && "distance must be positive for distinct points");

    return result;
}

int main()
{
    std::cout << dist(0.0, 0.0, 3.0, 4.0) << '\n';
    return 0;
}
```

The points `(0, 0)` and `(3, 4)` are three units apart horizontally and four vertically, so the distance is `5`. The `assert` documents a **postcondition**: if your math is right, `result` must be positive here. If a bug produced zero or a negative value, you want to know immediately during development.

## `assert` vs exceptions

They can look similar but serve different roles.

**Good `assert`:** impossible if callers obey the contract.

```cpp
#include <cassert>
#include <vector>

int& elementAt(std::vector<int>& values, std::size_t index)
{
    assert(index < values.size());  // caller must guarantee valid index
    return values.at(index);
}
```

**Good exception:** failure can happen in normal use (bad file, bad user file format).

```cpp
#include <fstream>
#include <stdexcept>
#include <string>

std::string readFirstLine(const std::string& path)
{
    std::ifstream input{path};

    if (!input)
    {
        throw std::runtime_error("could not open file: " + path);
    }

    std::string line{};
    std::getline(input, line);
    return line;
}
```

Rule of thumb:

- **Assert:** "This should never happen unless I have a bug."
- **Exception or error return:** "This might happen because the world is messy."

## `static_assert` at compile time

`static_assert` checks a condition **while compiling**. If it fails, you get a compile error with your message.

```
#include <type_traits>

static_assert(sizeof(int) >= 4, "int must be at least 32 bits for this program");
```

Use `static_assert` when the check does not need runtime data: type sizes, template constraints, constants known at compile time.

The general push in modern C++ is to **fail earlier**. Compile-time beats runtime beats silent wrong answers.

## Performance and release builds

Assertions can be disabled by defining `NDEBUG` before including `<cassert>`. Many release builds do that so failed internal checks do not abort in the field.

```cpp
#define NDEBUG    // Enable this line to disable assertions in the program
#include <cassert>
#include <iostream>

int main()
{
    int value = -1;
    assert(value >= 0 && "Value must be non-negative");  // Will not abort, even though value is negative
    std::cout << "Continuing after assert\n";
    return 0;
}
```

In practice, assertions that guard truly internal logic are cheap compared to I/O. Do not avoid them from fear of slowdown during learning.

## Messages in `assert`

The standard `assert` macro only takes one expression. A common trick is logical AND with a pointer to a string message:

```cpp
#include <cassert>

void setCount(int count)
{
    assert(count >= 0 && "count must be non-negative");
}
```

Why it works: in `A && B`, if `A` is false, `B` is not evaluated for the *result*, but the assert macro still prints context. The string literal `"count must be non-negative"` has a non-null address, so `count >= 0 && "message"` is false when `count` is negative, triggering the assert. The string may appear in the diagnostic depending on the implementation.

For clearer messages in larger projects, projects use custom assert macros or libraries. The idiom above is enough for coursework.

## Stub unimplemented features

```cpp
#include <cassert>
#include <iostream>

void exportToPdf()
{
    assert(false && "exportToPdf not implemented yet");
}

int main()
{
    exportToPdf();
    return 0;
}
```

Hitting this during development reminds you the feature is a placeholder. Remove or replace before shipping.

## Choosing a mechanism

| Mechanism | Use for | Do not use for |
|-----------|---------|----------------|
| Stream `fail` / `bool` return | Expected `cin` problems, recoverable I/O | Invariant that should never break |
| `assert` | Internal logic, preconditions between your own functions | Validating casual user keyboard input |
| `static_assert` | Compile-time type/size/template rules | Values only known at runtime |
| Exceptions | failures callers should handle | Control flow for ordinary branches |

> PREFERENCE: In most modern C++, use exceptions for error handling whenever possible—this is the approach taken in this book. Error codes are sometimes needed for low-level calls or when interfacing with certain APIs, but exceptions provide clearer, safer error management in your own code. Avoid using asserts for normal input validation or error handling; only use them to catch programmer bugs or unexpected internal mistakes. For regular error handling, choose exceptions over error codes when you have the option, and generally do not use asserts except with legacy libraries that require them.

## Try it now

### Exercise 1: Precondition with `assert`

Prompt: Finish `valueAt` with an `assert` that `index` is in range. Run with the valid call, then uncomment the bad call to see the assertion fire.

```cpp
// @file: main.cpp
#include <cassert>
#include <iostream>
#include <vector>

int valueAt(const std::vector<int>& values, std::size_t index)
{
    // TODO: assert index < values.size()
    return values.at(index);
}

int main()
{
    std::vector<int> values{10, 20, 30};

    std::cout << valueAt(values, 1) << '\n';

    // Uncomment to trigger the assert during development:
    // std::cout << valueAt(values, 99) << '\n';

    return 0;
}
```

### Exercise 2: Postcondition with `dist`

Prompt: Finish `dist` and add `assert(result >= 0.0)` after computing the distance. This assert should never fail if the math is correct—it serves as a safeguard against internal calculation bugs. Run with distinct points.

```cpp
// @file: main.cpp
#include <cassert>
#include <cmath>
#include <iostream>

double dist(double x1, double y1, double x2, double y2)
{
    double dx{x2 - x1};
    double dy{y2 - y1};
    double result{std::sqrt(dx * dx + dy * dy)};

    // This should never fail unless the math above is broken:
    assert(result >= 0.0 && "Internal error: distance result should never be negative");

    return result;
}

int main()
{
    std::cout << dist(0.0, 0.0, 3.0, 4.0) << '\n';

    // The assert should never fail if the math is right,
    // even when the points are the same (distance = 0):
    // std::cout << dist(1.0, 1.0, 1.0, 1.0) << '\n';

    return 0;
}
```

### Exercise 3: `static_assert` at compile time

Prompt: Run as-is. Then change the condition to `sizeof(int) == 1` and run again to read the compile error. Change it back when done.

```cpp
// @file: main.cpp
#include <iostream>

static_assert(sizeof(char) == 1, "char must be one byte on this platform");

int main()
{
    std::cout << "sizeof(char) = " << sizeof(char) << '\n';
    return 0;
}
```

### Exercise 4: `assert` vs exception

Prompt: `setCount` uses `assert` for an internal contract. `setCountSafe` throws for invalid input a caller might supply. Run both paths.

```cpp
// @file: main.cpp
#include <cassert>
#include <iostream>
#include <stdexcept>

void setCount(int count)
{
    assert(count >= 0);
    std::cout << "setCount internal: " << count << '\n';
}

void setCountSafe(int count)
{
    if (count < 0)
    {
        throw std::invalid_argument("count must be non-negative");
    }

    std::cout << "setCountSafe: " << count << '\n';
}

int main()
{
    setCount(3);

    try
    {
        setCountSafe(-1);
    }
    catch (const std::invalid_argument& ex)
    {
        std::cout << "Caught: " << ex.what() << '\n';
    }

    // Uncomment to see assert fail (development only):
    // setCount(-1);

    return 0;
}
```
