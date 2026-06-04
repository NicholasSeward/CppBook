# Declarations, Definitions, and Forward Declarations

C++ needs to know a function exists before you call it.

This chapter explains three related ideas:

- declaration
- definition
- forward declaration

## Definition before use

This compiles because `main` sees a declaration of `sayHello` before the call. The definition can come later.

```cpp
#include <iostream>

void sayHello()
{
    std::cout << "Hello\n";
}

int main()
{
    sayHello();
    return 0;
}
```

A **definition** gives the full implementation: header plus body.

## Calling too early

This will not compile:

```cpp
#include <iostream>

int main()
{
    sayHello();
    return 0;
}

void sayHello()
{
    std::cout << "Hello\n";
}
```

When the compiler reaches `sayHello();`, it has not seen `sayHello` yet.

## Reordering can fix it

For small programs, the simplest fix is to place helper functions above `main`.

That is why many early examples put `main` at the bottom.

> NOTE: Placing `main` at the bottom is a simple beginner pattern. Later, header files and forward declarations give us more flexibility.

## Forward declarations

A **forward declaration** tells the compiler a function exists and what its header looks like.

Add one above `main` when the full definition comes later in the file.

```cpp
#include <iostream>

void sayHello(); // forward declaration

int main()
{
    sayHello();
    return 0;
}

void sayHello()
{
    std::cout << "Hello\n";
}
```

The declaration ends with a semicolon.

The definition comes later.

## Declaration vs definition

A **declaration** tells the compiler that something exists.

```
void sayHello();
```

A **definition** provides the implementation.

```
void sayHello()
{
    std::cout << "Hello\n";
}
```

The compiler needs the declaration to check calls. The linker eventually needs the definition so the program can run.

## Mutual calls

Sometimes two functions call each other. This is a form of recursion.

This will not compile without a forward declaration:

```cpp
#include <iostream>

void countDown(int value)
{
    if (value <= 0)
    {
        return;
    }

    std::cout << value << "\n";
    countUp(value - 1); // Error: countUp has not been declared yet
}

void countUp(int value)
{
    countDown(value);
}

int main()
{
    countDown(3);
    return 0;
}
```

Forward declarations let the compiler know both functions exist.

```cpp
#include <iostream>

void countDown(int value);
void countUp(int value);

int main()
{
    countDown(3);
    return 0;
}

void countDown(int value)
{
    if (value <= 0)
    {
        return;
    }

    std::cout << value << "\n";
    countUp(value - 1);
}

void countUp(int value)
{
    countDown(value);
}
```

> NOTE: Recursion is powerful, but it can also be confusing. This example is here to show why forward declarations exist. We will study recursion more carefully later.

## One Definition Rule

For most functions and variables, C++ allows one definition in a given scope.

This violates the **one definition rule**:

```cpp
#include <iostream>

int add(int left, int right)
{
    return left + right;
}

int add(int left, int right)
{
    return left + right;
}

int main()
{
    std::cout << add(2, 3) << "\n";
    return 0;
}
```

The compiler sees two definitions of the same function.

There are special cases involving types, templates, and `inline`, but those are later topics.

## Try it now

### Exercise 1: Add a forward declaration

Prompt: Fix the program by adding a forward declaration.

```cpp
#include <iostream>

int main()
{
    printMessage();
    return 0;
}

void printMessage()
{
    std::cout << "Message\n";
}
```

### Exercise 2: Identify declaration and definition

Prompt: Label which line is the declaration and which block is the definition.

```cpp
#include <iostream>

int doubleValue(int value);

int main()
{
    std::cout << doubleValue(10) << "\n";
    return 0;
}

int doubleValue(int value)
{
    return value * 2;
}
```

