# Void Functions

Some functions do a job but do not produce a value.

Those functions use the return type `void`.

## A simple void function

```cpp
#include <iostream>

void printLine()
{
    std::cout << "*************\n";
}

int main()
{
    printLine();
    std::cout << "Report\n";
    printLine();

    return 0;
}
```

`printLine` prints text, but it does not return a value.

## No return value needed

A `void` function does not need a `return` statement at the end.

```cpp
#include <iostream>

void greet()
{
    std::cout << "Hello!\n";
}

int main()
{
    greet();
    return 0;
}
```

When the function reaches the closing `}`, it returns to the caller automatically.

## Early return

You can use `return;` in a `void` function to exit early.

```cpp
#include <iostream>

void printIfPositive(int value)
{
    if (value <= 0)
    {
        return;
    }

    std::cout << value << "\n";
}

int main()
{
    printIfPositive(10);
    printIfPositive(-3);

    return 0;
}
```

The second call prints nothing because the function returns early.

> PREFERENCE: In a `void` function, use `return;` when you need an early exit. Do not add a pointless `return;` at the very end.

## You cannot use a void result

Because a `void` function does not return a value, you cannot print its result.

This will not compile:

```cpp
#include <iostream>

void printHello()
{
    std::cout << "Hello\n";
}

int main()
{
    std::cout << printHello() << "\n";
    return 0;
}
```

`printHello` already does the printing. Just call it:

```cpp
#include <iostream>

void printHello()
{
    std::cout << "Hello\n";
}

int main()
{
    printHello();
    return 0;
}
```

## You cannot return a value from `void`

This will not compile:

```cpp
void badFunction()
{
    return 5;
}
```

If the function needs to produce a value, change its return type.

```
int goodFunction()
{
    return 5;
}
```

## When void makes sense

Use `void` when the job is an action:

- print a menu
- display a table
- update an object by reference
- save data
- show a message

If the job calculates a value, returning the value is usually clearer.

## Try it now

### Exercise 1: Print a menu

Prompt: Write a `void` function that prints three menu options.

```cpp
#include <iostream>

// TODO: Write printMenu here.

int main()
{
    printMenu();
    return 0;
}
```

### Exercise 2: Early return

Prompt: Complete the function so it prints only nonempty names.

```cpp
#include <iostream>
#include <string>

void printName(const std::string& name)
{
    // TODO: If name is empty, return early.
    // TODO: Otherwise print the name.
}

int main()
{
    printName("Ada");
    printName("");
    printName("Grace");

    return 0;
}
```
