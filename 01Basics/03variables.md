# Variables

Programs are only interesting when they can work with **data**. Data is anything your program can read, write, or change.

A chunk of data is called a **value**.

## Literals

A **literal** is a value written directly in your source code.

Common literals:

- **Integer**: `334534`
- **Floating point** (has a decimal point): `23.543`
- **Character** (single quotes, one character): `'A'`
- **String** (double quotes, zero or more characters): `"hello"`

Here is a program that prints a few literals:

```cpp
#include <iostream>
#include <string>

int main() {
    std::cout << 334534 << '\n';
    std::cout << 23.543 << '\n';
    std::cout << 'A' << '\n';
    std::cout << "hello" << '\n';
    return 0;
}
```

## Variables

If you do not want to type a literal every time, store a value in a **variable**.

A variable is not the literal itself. A variable is a named place in **memory** where a value can live. When you write `x`, your program reads or writes the value stored at `x`'s location.

NOTE: Later we will talk about where variables live and how to work with addresses using pointers and references. For now, treat a variable as a labeled box that holds a value.

### Reading, writing, and changing a variable

```cpp
#include <iostream>

int main() {
    int x{5};

    std::cout << x << '\n';
    x = x + 1;
    std::cout << x << '\n';

    return 0;
}
```

`x = x + 1;` reads the old value of `x` from the right side, adds one, then writes the new result back into `x` on the left side.

## Types

When you create a variable, you pick a **type**. The type tells the compiler what kind of value it will hold, and how much memory to reserve.

These are the main beginner types:

| Type | What it holds | Typical size | Notes |
|------|---------------|--------------|------|
| `int` | whole numbers | 32 bits | roughly from -2 billion to 2 billion |
| `float` | decimals | 32 bits | about 7 digits of precision; range about 10^-38 to 10^38 |
| `double` | decimals | 64 bits | about 15 to 16 digits of precision; range about 10^-308 to 10^308 |
| `char` | a single character | 8 bits | usually an ASCII character in beginner examples |
| `std::string` | a sequence of characters | varies | can have 0 or more characters |

NOTE: Exact sizes can vary by platform and compiler. `int` is commonly 32 bits on modern desktops, but the standard does not force an exact bit width.

HISTORY: `float` and `double` are both types for numbers with decimals. The names refer to their precision: `float` is "single precision floating point," and `double` stands for "double precision floating point." As humans, we are lazy and just say "float" and "double" now—most other programming languages use these names too. Pascal, VB, and Delphi call single-precision types `Single` instead of `float`. There are also larger types, like quadruple precision, but at that point the names often become more explicit such as `int128` in C++.

NOTE: Many modern languages default to double precision for decimals. In C++, `double` is a solid default unless you have a reason to use `float` (such as large arrays where memory and cache matter). Keep it simple and do not optimize until you need to.

You can define more than one variable of the same type on a single line:

```cpp
int a, b;
```

PREFERENCE: Define one variable per line. For example:

```cpp
int a = 1;
int b = 2;
```

This reduces mistakes—especially if you later change the type for only one variable. C++ lets you mix types in a list, but that quickly gets confusing and error-prone.

## Assignment

You can create a variable and assign later:

```cpp
#include <iostream>

int main() {
    int x;
    x = 5;
    std::cout << x << '\n';
    return 0;
}
```

The `=` here is the **assignment operator**. It takes the value on the right side and stores it into the variable on the left side. It is not an algebra equation.

You can assign multiple times:

```cpp
#include <iostream>

int main() {
    int x{0};
    x = 10;
    x = x + 5; //definetly not allowed in algebra but no problem here
    std::cout << x << '\n';
    return 0;
}
```

NOTE: `=` can mean different things in C++ depending on the types involved. Here it is basic copy assignment for a simple type. Later you will see references and objects where the story gets richer.

## Initialization

You do not have to define and then assign later. You can provide the first value immediately. That is called **initialization**.

C++ offers multiple initialization styles. Two common ones are:

```cpp
int x = 5;   // equals initialization
int y{5};    // brace initialization
```

PREFERENCE: In this book we will usually use brace initialization (`{}`) to build good habits and to prepare for related syntax you will see later. For basic integers in modern C++, `int x = 5;` and `int x{5};` behave similarly most of the time.

NOTE: It is OK to define a variable first and assign later. You must still **initialize it before you use it**. Avoid patterns like `int counter;` followed by code that assumes it started at zero. Even if it seems to work on your machine, it is unclear to the reader and can break with different compilers or settings. If you want a counter that starts at zero, write what you mean: `int counter{0};`.

## Uninitialized variables

It is legal to define a variable and never give it a value. This is almost always a mistake.

```cpp
#include <iostream>

int main() {
    int x;               // uninitialized
    std::cout << x << '\n';
    return 0;
}
```

This program might print `0`. It might print a random-looking number. It might appear to work and then fail later. The value of `x` is **undefined** here, and reading it is not something you can rely on.