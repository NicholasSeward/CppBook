# Generic Programming

Template code is part of a broader idea called **generic programming**: write algorithms that work for many types while still compiling to concrete, type-safe functions.

The Standard Library uses this heavily (`std::vector<T>`, `std::sort`, algorithms in `<algorithm>`). You have already used templates without defining them.

## One pattern, many types

The goal is to express **what** the code does once:

- find the larger of two values
- swap two values
- store a sequence of elements

The compiler fills in **how** for each type at compile time.

That is different from writing everything for `dynamic` runtime typing (as in some other languages). C++ keeps strong types and generates the right code per type.

## Keep templates simple

Templates scale from a five-line `max` to very advanced metaprogramming. For this course:

- use templates when the same logic truly repeats across types
- prefer one `typename T` when possible
- reach for overloading or a non-template function when types need very different behavior

> PREFERENCE: Use templates when they make code shorter and clearer. If a template is harder to read than two small overloads, the overloads may be the better choice.

## Different numbers of template parameters

You can overload templates by arity (how many template parameters they take):

```cpp
#include <iostream>

template <typename T>
T add(T a, T b)
{
    return a + b;
}

template <typename T, typename U, typename V>
void printThree(T a, U b, V c)
{
    std::cout << a << ", " << b << ", " << c << '\n';
}

int main()
{
    std::cout << add(2, 3) << '\n';
    printThree(1, 2.5, 'x');
    return 0;
}
```

`add` uses one type. `printThree` uses three. Each template parameter list is a separate pattern.

> PREFERENCE: Keep template functions to a single `typename T` unless you have a concrete mixed-type problem to solve.

## Try it now

1. Name one Standard Library type you have used that is almost certainly a template.
2. Write one sentence describing when you would choose a template over overloading for a helper function.
