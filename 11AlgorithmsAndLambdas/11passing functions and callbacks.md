# Passing Functions and Callbacks

STL algorithms often need a **helper function**: a comparison for `std::sort`, a predicate for `find_if`, or an action for `for_each`. You have already passed **named functions** that way.

This section names that pattern and introduces safer ways to store and pass callable code.

## Callbacks

A **callback** is a function you hand to another function so it can "call you back" later.

```cpp
#include <iostream>
#include <functional>

void greet()
{
    std::cout << "Hello\n";
}

void runTwice(const std::function<void()>& action)
{
    action();
    action();
}

int main()
{
    runTwice(greet);
    return 0;
}
```

`runTwice` does not know what `greet` prints. It only knows how to call something with the right signature.

> NOTE: **Functional programming** treats functions as values you can pass around. Languages such as **Haskell**, **Lisp**, **Scheme**, and **Clojure** lean on that style heavily. C++ mixes imperative code with selective functional patterns (STL algorithms, lambdas).

## Function pointers (old style)

C++ can store a function's address in a **function pointer**. The syntax is hard to read.

```cpp
#include <iostream>

void sayHi()
{
    std::cout << "Hi\n";
}

int main()
{
    std::cout << sayHi << '\n';  // address-ish value, not a friendly name

    void (*fp)(){sayHi};
    fp();
    return 0;
}
```

Printing `sayHi` does not run the function. You usually see a memory address (or something address-like), not `"Hi"`.

> PREFERENCE: Do not use raw function pointers in new code unless an older API forces you to. Prefer `std::function` or templates (or lambdas, next sections).

## `std::function`

`std::function` wraps callable code in a type that reads like a normal function type.

`#include <functional>`.

```cpp
#include <functional>
#include <iostream>

void sayHi()
{
    std::cout << "Hi\n";
}

int main()
{
    std::function<void()> action{sayHi};
    action();
    return 0;
}
```

Much clearer than `void (*)()`.

### Reading `function<...>` types

| Type | Meaning |
|------|---------|
| `std::function<void()>` | no args, no return value |
| `std::function<int(int, int)>` | two `int` args, returns `int` |
| `std::function<bool(const std::string&)>` | one string ref, returns `bool` |

That mirrors a normal function signature: return type, then arguments in parentheses.

### Callback with `std::function`

```cpp
#include <functional>
#include <iostream>

void runTwice(const std::function<void()>& action)
{
    action();
    action();
}

void ping()
{
    std::cout << "ping\n";
}

int main()
{
    runTwice(ping);
    return 0;
}
```

### Default arguments do not travel

Default parameter values belong to the **original function declaration**, not to the wrapper type.

```cpp
#include <functional>
#include <iostream>
#include <string>

void connect(const std::string& host, int port = 80)
{
    std::cout << host << ':' << port << '\n';
}

int main()
{
    std::function<void(const std::string&, int)> fn{connect};
    fn("example.com", 443);
    // fn("example.com");  // error: std::function has no default for port
    return 0;
}
```

When you store a function in `std::function`, callers must pass every argument explicitly.

## `auto` for functions and lambdas (C++17 style)

You can use `auto` to declare and store a lambda or function pointer, letting the compiler infer the type:

```cpp
#include <iostream>
#include <functional>

void runTwice(const std::function<void()>& action)
{
    action();
    action();
}

void ping()
{
    std::cout << "ping\n";
}

int main()
{
    auto action = ping;
    runTwice(action);

    auto lambdaAction = []() {
        std::cout << "lambda ping\n";
    };
    runTwice(lambdaAction);

    return 0;
}
```

Lambdas work here too. The next sections focus on them because they are the usual choice with STL algorithms.

## Try it now

### Exercise 1: `function` math callback

Prompt: Write `applyBoth(std::function<int(int,int)> op, int a, int b)` that prints `op(a, b)`.

```cpp
#include <functional>
#include <iostream>

int add(int a, int b)
{
    return a + b;
}

int main()
{
    // TODO: applyBoth with add and 3, 4
    return 0;
}
```
