# What Functions Are

A **function** is a named collection of statements that performs a job.

You have already used functions, even if we have not talked about them carefully yet.

## `main` is a function

Every runnable C++ program needs a `main` function. It is where your program starts.

```cpp
#include <iostream>

int main()
{
    std::cout << "Hello from main.\n";
    return 0;
}
```

`main` is special because the operating system calls it when your program runs.

## Library functions

C++ also gives you functions in the Standard Library. You can use them without knowing exactly how they are written.

```cpp
#include <cmath>
#include <iostream>

int main()
{
    double number{25.0};
    double result{std::sqrt(number)};

    std::cout << result << "\n";
    return 0;
}
```

`std::sqrt` is a function from `<cmath>`. You give it a value and it gives a value back.

Most programmers do not rewrite library functions. They learn what the function does, what inputs it needs, and what output it returns.

## Your own functions

You can also write your own functions.

```cpp
#include <iostream>

void printHello()
{
    std::cout << "Hello from a function.\n";
}

int main()
{
    printHello();
    return 0;
}
```

`printHello` is a function we wrote. The line `printHello();` is a **function call**.

## Why functions matter

Functions help you:

- give a chunk of code a name
- reuse code without copying and pasting
- break a large problem into smaller jobs
- test one job at a time

> NOTE: A function should usually have one clear purpose. If a function starts doing many unrelated jobs, it is probably time to split it.

## Try it now

### Exercise 1: Say hello twice

Prompt: Write a function named `printWelcome` and call it twice from `main`.

```cpp
#include <iostream>

// TODO: Write printWelcome here.

int main()
{
    // TODO: Call printWelcome twice.

    return 0;
}
```

### Exercise 2: Use a library function

Prompt: Use `std::sqrt` to print the square root of `81.0`.

```cpp
#include <cmath>
#include <iostream>

int main()
{
    double value{81.0};

    // TODO: Print the square root of value.

    return 0;
}
```
