# Function Calls and Flow

A function call temporarily jumps to another function.

When that function finishes, the program returns to the line after the call.

## A simple call

```cpp
#include <iostream>

void doSomething()
{
    std::cout << "Doing something.\n";
}

int main()
{
    std::cout << "Starting program.\n";
    doSomething();
    std::cout << "Ending program.\n";

    return 0;
}
```

The output is:

```
Starting program.
Doing something.
Ending program.
```

The program starts in `main`, reaches `doSomething();`, runs the body of `doSomething`, and then returns to `main`.

## Reusing a function

You can call the same function as many times as you want.

```cpp
#include <iostream>

void doSomething()
{
    std::cout << "Doing something.\n";
}

int main()
{
    doSomething();
    doSomething();
    doSomething();

    return 0;
}
```

One reason functions are useful is that the function body only has to be written once.

## Functions can call functions

Functions can call other functions.

```cpp
#include <iostream>

void doB()
{
    std::cout << "Starting B.\n";
    std::cout << "Ending B.\n";
}

void doA()
{
    std::cout << "Starting A.\n";
    doB();
    std::cout << "Ending A.\n";
}

int main()
{
    doA();
    return 0;
}
```

The output is:

```
Starting A.
Starting B.
Ending B.
Ending A.
```

`doA` pauses when it calls `doB`. After `doB` finishes, `doA` continues.

## Function headers and bodies

The first line is the **function header**:

```
void doSomething()
```

The function header tells the compiler:

- what type the function returns
- what the function is named
- what information must be passed in

The statements inside `{}` are the **function body**.

## No nested functions

In C++, you cannot define one normal function inside another function.

This will not compile:

```cpp
#include <iostream>

int main()
{
    void helper()
    {
        std::cout << "Helper.\n";
    }

    helper();
    return 0;
}
```

Some languages, such as Python, JavaScript, and Swift, allow nested functions. C++ does not allow normal functions to be defined this way.

## Try it now

### Exercise 1: Trace the output

Prompt: Before running the program, write down what you think it prints.

```cpp
#include <iostream>

void second()
{
    std::cout << "Second\n";
}

void first()
{
    std::cout << "First start\n";
    second();
    std::cout << "First end\n";
}

int main()
{
    std::cout << "Main start\n";
    first();
    std::cout << "Main end\n";

    return 0;
}
```

### Exercise 2: Add another call

Prompt: Add one more function and call it from `main`.

```cpp
#include <iostream>

void printName()
{
    std::cout << "Ada\n";
}

// TODO: Add another void function here.

int main()
{
    printName();
    // TODO: Call your new function.

    return 0;
}
```
