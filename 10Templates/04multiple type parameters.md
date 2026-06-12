# Multiple Type Parameters

Sometimes one type parameter is not enough. A function may need two (or more) independent types.

## Two type parameters

```cpp
#include <iostream>

template <typename T, typename U>
auto max(T a, U b)
{
    return a > b ? a : b;
}

int main()
{
    std::cout << max(3, 3.5) << '\n';
    std::cout << max(3.5, 3) << '\n';
    return 0;
}
```

`T` matches the type of `a`. `U` matches the type of `b`. Mixed calls like `max(3, 3.5)` compile.

## Ambiguous matches still happen

Templates do not remove every conflict. You can still get errors when the compiler cannot pick one clear version, especially if you also have overloads or multiple templates that fit the same call.

When that happens:

- simplify the call (make both arguments the same type)
- add an explicit type argument: `max<double>(3, 3.5)`
- use two type parameters so each argument keeps its own type

## Return types with two parameters

For `max(T, U)`, the return type might be `int`, `double`, or something else depending on `T` and `U`. In C++14 and later, `auto` return type deduction lets the compiler figure out the return type from the `return` statement.

Older style required you to spell the return type yourself, which gets heavy quickly. That is one reason multi-parameter templates can feel harder than they are worth in small programs.

## C++20 `auto` parameters

C++20 allows abbreviated templates:

```
template <typename T>
auto max(T a, T b) { return a > b ? a : b; }

auto max(auto a, auto b) { return a > b ? a : b; }
```

The second form means "make a template parameter for each `auto` parameter." It is concise, but the errors can still be verbose.

> PREFERENCE: In this course, prefer `template <typename T>` with one type parameter when one type is enough. Add `U` only when mixed-type calls are a real requirement.

## Try it now

### Exercise 1: Mixed types

Prompt: Call `max` with an `int` and a `double` in both orders. Confirm both compile and print the larger value.

```cpp
// @file: main.cpp
#include <iostream>

template <typename T, typename U>
auto max(T a, U b)
{
    return a > b ? a : b;
}

int main()
{
    // TODO: max(4, 4.5)
    // TODO: max(4.5, 4)
    return 0;
}
```
