# Compiling, Linking, and Libraries

This course builds C++ with **GCC's `g++`** (or similar) and sometimes **CMake** for larger projects. Here is how the pieces fit together.

## From source to executable

Typical flow:

1. You write `program.cpp` (source).
2. The **compiler** produces object files such as `program.o` (machine code for each translation unit, not yet a full program).
3. The **linker** combines `.o` files plus **libraries** into one executable.

On Windows the executable often ends in `.exe`. On Linux and macOS it often has **no extension**, for example `a.out` or `program`.

Common compilers for C++:

- **g++** ([GCC](https://en.wikipedia.org/wiki/GNU_Compiler_Collection))
- **clang++** ([Clang](https://clang.llvm.org/), cross-platform, also used on macOS and Linux)
- **MSVC** (Microsoft Visual C++, common on Windows with Visual Studio)

Example (terminal):

```bash
g++ -o program program.cpp
./program
```

Or, for safer, more robust builds with warnings and a specific C++ standard:

```bash
g++ -std=c++17 -Wall -Wextra -o program program.cpp
./program
```

The first example is simple and works for most cases. The second enables more warnings and specifies the C++ version, which is recommended for real projects.

Note: Most IDEs handle compiling and running automatically, but it's helpful to understand these steps.

## The C++ standard library

C++ ships with a **standard library** for common tasks: strings, containers, I/O, algorithms, and more. It saves you from reinventing the wheel.

For example, `#include <iostream>` lets you use `std::cout` instead of writing low level OS calls just to print text.

## Third party libraries

Sometimes the standard library is not enough. You can:

- write the feature yourself, or
- use a **third party library**

Tools like [vcpkg](https://vcpkg.io/) are **package managers**: they download and build libraries so you can link against them.

> NOTE: If everyone uses the same popular libraries, a single security flaw ([CVE](https://en.wikipedia.org/wiki/Common_Vulnerabilities_and_Exposures)) can affect many projects at once. That is a bit like agricultural **monoculture**: one disease can threaten every identical crop. Some teams lean on more custom or diverse code bases. There is no perfect answer, but it is worth knowing why dependency choices matter.

## Building vs compiling

**Compiling** turns one `.cpp` into an object file. **Linking** wires objects and libraries together. **Building** usually means the whole pipeline (compile, link, sometimes tests or packaging).

[Visual Studio](https://visual.visualstudio.com/) includes build tools behind the scenes. This course often calls `g++` directly for clarity. We will use [CMake](https://cmake.org/) occasionally when a project has multiple files.

> NOTE: CMake generates build files; it is not a compiler. Think of it as a recipe that tells `g++` (or MSVC) what to build.