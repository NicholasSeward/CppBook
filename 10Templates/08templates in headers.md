# Templates in Headers

Normal functions split cleanly between `.h` (declaration) and `.cpp` (definition). Templates break that habit.

## Forward declaration is not enough

For an ordinary function you might write:

```
// math.h
int add(int a, int b);

// math.cpp
int add(int a, int b) { return a + b; }
```

For a template, the compiler needs the **full pattern** at the point where it instantiates the function. A forward declaration alone does not give it enough information to generate `max<int>` or `max<double>`.

This fails when the definition stays hidden in a `.cpp` file:

```
// max.h
template <typename T>
T max(T a, T b);

// max.cpp
template <typename T>
T max(T a, T b)
{
    return a > b ? a : b;
}

// main.cpp
#include "max.h"
// linker error: undefined reference to max<int>, max<double>, etc.
```

`main.cpp` sees the declaration but the compiler never generates the bodies in `max.cpp` for the types `main` uses (unless you explicitly instantiate them, which is advanced and rare in beginner code).

## Define templates in the header

The usual fix: put the **full template definition** in the header file (or in a file the header includes).

```cpp
// @file: main.cpp
#include <iostream>
#include "max.h"

int main()
{
    std::cout << max(3, 7) << '\n';
    std::cout << max(3.5, 2.1) << '\n';
    return 0;
}

// @file: max.h
#pragma once
#include <iostream>

template <typename T>
T max(T a, T b)
{
    return a > b ? a : b;
}
```

Any `.cpp` that includes `max.h` can use `max` with any type the template supports.

> PREFERENCE: If a template function is shared across multiple `.cpp` files, define it in a `.h` header, not in a `.cpp` implementation file.

## Why headers grow

Template definitions in headers are normal in C++. Library headers like `<vector>` work the same way. The cost is larger headers and longer compile times on big projects. The benefit is correct instantiation everywhere.

You still use forward declarations for **non-template** functions. For templates, think "header-first."

## Try it now

### Exercise 1: Header-only template

Prompt: Finish `min` in `min.h` and call it from `main` with `int` and `double` arguments.

```cpp
// @file: main.cpp
#include <iostream>
#include "min.h"

int main()
{
    std::cout << min(3, 7) << '\n';
    std::cout << min(3.5, 2.1) << '\n';
    return 0;
}

// @file: min.h
#pragma once

template <typename T>
T min(T a, T b)
{
    // TODO: return the smaller of a and b
    return a;
}
```
