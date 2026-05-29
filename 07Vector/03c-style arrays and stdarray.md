# C-Style Arrays and std::array

Before `std::vector`, it helps to understand the older array styles in C and C++.

## C-style arrays

A C-style array stores elements in a fixed block of memory.

```cpp
#include <iostream>

int main()
{
    int scores[5] = {90, 88, 95, 81, 92};

    std::cout << scores[0] << " " << scores[4] << "\n";
    return 0;
}
```

Many languages use a similar syntax because C++ is built on C.

C-style arrays are the foundation of many containers in the C++ Standard Library. They can be useful in small, careful cases, but they have serious limitations for general programming.

## Problems with C-style arrays

> PREFERENCE: Do not use C-style arrays in new C++ code.

Common problems:

- Hard to resize after creation
- Size must be passed separately to functions, often as a raw pointer with no length information
- Easy to create memory bugs with out-of-bounds access
- No built-in safety checks

## std::array

The Standard Library provides `std::array`, a safer wrapper around a C-style array with a fixed size known at compile time.

```cpp
#include <iostream>
#include <array>

int main()
{
    std::array<int, 5> scores{90, 88, 95, 81, 92};

    std::cout << scores.at(0) << " " << scores.at(4) << "\n";
    return 0;
}
```

`std::array` fixes some problems of raw C-style arrays, but it still cannot grow or shrink at runtime.

## Why std::vector is the default choice here

`std::vector` can do everything `std::array` can do, and more:

- It can grow and shrink
- It works well with functions
- It supports safer access with `.at()`
- It is the usual choice for dynamic collections in this book

> PREFERENCE: Use `std::vector` for most array and list needs in this book. This book will not use `std::array`.

> NOTE: The Standard Library includes many container types. This chapter focuses on `std::vector` because it solves the problems that show up most often in beginner programs.

## Try it now

### Exercise 1: Fixed-size array

Prompt: Create a `std::array` of five integers and print the first and last values.

```cpp
#include <iostream>
#include <array>

int main()
{
    std::array<int, 5> values{10, 20, 30, 40, 50};

    // TODO: Print the first and last values.

    return 0;
}
```
