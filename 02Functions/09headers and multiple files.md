# Headers and Multiple Files

As programs grow, you often split code into multiple files.

This keeps each file focused and easier to navigate.

## Why not include a `.cpp` file?

You may see code like this:

```cpp
// @file: main.cpp
#include "helper.cpp"

int main()
{
    greet();
    return 0;
}

// @file: helper.cpp
#include <iostream>

void greet()
{
    std::cout << "Hello\n";
}
```

This works in small experiments, but it throws away an important benefit of C++: compiling `.cpp` files separately.

`#include` acts like copying and pasting the included file's text into the current file.

## Better structure: header plus source

A common layout uses:

- a `.h` file for declarations
- a `.cpp` file for definitions
- `main.cpp` for the program entry point

```cpp
// @file: main.cpp
#include "helper.h"

int main()
{
    greet();
    return 0;
}

// @file: helper.h
#pragma once

void greet();

// @file: helper.cpp
#include <iostream>
#include "helper.h"

void greet()
{
    std::cout << "Hello\n";
}
```

`main.cpp` only needs to know that `greet` exists. The linker will make sure you can call the function; the definition lives in `helper.cpp`.

## Header files

Header files usually contain declarations.

```
void greet();
int add(int left, int right);
```

They tell other `.cpp` files what functions are available.

> PREFERENCE: Do not put normal function or variable definitions in headers yet. There are exceptions, but declarations are the right beginner habit.

## Include your own headers with quotes

Use angle brackets for Standard Library headers:

```
#include <iostream>
#include <vector>
```

Use quotes for headers you wrote:

```
#include "helper.h"
```

## The matching `.cpp` should include its header

If `helper.cpp` implements functions declared in `helper.h`, include the header at the top of `helper.cpp`.

```cpp
// @file: main.cpp
#include <iostream>
#include "helper.h"

int main()
{
    std::cout << add(2, 3) << "\n";
    return 0;
}

// @file: helper.h
#pragma once

int add(int left, int right);

// @file: helper.cpp
#include "helper.h"

int add(int left, int right)
{
    return left + right;
}
```

This helps catch mismatches between the declaration and definition.

## Compiling multiple files

If you compile from the terminal with `g++`, list all source files, or show with *:

```
g++ main.cpp helper.cpp -o app
```

or

```
g++ *.cpp -o app
```

`helper.h` is included by the `.cpp` files. You usually do not list headers as separate compile targets.

An IDE or build system such as CMake can manage this for you.

## Transitive includes

Sometimes one header includes another header. That can make a file compile even when it does not directly include what it uses.

Do not rely on that.

If a file uses `std::sqrt`, include `<cmath>` in that file.

Fragile style (relies on `math_header.h` to pull in `<cmath>`):

```cpp
// @file: main.cpp
#include <iostream>
#include "math_header.h"

int main()
{
    std::cout << std::sqrt(25.0) << "\n";
    return 0;
}

// @file: math_header.h
#pragma once
#include <cmath>
```

Clear style (each file includes what it uses):

```cpp
// @file: main.cpp
#include <cmath>
#include <iostream>
#include "math_header.h"

int main()
{
    std::cout << std::sqrt(25.0) << "\n";
    return 0;
}

// @file: math_header.h
#pragma once
```
> PREFERENCE: Include what you use. Every file should directly include the headers for features it uses. This avoids fragile dependencies and makes maintenance easier.

## Good header habits

- use `#pragma once`
- put declarations in headers
- put normal function definitions in `.cpp` files
- match names: `helper.h` and `helper.cpp`
- include what you use
- avoid including `.cpp` files
- keep each header and source pair focused on one job

When a function uses default arguments, put those defaults on the declaration in the header. See [Default Arguments](14default%20arguments.md).

## Try it now

### Exercise 1: Split a helper

Prompt: Put the declaration in `math_helpers.h` and the definition in `math_helpers.cpp`.

```cpp
// @file: main.cpp
#include <iostream>
#include "math_helpers.h"

int main()
{
    std::cout << triple(5) << "\n";
    return 0;
}

// @file: math_helpers.h
#pragma once

// TODO: Declare triple.

// @file: math_helpers.cpp
#include "math_helpers.h"

// TODO: Define triple.
```

### Exercise 2: Compile two files

Prompt: Write the command you would use to compile `main.cpp` and `math_helpers.cpp` into `app`.

```
TODO: g++ command here
```
