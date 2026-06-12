# Templates With Overloading

Templates and overloaded functions can coexist. The combination is powerful and easy to confuse.

## Template plus a non-template overload

```cpp
#include <iostream>

template <typename T>
T max(T a, T b)
{
    return a > b ? a : b;
}

int max(int a, int b)
{
    std::cout << "int overload\n";
    return a > b ? a : b;
}

int main()
{
    std::cout << max(3, 7) << '\n';          // int overload
    std::cout << max(3.5, 2.1) << '\n';      // template: double
    std::cout << max<int>(3, 7) << '\n';     // template: int (explicit)
    return 0;
}
```

- `max(3, 7)` can call the plain `int` overload (non-template functions can win when they are an exact match).
- `max<int>(3, 7)` **forces** the template version even when an overload exists.

> PREFERENCE: Avoid mixing templates and overloads for the same name unless you have a clear reason. If the template already covers the type, extra overloads often add surprise.

## Special behavior for one type

You can give a specific type custom logic with a **template specialization** (full specialization for a concrete type):

```cpp
#include <iostream>
#include <string>

template <typename T>
T announce(T value)
{
    std::cout << "generic: " << value << '\n';
    return value;
}

template <>
int announce(int value)
{
    std::cout << "special int: " << value << '\n';
    return value;
}

int main()
{
    announce(3.5);
    announce(42);
    return 0;
}
```

The generic template runs for `double`. The `template <>` version runs for `int`.

## Mix template types and regular parameters

Template parameters can appear with normal function parameters:

```cpp
#include <iostream>

template <typename T>
void printRepeated(T value, int count)
{
    for (int i{0}; i < count; ++i)
    {
        std::cout << value << ' ';
    }
    std::cout << '\n';
}

int main()
{
    printRepeated('*', 5);
    printRepeated(7, 3);
    return 0;
}
```

`T` is deduced from the first argument. `count` is always an `int`.

## Default arguments on non-template parameters

Defaults work on ordinary parameters the same as in non-template functions:

```cpp
#include <iostream>

template <typename T>
void show(T value, int times = 1)
{
    for (int i{0}; i < times; ++i)
    {
        std::cout << value;
    }
    std::cout << '\n';
}

int main()
{
    show('A');
    show('B', 3);
    return 0;
}
```

You cannot default a `typename T` parameter the same way without more advanced syntax. In beginner code, defaults usually belong on normal parameters like `int times`.

## Try it now

### Exercise 1: See which `max` runs

Prompt: Run as-is. Then add `max<int>(3, 7)` and compare output to `max(3, 7)`.

```cpp
// @file: main.cpp
#include <iostream>

template <typename T>
T max(T a, T b)
{
    std::cout << "template\n";
    return a > b ? a : b;
}

int max(int a, int b)
{
    std::cout << "int overload\n";
    return a > b ? a : b;
}

int main()
{
    std::cout << max(3, 7) << '\n';
    std::cout << max(3.5, 2.0) << '\n';
    return 0;
}
```
