# What Streams Are

You have already used streams in [Input and Output](../01Basics/04input%20output.md) with `std::cin` and `std::cout`.

A **stream** is a sequence of bytes you read or write **in order**, one step after another.

Think of it like water flowing through a pipe:

- data arrives at one end
- your program takes bytes out, or puts bytes in, as it goes
- you do not jump around randomly in the simple cases in this book

## Input and output streams

An **input stream** gives data to your program.

`std::cin` is the usual keyboard input stream.

An **output stream** sends data out of your program.

`std::cout` is the usual terminal output stream.

| Stream | Direction | Typical source or destination |
|--------|-----------|-------------------------------|
| `std::cin` | input | keyboard |
| `std::cout` | output | terminal |

## The operators you already know

For input streams you use the **extraction operator** `>>`:

```
std::cin >> age;
```

For output streams you use the **insertion operator** `<<`:

```
std::cout << age << "\n";
```

Some stream types support both directions. File and string streams can do more than console I/O. This part of the book stays with straightforward sequential use.

> PREFERENCE: Keep console and file I/O sequential. Bidirectional streams and random access inside a stream are possible, but most beginner programs read or write from start to end.

## Buffering

Streams often **buffer** data. That means they hold bytes temporarily before your program or the operating system processes them.

**Input buffering (`std::cin`):**

When you type on the keyboard, characters may sit in a buffer until you press Enter or until a read operation tries to take them.

**Output buffering (`std::cout`):**

When you print, text may wait in a buffer until the buffer fills, you flush it, or the program ends. The operating system then shows it on screen.

That is why `std::endl` can feel different from `"\n"`. `std::endl` inserts a newline and **flushes** the output stream.

```cpp
#include <iostream>

int main()
{
    std::cout << "Step 1\n";
    std::cout << "Step 2" << std::endl;
    std::cout << "Step 3\n";

    return 0;
}
```

Buffering matters more when you write to **files**. You will see `flush` and `close` later so data actually reaches disk.

## Streams beyond the keyboard

The same stream ideas apply to:

- strings in memory (`std::istringstream`, `std::ostringstream`)
- files on disk (`std::ifstream`, `std::ofstream`)

Reading from a file feels like reading from `std::cin`.

Writing to a file feels like writing to `std::cout`.

The upcoming chapters build those skills step by step.

## Try it now

### Exercise 1: Name the streams

Prompt: In comments, label each line as input or output.

```cpp
#include <iostream>

int main()
{
    int score{};

    // TODO: Comment: input or output?
    std::cout << "Enter score: ";
    // TODO: Comment: input or output?
    std::cin >> score;
    // TODO: Comment: input or output?
    std::cout << "Score: " << score << "\n";

    return 0;
}
```