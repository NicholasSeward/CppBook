# C++ Versions and g++

C++ is old and still changing. New **standards** add features and tighten rules. Compilers let you choose which standard to target.

## Standard versions

Recent standards include:

- C++11, C++14, C++17, C++20, C++23, C++26 (in progress)

Features you may see online or from AI often assume **C++20** or **C++23**. This course targets **C++17** on purpose.

Why one or two versions back?

- Compilers and teaching environments support it widely
- Core concepts matter more than the newest syntax sugar
- Newer code can often be adapted later with small edits

NOTE: Standards are mostly **backward compatible** for well written code. Writing C++17 and compiling with a C++20 compiler usually works. The reverse (using C++20 features while asking for C++17) fails.

## What we skip on purpose

C++ is huge. A first course cannot cover every feature. We will skip many advanced tricks in C++20 and C++23 to stay focused on:

- variables, control flow, functions
- basic I/O and problem solving
- foundations that transfer to other languages

You can explore modern features after the core sticks.

## Compiler flag

Tell `g++` which standard to use:

```bash
g++ -std=c++17 -Wall -Wextra -o program program.cpp
```

- `-std=c++17` selects the language rules
- `-Wall -Wextra` enables extra warnings (helpful while learning)

Compilers can usually target different versions. Check documentation if you switch machines.

## GCC and g++

We use **GCC** (GNU Compiler Collection). The C++ front end command is **`g++`**. On some systems `clang++` is also common; concepts are the same, flags differ slightly.

NOTE: Snippets in the book UI may use another toolchain (Clang to WebAssembly). For homework and local work, assume **`g++`** unless told otherwise.