# Cin Input Validation

`std::cin` is a frequent source of bugs in beginner programs.

It uses **error state** (not exceptions by default), so you must check whether reads succeeded and clean up the input buffer when they do not.

This chapter builds on [Stream States and Robust Input](../09FilesAndStreams/07stream%20states%20and%20robust%20input.md) with patterns you will reuse in many assignments.

## How `operator>>` behaves

Reminder for `std::cin >> value`:

- Leading whitespace is skipped.
- If the buffer is empty, extraction waits for the user to type.
- Characters are read while they fit the target type. Reading stops at the first character that cannot be part of the value or at whitespace.
- If **at least one** character contributed to the value, the read counts as success.
- If **no** characters could be extracted, the stream enters a **fail** state. Further extractions fail until you `clear()` the state and remove the bad characters.

Success on `42abc` still leaves `abc` in the buffer, which can break the next read.

## Input validation

**Input validation** means checking that user input is acceptable before the rest of the program uses it.

In a GUI you might use sliders and checkboxes that only allow valid choices. In the terminal, users can type anything. Your code must cope.

Typical loop:

1. Prompt.
2. Try to read.
3. If bad, explain, clear errors, discard the rest of the line, and ask again.
4. If good, optionally check range or allowed characters, then continue.

## Without error handling

```cpp
#include <iostream>

int main()
{
    int age{};

    std::cout << "Enter age: ";
    std::cin >> age;

    std::cout << "You entered: " << age << '\n';
    return 0;
}
```

Type `twelve`. The read fails. `age` may be unchanged or indeterminate. Later reads on `cin` also fail unless you recover.

## With error handling

```cpp
#include <iostream>
#include <limits>

int main()
{
    int age{};

    while (true)
    {
        std::cout << "Enter age: ";

        if (std::cin >> age)
        {
            break;
        }

        std::cout << "Please enter a whole number.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::cout << "Age: " << age << '\n';
    return 0;
}
```

## Ways text input can be invalid

| Problem | Example | Symptom |
|---------|---------|---------|
| Wrong type | `two` when you need an `int` | Extraction fails |
| Extra junk on line | `42abc` | Read "succeeds" but buffer not clean |
| Valid parse, wrong meaning | `for sure` when you wanted `y` or `n` | Technically read as string, not the policy you need |
| Out of range | age `-5` or `999` when you want 0..120 | Parse works, value bad |

The best fix is often a dedicated input function that loops until all rules pass.

## `getInt` with range

```cpp
#include <iostream>
#include <limits>
#include <string>

int getInt(const std::string& prompt, int minValue, int maxValue)
{
    int value{};

    while (true)
    {
        std::cout << prompt;

        if (!(std::cin >> value))
        {
            std::cout << "Invalid input. Try again.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        if (std::cin.peek() != '\n')
        {
            std::cout << "Enter only one integer on the line.\n";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (value < minValue || value > maxValue)
        {
            std::cout << "Enter a value from " << minValue << " to " << maxValue << ".\n";
            continue;
        }

        return value;
    }
}

int main()
{
    int age{getInt("Enter age (0-120): ", 0, 120)};
    std::cout << "Age: " << age << '\n';
    return 0;
}
```

Goals of a strong input helper:

- extraction must succeed
- the line should be consumed cleanly
- the value must satisfy your program rules

## `getChar` from allowed set

```cpp
#include <iostream>
#include <limits>
#include <string>

char getChar(const std::string& prompt, const std::string& allowed)
{
    char ch{};

    while (true)
    {
        std::cout << prompt;

        if (!(std::cin >> ch))
        {
            std::cout << "Invalid input.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (allowed.find(ch) != std::string::npos)
        {
            return ch;
        }

        std::cout << "Choose one of: " << allowed << '\n';
    }
}

int main()
{
    char again{getChar("Play again (y/n)? ", "yn")};
    std::cout << "You chose: " << again << '\n';
    return 0;
}
```

Note: `>>` into `char` skips whitespace and reads the next non-whitespace character. For full-line answers like `yes` / `no`, use `std::getline` instead.

## Stream tools reference

| Tool | Role in validation |
|------|-------------------|
| `fail()` / `if (cin)` | Detect failed extraction |
| `clear()` | Reset error flags so reads can continue |
| `ignore(n, '\n')` | Discard characters up to newline (clears `42abc` junk) |
| `peek()` | Look at next character without removing it (detect extra junk) |
| `eof()` | True when end of input reached (files, piped input) |

You often use `fail`, `clear`, `ignore`, and `peek` together in input loops.

## Try it now

### Exercise 1: Recover from a failed read

Prompt: Wrap the read in a loop. On failure, print a message, call `clear()` and `ignore()`, and ask again. Try typing `twelve`, then a valid number.

```cpp
// @file: main.cpp
#include <iostream>
#include <limits>

int main()
{
    int age{};

    // TODO: loop until std::cin >> age succeeds
    std::cout << "Enter age: ";
    std::cin >> age;

    std::cout << "Age: " << age << '\n';
    return 0;
}
```

### Exercise 2: Positive scores only

Prompt: Finish `getPositiveInt` so it rejects zero and negative values after a successful parse. Use `peek()` to reject extra junk on the line (for example `42abc`).

```cpp
// @file: main.cpp
#include <iostream>
#include <limits>
#include <string>

int getPositiveInt(const std::string& prompt)
{
    int value{};

    while (true)
    {
        std::cout << prompt;

        if (!(std::cin >> value))
        {
            std::cout << "Invalid input. Try again.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        if (std::cin.peek() != '\n')
        {
            std::cout << "Enter only one integer on the line.\n";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        // TODO: reject if value <= 0

        return value;
    }
}

int main()
{
    int score{getPositiveInt("Enter a positive score: ")};
    std::cout << "Score: " << score << '\n';
    return 0;
}
```

### Exercise 3: `y` or `n`, any case

Prompt: Finish `getYesOrNo` so it accepts `y`, `Y`, `n`, or `N`. Hint: `#include <cctype>` and `std::tolower`.

```cpp
// @file: main.cpp
#include <cctype>
#include <iostream>
#include <limits>
#include <string>

char getYesOrNo(const std::string& prompt)
{
    char ch{};

    while (true)
    {
        std::cout << prompt;

        if (!(std::cin >> ch))
        {
            std::cout << "Invalid input.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        // TODO: normalize with std::tolower(ch)
        // TODO: accept only 'y' or 'n'

        return ch;
    }
}

int main()
{
    char again{getYesOrNo("Play again (y/n)? ")};
    std::cout << "You chose: " << again << '\n';
    return 0;
}
```
