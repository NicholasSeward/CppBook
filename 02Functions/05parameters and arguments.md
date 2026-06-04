# Parameters and Arguments

Return values send information **out** of a function.

Parameters send information **into** a function.

## The black box idea

Think of a function as a small machine:

```
inputs: first number, second number
function: add
output: sum
```

Inputs go in. One output comes back.

## A function with parameters

```cpp
#include <iostream>

int add(int left, int right)
{
    return left + right;
}

int main()
{
    int sum{add(3, 4)};

    std::cout << sum << "\n";
    return 0;
}
```

`left` and `right` are **parameters**.

They are listed inside the function header:

```
int add(int left, int right)
```

Each parameter has a type and a name.

## Arguments

The values passed into a function call are **arguments**.

```
add(3, 4)
```

In that call:

- `3` is copied into `left`
- `4` is copied into `right`

The argument names do not have to match the parameter names.

```cpp
#include <iostream>

int add(int left, int right)
{
    return left + right;
}

int main()
{
    int first{10};
    int second{20};

    std::cout << add(first, second) << "\n";
    return 0;
}
```

`first` and `second` are variables in `main`. `left` and `right` are variables inside `add`.

## Matching the parameter list

The number and types of arguments must match the function's parameter list.

This will not compile:

```cpp
#include <iostream>

int add(int left, int right)
{
    return left + right;
}

int main()
{
    std::cout << add(3) << "\n";
    return 0;
}
```

`add` expects two arguments, but the call only gives one.

## Prompts as parameters

Parameters make a function more flexible.

```cpp
#include <iostream>
#include <string>

int getInt(const std::string& prompt)
{
    int value{};

    std::cout << prompt;
    std::cin >> value;

    return value;
}

int add(int left, int right)
{
    return left + right;
}

int main()
{
    int first{getInt("First number: ")};
    int second{getInt("Second number: ")};

    std::cout << add(first, second) << "\n";
    return 0;
}
```

`getInt` handles input, and `add` handles math. Each function has a clear job.

> PREFERENCE: Most functions should not do user input or output. A function named `add` should just add. A function named `getInt` or `printMenu` clearly tells the reader that input or output is part of the job.

## Nested calls

You can use function calls as arguments:

```cpp
#include <iostream>
#include <string>

int getInt(const std::string& prompt)
{
    int value{};

    std::cout << prompt;
    std::cin >> value;

    return value;
}

int add(int left, int right)
{
    return left + right;
}

int main()
{
    std::cout << add(getInt("First number: "), getInt("Second number: ")) << "\n";
    return 0;
}
```

This is shorter, but not always clearer.

Some compilers may evaluate function arguments in an order you do not expect. If the order matters for the reader, use separate statements.

## Unused parameters

Sometimes a parameter is planned but not used yet. If you leave it unnamed, some compilers will stop warning about it.

```
void drawBox(int width, int /*height*/)
{
    std::cout << "Width: " << width << "\n";
}
```

The comment reminds you what the parameter was meant to be.

## Try it now

### Exercise 1: Multiply

Prompt: Write a function named `multiply` that takes two `int` parameters and returns their product.

```cpp
#include <iostream>

// TODO: Write multiply here.

int main()
{
    std::cout << multiply(6, 7) << "\n";
    return 0;
}
```

### Exercise 2: Prompt twice

Prompt: Complete `getInt` and use it to read two numbers.

```cpp
#include <iostream>
#include <string>

int getInt(const std::string& prompt)
{
    int value{};

    // TODO: Print prompt.
    // TODO: Read value.
    // TODO: Return value.
}

int main()
{
    // TODO: Read two numbers with different prompts.
    // TODO: Print their sum.

    return 0;
}
```
