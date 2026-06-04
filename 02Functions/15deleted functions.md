# Deleted Functions

Most of the time you **define** functions you want to use.

C++ also lets you **delete** a function on purpose so it cannot be called.

## Why delete a function?

A deleted function says: this signature exists, but you are not allowed to use it.

That is useful when:

- a library wants to block a dangerous conversion
- a template would otherwise match a type you do not support
- you want to prevent an old overload from being called accidentally

In beginner programs you will see this less often than overloading and default arguments. It is still worth recognizing in real code.

## Basic syntax

```cpp
#include <iostream>

void printInt(int value)
{
    std::cout << value << "\n";
}

void printInt(double value) = delete;

int main()
{
    printInt(5);
    // printInt(5.0); // Error: deleted overload

    return 0;
}
```

`printInt(5)` uses the `int` version.

`printInt(5.0)` would normally call a `double` overload through conversion. Here the `double` overload is deleted, so the call is rejected.

## Compared to not defining the function

If no `double` overload exists, `printInt(5.0)` might still compile by converting to `int`.

Deleting the overload makes the rejection explicit.

## Rare in day-to-day beginner code

You are more likely to use:

- normal function definitions
- overloading
- default arguments

Deleted functions show up more in library design and advanced template code.

> NOTE: If you see `= delete` on a function, read it as "this call is intentionally forbidden."

## Try it now

### Exercise 1: Predict the error

Prompt: Which call compiles and which fails?

```cpp
#include <iostream>

int toInt(int value)
{
    return value;
}

int toInt(double value) = delete;

int main()
{
    std::cout << toInt(10) << "\n";
    std::cout << toInt(10.0) << "\n";

    return 0;
}
```

### Exercise 2: Explain in a comment

Prompt: In one sentence, explain why a library might delete an overload instead of leaving it out.

```cpp
#include <iostream>

int main()
{
    // TODO: Write your explanation here.

    return 0;
}
```
