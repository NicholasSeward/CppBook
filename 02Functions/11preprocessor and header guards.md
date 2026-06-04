# Preprocessor and Header Guards

C++ runs a **preprocessor** before normal compilation.

The preprocessor handles lines that start with `#`.

## `#include`

You already use `#include`.

```cpp
#include <iostream>

int main()
{
    std::cout << "Hello\n";
    return 0;
}
```

`#include <iostream>` tells the preprocessor to include declarations for input and output tools such as `std::cout`.

For your own headers, use quotes:

```
#include "helper.h"
```

## Macros with `#define`

The preprocessor can also do text replacement.

```cpp
#include <iostream>

#define ANSWER 42

int main()
{
    std::cout << ANSWER << "\n";
    return 0;
}
```

Before compilation, the preprocessor replaces `ANSWER` with `42`.

This looks convenient, but macros are not normal variables. They are text substitutions.

## Why macros are dangerous

Macros can create confusing bugs because the compiler sees the replaced text, not the original name.

```
#define DOUBLE(x) x + x
```

This looks like a function, but it is not a function. It is text replacement.

> PREFERENCE: Except for `#include` and header guards, avoid preprocessor metaprogramming while learning C++. Prefer constants, functions, and normal language features.

## Preprocessor conditionals

The preprocessor also has conditionals:

```
#if
#ifdef
#ifndef
#endif
```

Older C++ headers often use them to prevent the same header from being included more than once.

## The duplicate include problem

Imagine a header that defines a type:

```cpp
// @file: main.cpp
#include "player.h"
#include "point.h"

int main()
{
    Player player{};
    return 0;
}

// @file: player.h
#include "point.h"

struct Player
{
    Point position{};
};

// @file: point.h
struct Point
{
    int x{};
    int y{};
};
```

`main.cpp` includes `point.h` directly and also indirectly through `player.h`.

Without protection, `Point` may be defined twice in the same translation unit.

## Traditional header guards

One older solution is an include guard:

```cpp
// @file: point.h
#ifndef POINT_H
#define POINT_H

struct Point
{
    int x{};
    int y{};
};

#endif
```

This says: if `POINT_H` has not been defined, define it and include the contents.

The second time the file is included, the contents are skipped.

## `#pragma once`

Modern code often uses the simpler form:

```cpp
// @file: point.h
#pragma once

struct Point
{
    int x{};
    int y{};
};
```

`#pragma once` tells the compiler to include this header only once per translation unit.

> PREFERENCE: Use `#pragma once` in this book. Traditional guards are still common in older code, so you should recognize them.

## Header files and the linker

Headers usually provide declarations.

The actual function definitions usually live in `.cpp` files.

The compiler compiles `.cpp` files separately. Then the linker connects compiled object files with each other and with library code.

You do not need to understand every detail yet. The main habit is:

- include headers
- compile `.cpp` files
- do not include `.cpp` files unless you are doing a small workaround

## Try it now

### Exercise 1: Guard a header and include it

Prompt: Add `#pragma once` to `location.h` and add the correct `#include` in `main.cpp` so the program compiles.

```cpp
// @file: main.cpp
#include <iostream>

// TODO: Include location.h.

int main()
{
    Location office{51.5, -0.1};
    std::cout << "Lat: " << office.latitude << ", Lon: " << office.longitude << "\n";
    return 0;
}

// @file: location.h
// TODO: Add #pragma once.

struct Location
{
    double latitude{};
    double longitude{};
};
```

### Exercise 2: Predict a macro

Prompt: Before compiling, predict what this program prints. Then run it and explain how the `PRINT` macro is expanded.

```cpp
#include <iostream>

#define PRINT std::cout <<

int main()
{
    PRINT "hello";
    return 0;
}
```