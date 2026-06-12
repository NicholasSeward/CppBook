# Function Template Basics

A **function template** is a blueprint. The compiler uses it to create real functions for the types you actually call.

## A simple `max` template

```cpp
#include <iostream>

template <typename T>
T max(T a, T b)
{
    return a > b ? a : b;
}

int main()
{
    std::cout << max(3, 7) << '\n';
    std::cout << max(3.5, 2.1) << '\n';
    return 0;
}
```

One template replaces the three separate overloads from the previous chapter.

## Syntax

| Piece | Meaning |
|-------|---------|
| `template <typename T>` | Start a template; `T` is a **type parameter** |
| `typename T` | Same idea as `class T` in template headers (this book uses `typename`) |
| `T max(T a, T b)` | Normal function except `T` stands for "some type" |

`T` is a placeholder, not a real type. The compiler substitutes a concrete type when you call `max`.

## What the compiler does

When you write `max(3, 7)`:

1. The compiler deduces `T` as `int`.
2. It **generates** something like an `int` version of `max` at compile time.
3. That generated function is what actually runs.

When you write `max(3.5, 2.1)`, the same pattern runs with `T` as `double`.

You do not ship one generic runtime function that checks types. You get separate compiled versions for each use.

> PROTIP: Template errors often mention long type names inside angle brackets. Read the **first** line of the error for the real mistake (wrong operator, missing `#include`, and so on).

## The usual placeholders

`T` is the normal first type parameter name. If you need more, common style is `T`, then `U`, then `V`:

```
template <typename T, typename U>
```

Pick names that help you read the code. `T` alone is fine for one type.

## Try it now

### Exercise 1: Use the template

Prompt: Add a call to `max` with two `long` values and print the result.

```cpp
// @file: main.cpp
#include <iostream>

template <typename T>
T max(T a, T b)
{
    return a > b ? a : b;
}

int main()
{
    std::cout << max(10, 20) << '\n';

    // TODO: call max with two long values

    return 0;
}
```
