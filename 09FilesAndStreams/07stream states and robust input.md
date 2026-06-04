# Stream States and Robust Input

Streams track whether recent operations succeeded.

When input does not match what you expect, you must notice the failure and clean up the buffer.

## When reads go wrong

```cpp
#include <iostream>

int main()
{
    int age{};

    std::cout << "Enter your age: ";
    std::cin >> age;

    if (!std::cin)
    {
        std::cout << "That was not a valid integer.\n";
    }

    return 0;
}
```

Type `Asdf` when the program expects an `int`. The read fails.

## Checking stream state

| Check | Meaning |
|-------|---------|
| `good()` | stream is ready for I/O |
| `eof()` | end of input reached |
| `fail()` | logical error or failed read |
| `bad()` | serious stream error |
| `operator bool` / `if (stream)` | commonly used as "ok to use" |

After a failed numeric read, `fail()` is true until you fix the stream.

`clear()` resets error flags so you can try again:

```
std::cin.clear();
```

Failed reads often leave bad characters in the buffer. Skip them with `ignore`:

```
#include <limits>

std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
```

`std::numeric_limits<std::streamsize>::max()` means "as many characters as needed" until the newline.

You must `#include <limits>` for that expression.

## A loop that asks until input works

```cpp
#include <iostream>
#include <limits>

int main()
{
    int age{};

    while (true)
    {
        std::cout << "Enter your age: ";

        if (std::cin >> age)
        {
            break;
        }

        std::cout << "Please enter a whole number.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::cout << "Age: " << age << "\n";
    return 0;
}
```

This pattern is common enough to wrap in a function.

## `getInt` helper

```cpp
#include <iostream>
#include <limits>
#include <string>

int getInt(const std::string& prompt)
{
    int value{};

    while (true)
    {
        std::cout << prompt;

        if (std::cin >> value)
        {
            return value;
        }

        std::cout << "Invalid input. Try again.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

int main()
{
    int score{getInt("Enter score: ")};
    std::cout << "Score: " << score << "\n";
    return 0;
}
```

## Stronger `getInt`: nothing extra on the line

If the user types `42abc`, `>>` may read `42` and leave `abc` in the buffer. The read "succeeded" but the line was not clean.

After a successful `>>`, use `peek()` to look at the next character without removing it. If it is not a newline, something extra is still waiting.

```cpp
#include <iostream>
#include <limits>
#include <string>

int getInt(const std::string& prompt)
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
        return value;
    }
}

int main()
{
    int age{getInt("Enter age: ")};
    std::cout << "Age: " << age << "\n";
    return 0;
}
```

`42abc` fails because `peek()` sees `a`, not `\n`.

`42` followed by Enter passes because the next character is `\n`.

> PROTIP: Put `getInt` in a small helper file once you are comfortable with headers. Reuse it in every program that asks for numbers.