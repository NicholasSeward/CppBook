# Default Arguments

Sometimes you want one function that usually behaves one way but can be tweaked when needed.

You could write several overloaded versions:

```cpp
int rollDie();
int rollDie(int sides);
```

Default arguments are often a cleaner choice.

## The idea

A **default argument** gives a parameter a value to use when the caller leaves that argument out.

```cpp
#include <iostream>
#include <random>

int rollDie(int sides = 6)
{
    std::random_device rd;
    std::mt19937 rng{rd()};
    std::uniform_int_distribution<int> die{1, sides};

    return die(rng);
}

int main()
{
    std::cout << rollDie() << "\n";
    std::cout << rollDie(20) << "\n";

    return 0;
}
```

`rollDie()` uses the default `6`.

`rollDie(20)` passes `20` explicitly.

## Syntax rules

Default values use `=` in the parameter list:

```
int rollDie(int sides = 6)
```

Curly braces `{}` are for initialization. They do not set default parameter values.

Put parameters **without** defaults first, then parameters **with** defaults:

```cpp
void connect(const std::string& host, int port = 80);
```

This is wrong:

```cpp
void bad(int port = 80, const std::string& host);
```

A non-default parameter cannot follow a default parameter.

## Compared to many overloads

Without defaults, you might write:

```cpp
void greet();
void greet(const std::string& name);
void greet(const std::string& name, int count);
```

With defaults, one declaration can cover the common cases:

```cpp
#include <iostream>
#include <string>

void greet(const std::string& name = "Guest", int count = 1)
{
    for (int i{0}; i < count; ++i)
    {
        std::cout << "Hello, " << name << "!\n";
    }
}

int main()
{
    greet();
    greet("Ada");
    greet("Ada", 3);

    return 0;
}
```

> PREFERENCE: Use default arguments when one function mostly works one way but sometimes needs a small tweak. Use overloading when the behavior or parameter types really change.

## Defaults and forward declarations

You typically put default values on the **forward declaration**, not on both the declaration and the definition.

This will not compile:

```cpp
#include <iostream>

int multiply(int value, int factor = 2);

int multiply(int value, int factor)
{
    return value * factor;
}

int main()
{
    std::cout << multiply(5) << "\n";
    return 0;
}
```

If the default appears in the header or forward declaration, leave it off the definition in the `.cpp` file.

Think of the forward declaration as the documentation other code reads. Header files should show how to call the function.

```cpp
// @file: main.cpp
#include <iostream>
#include "math_helpers.h"

int main()
{
    std::cout << multiply(5) << "\n";
    std::cout << multiply(5, 3) << "\n";
    return 0;
}

// @file: math_helpers.h
#pragma once

int multiply(int value, int factor = 2);

// @file: math_helpers.cpp
#include "math_helpers.h"

int multiply(int value, int factor)
{
    return value * factor;
}
```

## Defaults and overloading together

You can combine default arguments with overloading.

```cpp
#include <iostream>
#include <string>

void logMessage(const std::string& message)
{
    std::cout << message << "\n";
}

void logMessage(const std::string& message, int repeatCount)
{
    for (int i{0}; i < repeatCount; ++i)
    {
        std::cout << message << "\n";
    }
}

int main()
{
    logMessage("Once");
    logMessage("Three times", 3);

    return 0;
}
```

Be careful when two overloads could both be called with no arguments.

```cpp
#include <iostream>

void foo(int value = 0);
void foo(double value = 0.0);

int main()
{
    foo();
    return 0;
}
```

`foo()` is ambiguous. Both overloads could match.

Every call must resolve to exactly one function.

## When to use defaults

Good uses:

- optional labels or prompts
- default die sides (`6`)
- default ports, flags, or counts
- optional formatting choices

Defaults are not a replacement for every overload. They work best when the missing argument has one obvious default value.

## Try it now

### Exercise 1: Repeat a message

Prompt: Give `times` a default of `1`. Call `announce("Start")` once and `announce("Go", 3)` three times.

```cpp
#include <iostream>
#include <string>

void announce(const std::string& message, int times /* TODO: default */)
{
    for (int i{0}; i < times; ++i)
    {
        std::cout << message << "\n";
    }
}

int main()
{
    // TODO: Call announce with one argument.
    // TODO: Call announce with two arguments.

    return 0;
}
```

### Exercise 2: Default in the header only

Prompt: Declare `padLeft` in the header with default width `10`. Define it in the `.cpp` file without repeating the default. `main` should call `padLeft("Hi")` and `padLeft("Hi", 6)`.

```cpp
// @file: main.cpp
#include <iostream>
#include "text_helpers.h"

int main()
{
    padLeft("Hi");
    padLeft("Hi", 6);
    return 0;
}

// @file: text_helpers.h
#pragma once
#include <string>

// TODO: Declare padLeft with default width 10.

// @file: text_helpers.cpp
#include <iostream>
#include "text_helpers.h"

void padLeft(const std::string& text, int width)
{
    // TODO: Print text in a field of width characters (pad on the left).
}
```

### Exercise 3: Spot the ambiguity

Prompt: Before compiling, explain why `run()` is ambiguous. Change the declarations so `run()`, `run(5)`, and `run(2.5)` each resolve to exactly one function.

```cpp
#include <iostream>

void run(int steps = 1);
void run(double steps = 1.0);

int main()
{
    run();
    run(5);
    run(2.5);
    return 0;
}
```
