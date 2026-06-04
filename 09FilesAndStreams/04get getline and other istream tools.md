# get, getline, and Other istream Tools

`operator>>` is convenient for numbers and single words.

Sometimes you need one character, a full line, or finer control over what to skip.

## `std::get` for one character

`std::cin.get()` reads **one character**, including spaces and newlines if they are next.

```cpp
#include <iostream>

int main()
{
    char ch{};

    std::cout << "Type a few characters, then Enter: ";
    ch = std::cin.get();

    std::cout << "First character read: [" << ch << "]\n";
    return 0;
}
```

Use `get` when whitespace itself matters.

## Why full names are awkward with `>>`

```cpp
#include <iostream>
#include <string>

int main()
{
    std::string first{};
    std::string last{};

    std::cout << "Enter first and last name: ";
    std::cin >> first >> last;

    std::cout << "Hello, " << first << " " << last << "\n";
    return 0;
}
```

For `Ada Lovelace`, `first` is `Ada` and `last` is `Lovelace`. That works only because there is no space inside a single name.

For `Mary Ann Smith`, `>>` stops at spaces and the result is wrong for a "full name" prompt.

## `std::getline` for a full line

`std::getline` reads until the newline (or end of input) and stores the line in a `std::string`.

```cpp
#include <iostream>
#include <string>

int main()
{
    std::string fullName{};

    std::cout << "Enter your full name: ";
    std::getline(std::cin, fullName);

    std::cout << "Hello, " << fullName << "!\n";
    return 0;
}
```

Include `<string>` for `std::string` and `std::getline`.

### Mixing `>>` and `getline`

A common bug: you read a number with `>>`, then call `getline` and it seems to "skip" input.

```cpp
#include <iostream>
#include <string>

int main()
{
    int age{};
    std::string line{};

    std::cout << "Enter age: ";
    std::cin >> age;

    std::cout << "Enter a sentence: ";
    std::getline(std::cin, line);

    std::cout << "Age: " << age << "\n";
    std::cout << "Sentence: " << line << "\n";
    return 0;
}
```

After `>> age`, the newline from pressing Enter is still in the buffer. The next `getline` may read an empty line.

Fix: clear leftover newline before `getline` when needed:

```cpp
std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
```

You need `#include <limits>` for `std::numeric_limits`.

## Other useful istream members

| Function | What it does |
|----------|----------------|
| `ignore()` | skip one character |
| `ignore(n)` | skip up to `n` characters |
| `ignore(n, ch)` | skip until `n` characters or delimiter `ch` |
| `peek()` | look at the next character without removing it |
| `unget()` | put one character back (if allowed) |
| `putback(ch)` | put a specific character back |
| `gcount()` | characters extracted by the last unformatted read |

```cpp
#include <iostream>

int main()
{
    std::cout << "Type: abcdef then Enter: ";

    char next{static_cast<char>(std::cin.peek())};
    std::cout << "Peek sees: " << next << "\n";

    std::cin.ignore(2);
    char afterIgnore{};
    std::cin.get(afterIgnore);
    std::cout << "After ignoring 2 chars, got: " << afterIgnore << "\n";

    return 0;
}
```

You will not need every function in every program. Know they exist when `>>` is too coarse.

## Try it now

### Exercise 1: Full line greeting

Prompt: Use `std::getline` to read a full name and print a greeting.

```cpp
#include <iostream>
#include <string>

int main()
{
    std::string name{};

    // TODO: Prompt and read a full line into name.
    // TODO: Print "Hello, <name>!".

    return 0;
}
```

### Exercise 2: Age then sentence

Prompt: Read an `int` with `>>`, ignore the rest of the line, then `getline` a sentence.

```cpp
#include <iostream>
#include <limits>
#include <string>

int main()
{
    int age{};
    std::string sentence{};

    std::cout << "Enter age: ";
    std::cin >> age;

    // TODO: Ignore characters through the newline.
    // TODO: getline a sentence and print it.

    return 0;
}
```
