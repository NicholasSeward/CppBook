# Explicit Calls and Deduction

When you call a template function, you can let the compiler **deduce** the type from the arguments, or you can **tell it** the type explicitly.

## Template argument deduction

Most of the time you call a template like a normal function:

```cpp
#include <iostream>

template <typename T>
T max(T a, T b)
{
    return a > b ? a : b;
}

int main()
{
    std::cout << max(3, 7) << '\n';       // T deduced as int
    std::cout << max(3.5, 2.1) << '\n';   // T deduced as double
    return 0;
}
```

The compiler looks at the arguments and picks `T`. This is **template argument deduction**. It feels similar to overload resolution picking the best match.

## Explicit type arguments

You can also write the type in angle brackets after the function name:

```cpp
#include <iostream>

template <typename T>
T max(T a, T b)
{
    return a > b ? a : b;
}

int main()
{
    std::cout << max<int>(3, 7) << '\n';
    std::cout << max<double>(3, 7) << '\n';
    return 0;
}
```

Both calls pass `int` literals, but `max<double>(3, 7)` forces `T` to be `double`. The comparison and return use floating-point `max`.

That is something overloads cannot do as directly. With overloads you only get the version whose parameter types match. With templates you can request a specific instantiation.

## When explicit calls help

Explicit `max<int>(...)` is useful when:

- deduction would pick the wrong type
- you want a wider or narrower type than the literals suggest
- you are teaching or debugging which version was generated

For simple calls like `max(3, 7)`, deduction is enough.

## Deduction limits

Both arguments must agree on `T` for `max(T a, T b)`:

```cpp
max(3, 3.5);  // error: T cannot be both int and double
```

The next chapter shows how a second type parameter fixes that.

## Try it now

### Exercise 1: Deduction vs explicit

Prompt: Predict the output types, then run. Add `max<double>(2, 5)` and notice the result prints as a floating-point value.

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
    std::cout << max(2, 5) << '\n';
    std::cout << max<double>(2, 5) << '\n';
    return 0;
}
```
