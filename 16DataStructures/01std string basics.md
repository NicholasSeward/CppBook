# std::string Basics

Programs work with text constantly: names, paths, commands, and user input. C++ provides **`std::string`** for that job.

## Why not C-style character arrays?

A C-style string is a `char` array ending with `'\0'`. The compiler adds the terminator for string literals. You must leave room for it if you build the array yourself.

```cpp
#include <iostream>

int main()
{
    char name[6]{"Ada"};  // holds 'A','d','a','\0' plus one spare slot

    std::cout << name << '\n';
    std::cout << name[0] << '\n';

    return 0;
}
```

`name` works, but the size is fixed at compile time. Appending more text means picking a bigger array or writing careful copy logic yourself.

> PREFERENCE: Do not use C-style strings in new code unless an API or library forces you to (for example a function parameter typed as `const char*`). Prefer `std::string` everywhere else in this course.

`std::string` is usually easier:

- grows and shrinks as needed
- owns its character buffer
- supports `+`, `==`, and `size()` naturally
- works with `std::getline` and file I/O

```cpp
#include <iostream>
#include <string>

int main()
{
    std::string greeting{"Hello"};

    greeting += ", C++";
    std::cout << greeting << '\n';
    std::cout << "Length: " << greeting.size() << '\n';

    return 0;
}
```

## How it works

At a high level, `std::string` behaves like a specialized text container:

- stores characters in heap memory
- tracks **length** (how many characters you are using)

`#include <string>` to use it.

## Creating strings

```cpp
#include <iostream>
#include <string>

int main()
{
    std::string empty{};
    std::string word{"hello"};
    std::string copy{word};
    std::string repeated(5, '*');  // "*****"

    std::cout << empty.size() << '\n';
    std::cout << word << '\n';
    std::cout << copy << '\n';
    std::cout << repeated << '\n';

    return 0;
}
```

## Size and state

| Method | Meaning |
|--------|---------|
| `size()` / `length()` | number of characters (same meaning) |
| `empty()` | true when length is 0 |
| `clear()` | remove all characters |

## Access

| Method | Meaning |
|--------|---------|
| `s[i]` | character at index (no bounds check) |
| `s.at(i)` | character at index (throws if out of range) |
| `s.front()` | first character |
| `s.back()` | last character |

> PREFERENCE: Prefer `.at()` when teaching bounds safety, same as with `std::vector`.

## Reading strings

`std::cin >> word` reads one whitespace-delimited token. It stops at space, tab, or newline.

`std::getline(std::cin, line)` reads a full line, including spaces, until `\n`.

```cpp
#include <iostream>
#include <string>

int main()
{
    std::string word{};
    std::string line{};

    std::cout << "Enter one word: ";
    std::cin >> word;

    std::cout << "Enter a full line: ";
    std::cin.ignore();  // clear leftover '\n' after >>
    std::getline(std::cin, line);

    std::cout << "Word: " << word << '\n';
    std::cout << "Line: " << line << '\n';

    return 0;
}
```

## What is "missing" and why

`std::string` has `pop_back()` but no cheap `pop_front()`. Removing the first character shifts the rest left, which is **O(n)**. Same idea as `std::vector`.

In loops, prefer `+=` or `append()` over repeated `+`, which can create many temporary strings.

## Try it now

### Exercise 1: Build a greeting

Prompt: Ask for a name with `getline`, then print `Hello, <name>!` using `+` or `+=`.

```cpp
// @file: main.cpp
#include <iostream>
#include <string>

int main()
{
    std::string name{};

    // TODO: getline for name
    // TODO: build and print greeting

    return 0;
}
```
