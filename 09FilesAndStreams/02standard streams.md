# Standard Streams

The C++ standard library gives you four common **character streams** tied to the console.

You have used two of them already. The other two are worth knowing even if this book rarely uses them in exercises.

## The four streams

| Stream | Type | Purpose |
|--------|------|---------|
| `std::cin` | input | normal keyboard input |
| `std::cout` | output | normal program output |
| `std::cerr` | output | errors and diagnostics |
| `std::clog` | output | logging (often buffered like `cout`) |

All four live in `<iostream>`.

## `std::cin` and `std::cout`

These are your everyday tools.

```cpp
#include <iostream>

int main()
{
    int value{};

    std::cout << "Enter a number: ";
    std::cin >> value;
    std::cout << "You entered " << value << "\n";

    return 0;
}
```

## `std::cerr` for errors

`std::cerr` is an output stream meant for **error messages**.

It is usually connected to the same terminal as `std::cout`, but the operating system can treat it separately. That helps when another program captures your normal output but should still show errors.

```cpp
#include <iostream>

int main()
{
    int age{};

    std::cout << "Enter your age: ";
    if (!(std::cin >> age))
    {
        std::cerr << "Error: expected a number.\n";
        return 1;
    }

    std::cout << "Age: " << age << "\n";
    return 0;
}
```

> NOTE: This book mostly uses `std::cout` for teaching examples. In larger programs, sending failures to `std::cerr` keeps normal output clean.

## `std::clog`

`std::clog` is also for output. It is often used like a log stream.

For beginners the difference between `std::clog` and `std::cerr` is small. Both are output streams. `cerr` is typically unbuffered so error text shows up quickly.

> PREFERENCE: Use `std::cout` for normal results. Consider `std::cerr` when something went wrong and you want the message separated from regular output.

## One header, four objects

You do not need separate includes for each stream name.

```cpp
#include <iostream>
```

That one line brings in `std::cin`, `std::cout`, `std::cerr`, and `std::clog`.

## Try it now

### Exercise 1: Route an error

Prompt: If the user enters non-numeric input for an `int`, print a short message to `std::cerr` and return `1`.

```cpp
#include <iostream>

int main()
{
    int value{};

    std::cout << "Enter an integer: ";
    // TODO: Read value. On failure, print to cerr and return 1.

    std::cout << "Value: " << value << "\n";
    return 0;
}
```