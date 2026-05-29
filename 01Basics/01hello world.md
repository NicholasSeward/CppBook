# Hello World

The simplest way to start learning C++ is by writing a program that prints a message. This chapter introduces key ideas: **statements**, the **`main`** function, **strings**, and common kinds of errors, using the standard hello world example.

## Statements

A **statement** is a single step your program takes. In C++, most statements end with a semicolon (`;`).

You can group statements inside a **function**, a named block of code that runs together.

## `main`: where execution starts

C++ has a special function called **`main`**. That is where your program begins.

For starter programs, you put one statement after another inside `main`. The runtime runs them in order from top to bottom.

### One statement

Here is hello world with a single output statement:

```cpp
#include <iostream>

int main()
{
    std::cout << "Hello, world!\n";
    return 0;
}
```

### Multiple statements

Add more statements and they run one after another:

```cpp
#include <iostream>

int main()
{
    std::cout << "Hello, world!\n";
    std::cout << "Second line.\n";
    return 0;
}
```

### Without `main`

If there is no `main`, the program has no defined entry point, even a typo counts:

```cpp
#include <iostream>

int Main()
{  // wrong: must be main
    std::cout << "Hello\n";
    return 0;
}
```

The compiler will report an error. Your program does not know where to start.

### When the program ends

A simple program ends when execution reaches the end of `main` (after `return 0` runs).

## Built-in and custom functions

C++ ships with the [Standard Library](https://en.wikipedia.org/wiki/C%2B%2B_Standard_Library) (often called the STL): many ready-made functions you can call. You can also write your own.

```cpp
#include <iostream>
#include <cmath>

int doubleValue(int x)
{
    return x * 2;
}

int main()
{
    std::cout << "sqrt(9) = " << std::sqrt(9) << '\n';
    std::cout << "double(5) = " << doubleValue(5) << '\n';
    return 0;
}
```

`std::sqrt` comes from the library; `doubleValue` is yours.

## Strings and characters

In hello world, the text inside quotes is a **string literal**, characters grouped together between `"` characters.

You can also store a single character or a longer string in variables:

```cpp
#include <iostream>
#include <string>

int main()
{
    char letter = 'A';
    std::string word = "ASCII";

    std::cout << letter << '\n';
    std::cout << word << '\n';
    return 0;
}
```

## Character sets: from ASCII to Unicode

Computers store text as numbers. The oldest still widely used mapping is [ASCII](https://en.wikipedia.org/wiki/ASCII) (American Standard Code for Information Interchange). For example, capital **A** is **65** on the table, which is `1000001` in binary.

Computers send letters as bits, just 1s and 0. If we send those bits down a wire, the signal might look like this:

```
Clock:
     +   +---+   +---+   +---+   +
     |   |   |   |   |   |   |   |
     |   |   |   |   |   |   |   |
     +---+   +---+   +---+   +---+
Signal:
     + +-+   +---+   +---+   +-+ +
     | | |   |   |   |   |   | | |
     | | |   |   |   |   |   | | |
     +-+ +---+   +---+   +---+ +-+
Bits:  1   0   0   0   0   0   1  = 65 = 'A'

```
In a common modulation, each **1** is two voltage changes for each clock cycle and each **0** is only one volate change.

Today we need far more than ASCII, emojis, many languages, symbols. [Unicode](https://en.wikipedia.org/wiki/Unicode) and encodings like UTF-8 extend the idea while staying largely backward compatible with ASCII for basic English text. Most source code for most programming languages is **plain text** restricted to ASCII characters.

> HISTORY: ASCII appeared in the 1960s, well before graphical monitors were common. Many programs printed on paper. Codes 0 to 31 are mostly **control characters** for devices (not printable glyphs). Some remain useful (`\n` newline, `\t` tab). Others are historical baggage on modern systems, but we still inherit them. A fun one is the **bell** (code 7): printing it can still trigger a system beep, once used to signal that a long job finished.

```cpp
#include <iostream>

int main()
{
    char bell = 7; // ASCII code for bell
    std::cout << "Done!" << bell << '\n';
    return 0;
}
```

ASCII originally used 7 bits of an 8-bit byte. The spare bit, and later [code pages](https://en.wikipedia.org/wiki/Code_page), enabled “extended” characters for box-drawing and simple menus before true GUIs:

```
╔══════════════════╗
║ 1. New game      ║
║ 2. Load game     ║
║ 3. Quit          ║
╚══════════════════╝
```

## How hello world works, line by line

```cpp
#include <iostream>

int main()
{
    std::cout << "Hello, world!\n";
    return 0;
}
```

- `#include <iostream>` ,  a **preprocessor directive**. Before compilation, the compiler pulls in declarations from `<iostream>`, giving you `std::cout` (character output) and `std::cin` (character input).
- The blank line ,  C++ ignores extra **whitespace**. You do not need blank lines, but they separate ideas and help humans (and tools) read the file.

> AI: Large codebases are increasingly written and maintained with AI assistance. Readable layout and predictable style still matter: conventions make code easier for people and models to parse and extend.

- `int main()` ,  defines `main`. The `int` is the **return type**: the kind of value `main` sends back to the environment. Think of a math helper that takes a number and **returns** a result; `main` returns an integer status code.
- `std::cout` ,  standard character output (typically the terminal). The `<<` **insertion operator** sends strings or other values into the stream.
- `return 0` ,  success. Conventionally `0` means “finished OK.” Non-zero values (such as `1`) often mean something went wrong; you can assign your own meanings in larger programs.

## When things go wrong

Programs fail in three broad ways:

1. **Syntax** (compile-time) ,  the compiler cannot understand the source: missing `;`, wrong quotes, typo in `main`.
2. **Runtime** ,  the build succeeded but the program crashes or stops abnormally while running.
3. **Logic** ,  it runs but does the wrong thing.

This chapter focuses on **syntax** errors, sometimes called compilation errors.

> AI: Missing semicolons and typos used to cost hours of debugging. Today, assistants can spot many syntax errors instantly. But learning theory says that wrestling with mistakes helps you build lasting understanding, struggle is a key part of learning. It’s still an open question what balance of guided help versus personal problem solving works best for learning programming in the modern world. When you are starting out, still try to understand *why* a fix is needed.

### Try breaking your program

Start with a simple working example you can run and modify:

```cpp
#include <iostream>

int main()
{
    std::cout << "Hello, world!\n";
    return 0;
}
```

Deliberately introduce mistakes and read the compiler message:

- Remove a semicolon after a statement
- Change `"` to `'` in the wrong place
- Misspell `main` as `Main` or `man`
- Drop `#include <iostream>` and use `std::cout` anyway

Sometimes the message points straight at the problem; sometimes it is vague. Different compilers and flags change the wording.

> NOTE: Runnable snippets in this book are often compiled to [WebAssembly](https://en.wikipedia.org/wiki/WebAssembly) with [Clang](https://en.wikipedia.org/wiki/Clang). Outside the book, this text assumes **g++** (GNU C++). Other common toolchains include [GCC](https://en.wikipedia.org/wiki/GNU_Compiler_Collection) and [Microsoft Visual C++](https://en.wikipedia.org/wiki/Microsoft_Visual_C%2B%2B) (MSVC).
