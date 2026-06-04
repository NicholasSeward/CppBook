# Scope

**Scope** controls where a name can be used.

A variable exists only inside the block where it is defined.

## Local variables

A variable defined inside a function is a **local variable**.

```cpp
#include <iostream>

void printValue()
{
    int value{10};
    std::cout << value << "\n";
}

int main()
{
    printValue();
    // std::cout << value << "\n"; // Error: value is out of scope

    return 0;
}
```

`value` belongs to `printValue`. `main` cannot use it.

## Parameters are local too

Parameters are local variables created for a function call.

```cpp
#include <iostream>

void printDouble(int value)
{
    std::cout << value * 2 << "\n";
}

int main()
{
    int number{21};

    printDouble(number);
    return 0;
}
```

`number` lives in `main`. `value` lives in `printDouble`.

When `printDouble(number)` runs, the value of `number` is copied into `value`.

## Block scope

Blocks also create scope.

```cpp
#include <iostream>

int main()
{
    if (true)
    {
        int value{42};
        std::cout << value << "\n";
    }

    // std::cout << value << "\n"; // Error: value is out of scope

    return 0;
}
```

The variable `value` is created inside the `if` block. It is destroyed when the block ends.

## Going out of scope

When execution leaves a block, local variables in that block are destroyed.

You will often hear:

- a variable is **in scope** if you can use it here
- a variable is **out of scope** if you cannot use it here
- a variable **goes out of scope** when its lifetime ends

## Same value, different names

Arguments and parameters can have different names.

```cpp
#include <iostream>

int square(int value)
{
    return value * value;
}

int main()
{
    int number{5};
    int result{square(number)};

    std::cout << result << "\n";
    return 0;
}
```

`number` and `value` are not the same variable. The value `5` is copied from `number` into `value`.

> NOTE: A function with parameters lives in its own small world. It receives values, does its job, and then its local variables disappear.

## Shadowing

It is legal to reuse a name in an inner scope, but it can be confusing.

```cpp
#include <iostream>

int main()
{
    int value{10};

    if (true)
    {
        int value{20};
        std::cout << value << "\n";
    }

    std::cout << value << "\n";
    return 0;
}
```

This prints:

```
20
10
```

The inner `value` temporarily hides the outer `value`.

> PREFERENCE: Avoid reusing the same name in nested scopes while you are learning. Clear names make scope easier to reason about.

## Try it now

### Exercise 1: Fix the scope error

Prompt: Move or return the value so `main` can print it.

```cpp
#include <iostream>

void makeNumber()
{
    int number{42};
}

int main()
{
    makeNumber();

    // TODO: Print 42 without using number out of scope.

    return 0;
}
```

### Exercise 2: Trace scope

Prompt: Before running, predict what this program prints.

```cpp
#include <iostream>

void printValue(int value)
{
    value += 10;
    std::cout << value << "\n";
}

int main()
{
    int value{5};

    printValue(value);
    std::cout << value << "\n";

    return 0;
}
```
