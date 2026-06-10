# Handling Errors

Programs interact with users, files, networks, and hardware. Those interactions fail sometimes.

**Error handling** is how your code responds when something does not go as planned.

## What can go wrong

Examples:

- a function receives an invalid argument
- a file cannot be opened or read
- the user types data that cannot be parsed
- memory or resources are unavailable

It is easy to test only the **happy path** where everything succeeds. Production code (and good homework) also plans for **sad paths**.

## Four broad strategies

| Strategy | Idea | When it fits |
|----------|------|----------------|
| Handle inside the function | Fix, retry, or substitute locally | Caller does not need to know details |
| Return status to caller | `bool`, error code, optional value | Caller decides next step |
| Halt the program | `std::exit` or abort | Unrecoverable fatal error |
| Throw an exception | Signal failure up the call stack | Modern C++ default for exceptional cases |

Often you combine them: try locally, then escalate if recovery fails.

## Handle inside the function

Sometimes the function can recover without bothering the caller.

**Retry** until success (network flakiness, asking the user again):

```cpp
#include <iostream>
#include <limits>
#include <string>

int askPositiveInt()
{
    int value{};

    while (true)
    {
        std::cout << "Enter a positive integer: ";

        if (std::cin >> value && value > 0)
        {
            return value;
        }

        std::cout << "Try again.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}
```

**Cancel** the operation and return a safe default or sentinel.

**Ignore** is rarely correct, but sometimes acceptable for optional cosmetic features. Document why.

```cpp
#include <iostream>

double safeRatio(int a, int b)
{
    if (b == 0)
    {
        return 0.0;  // chosen policy: no ratio defined
    }

    return static_cast<double>(a) / b;
}
```

Ignoring division by zero without telling the caller can hide bugs. Prefer explicit status when the caller cares.

## Pass errors back to the caller

Return `bool` or an error code so the caller chooses what to do.

```cpp
#include <iostream>

bool printIntDivision(int numerator, int denominator)
{
    if (denominator == 0)
    {
        return false;
    }

    std::cout << numerator / denominator << '\n';
    return true;
}

int main()
{
    if (!printIntDivision(10, 0))
    {
        std::cout << "Cannot divide by zero.\n";
    }

    return 0;
}
```

### Sentinel values

Some APIs return a special value that means "error," such as `-1` for "not found."

```cpp
#include <iostream>

constexpr double kReciprocalError{-1.0};

double reciprocal(double x)
{
    if (x == 0.0)
    {
        return kReciprocalError;
    }

    return 1.0 / x;
}

int main()
{
    double result{reciprocal(0.0)};

    if (result == kReciprocalError)
    {
        std::cout << "No reciprocal for zero.\n";
    }

    return 0;
}
```

Sentinels are easy to misuse (what if `-1` is also a valid result?). This book prefers explicit `bool` returns or exceptions for new code, but you will see sentinel patterns in libraries and older code.

## Fatal errors

When recovery is impossible and continuing would corrupt data, ending the program may be appropriate.

```cpp
#include <cstdlib>
#include <iostream>

void requireConfigFile()
{
    // Pseudocode: if critical config missing, stop.
    bool configLoaded{false};

    if (!configLoaded)
    {
        std::cerr << "Fatal: config file missing.\n";
        std::exit(1);
    }
}
```

Use fatal exits sparingly in interactive programs. Prefer returning an error to `main` when you can.

## Exceptions

**Exceptions** let a function say "I cannot complete this" without encoding every failure as a return value. A matching `catch` block elsewhere handles it.

Throw:

```cpp
#include <stdexcept>

double divide(double a, double b)
{
    if (b == 0.0)
    {
        throw std::invalid_argument("divide by zero");
    }

    return a / b;
}
```

Catch:

```cpp
#include <iostream>
#include <stdexcept>

double divide(double a, double b)
{
    if (b == 0.0)
    {
        throw std::invalid_argument("divide by zero");
    }

    return a / b;
}

int main()
{
    try
    {
        std::cout << divide(10.0, 0.0) << '\n';
    }
    catch (const std::invalid_argument& ex)
    {
        std::cout << "Error: " << ex.what() << '\n';
    }

    return 0;
}
```

### Errors vs exceptions (culture and mechanics)

| | Error codes / stream fail | Exceptions |
|--|---------------------------|------------|
| Who notices | Caller must check every time | Uncaught exception propagates until caught |
| Typical for | Expected routine outcomes (`cin` fail) | Exceptional failure paths |
| Risk if ignored | Silent wrong behavior | `std::terminate` if uncaught |

C++ is old enough to have both styles. New application code often leans on exceptions for true error paths. Low-level and embedded code sometimes avoids them for performance or style reasons.

`std::cin` reports failure via stream state, not exceptions by default. [Cin Input Validation](11cin%20input%20validation.md) covers that pattern.

## Try it now

### Exercise 1: Return `false` on bad input

Prompt: Finish `parseScore` so it returns `true` only when `text` is a whole number. Test with good and bad strings in `main`.

```cpp
// @file: main.cpp
#include <iostream>
#include <string>

bool parseScore(const std::string& text, int& outScore)
{
    // TODO: return false for non-numeric text like "abc"
    // TODO: return true and set outScore for valid text like "85"
    return false;
}

int main()
{
    int score{};

    if (parseScore("85", score))
    {
        std::cout << "Parsed: " << score << '\n';
    }
    else
    {
        std::cout << "Failed to parse 85\n";
    }

    if (!parseScore("abc", score))
    {
        std::cout << "Correctly rejected abc\n";
    }
    else
    {
        std::cout << "Should not parse abc\n";
    }

    return 0;
}
```

### Exercise 2: Throw and catch

Prompt: Make `divide` throw `std::invalid_argument` when the denominator is zero. Catch in `main` and print `ex.what()`.

```cpp
// @file: main.cpp
#include <iostream>
#include <stdexcept>

double divide(double a, double b)
{
    // TODO: throw std::invalid_argument when b is 0.0
    return a / b;
}

int main()
{
    try
    {
        std::cout << divide(10.0, 2.0) << '\n';
        std::cout << divide(10.0, 0.0) << '\n';
    }
    catch (const std::invalid_argument& ex)
    {
        std::cout << "Caught: " << ex.what() << '\n';
    }

    return 0;
}
```

### Exercise 3: `bool` return vs throw

Prompt: `openBonus` returns `false` for an expected user mistake. `loadRequiredFile` throws when a required path is empty. Run both paths.

```cpp
// @file: main.cpp
#include <iostream>
#include <stdexcept>
#include <string>

bool openBonus(int level)
{
    if (level < 5)
    {
        return false;
    }

    std::cout << "Bonus opened!\n";
    return true;
}

void loadRequiredFile(const std::string& path)
{
    if (path.empty())
    {
        throw std::runtime_error("required file path is empty");
    }

    std::cout << "Loaded " << path << '\n';
}

int main()
{
    if (!openBonus(2))
    {
        std::cout << "Level too low for bonus.\n";
    }

    try
    {
        loadRequiredFile("");
    }
    catch (const std::runtime_error& ex)
    {
        std::cout << "Load failed: " << ex.what() << '\n';
    }

    return 0;
}
```
