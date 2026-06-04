# Namespaces

Sometimes two things need the same name.

A **namespace** creates a named scope so those names do not collide.

## Naming collisions

This will not compile because both functions have the same name and parameter list:

```cpp
#include <iostream>

void print()
{
    std::cout << "First print\n";
}

void print()
{
    std::cout << "Second print\n";
}

int main()
{
    print();
    return 0;
}
```

The compiler does not know how to keep two identical global function names apart.

## A namespace fences off names

```cpp
#include <iostream>

namespace text_output
{
    void print()
    {
        std::cout << "Text output\n";
    }
}

namespace debug_output
{
    void print()
    {
        std::cout << "Debug output\n";
    }
}

int main()
{
    text_output::print();
    debug_output::print();

    return 0;
}
```

Both namespaces contain a function named `print`, but the full names are different:

- `text_output::print`
- `debug_output::print`

## Scope resolution operator

The `::` operator is the **scope resolution operator**.

It says which scope a name belongs to.

You have already used it:

```cpp
#include <iostream>

int main()
{
    std::cout << "Hello\n";
    return 0;
}
```

`std::cout` means `cout` inside the `std` namespace.

## `std` is a namespace

The Standard Library uses the `std` namespace.

That is why we write:

```
std::cout
std::cin
std::string
std::vector
```

This prevents Standard Library names from colliding with names in your own code.

## Avoid `using namespace std;`

Older examples often write:

```
using namespace std;
cout << "Hello\n";
```

This pulls many names from `std` into the global namespace.

That can create surprising name conflicts, especially in larger programs.

> PREFERENCE: Do not use `using namespace std;` in this book. Writing `std::` is a small cost for clearer code.

## Global namespace

Names outside any namespace are in the **global namespace**.

```cpp
#include <iostream>

void greet()
{
    std::cout << "Hello\n";
}

int main()
{
    greet();
    return 0;
}
```

Small examples often use global functions. Larger projects usually organize helper functions inside namespaces.

## Operators across languages

C++ uses several operators for name access:

- `.` for members of an object
- `->` for members through a pointer
- `::` for names inside a scope

Some languages use `.` for most of these jobs. C++ is more specific.

## Try it now

### Exercise 1: Add a namespace

Prompt: Put `print` inside a namespace named `messages` and call it from `main`.

```cpp
#include <iostream>

// TODO: Add namespace messages.
// TODO: Move print inside it.
void print()
{
    std::cout << "Hello\n";
}

int main()
{
    // TODO: Call print through the namespace.

    return 0;
}
```