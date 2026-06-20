# Inline, Static, and the ODR

Large programs compile many `.cpp` files separately. The **One Definition Rule (ODR)** keeps linkers from seeing duplicate symbols for the same function or variable.

## Inline functions

**`inline`** on a function (especially in a header) tells the compiler it is OK to define the function in multiple translation units. The linker merges them.

Modern guidance: use **`inline`** on small functions defined in headers. Avoid **`static`** on free functions in headers for this purpose (old C habit).

```cpp
#include <iostream>

inline int maxInt(int a, int b)
{
    return a > b ? a : b;
}

int main()
{
    std::cout << maxInt(3, 7) << '\n';
    return 0;
}
```

Class member functions **defined inside the class body** are implicitly **`inline`**.

```cpp
#include <iostream>

class Box
{
public:
    Box(int w, int h)
        : width{w}
        , height{h}
    {
    }

    int volume() const { return width * height; }  // implicitly inline

private:
    int width{};
    int height{};
};

int main()
{
    Box b{3, 4};
    std::cout << b.volume() << '\n';
    return 0;
}
```

## Static member functions

**`static`** member functions belong to the **class**, not to one object. They cannot use non-static data members directly (no `this`).

```cpp
#include <iostream>

class MathUtil
{
public:
    static int max(int a, int b)
    {
        return a > b ? a : b;
    }
};

int main()
{
    std::cout << MathUtil::max(3, 7) << '\n';
    return 0;
}
```

Call with **`ClassName::functionName`**, not through an instance.

If a function does not need object state, ask whether it should be a **free function** in a namespace instead. `static` members are useful when the name should live with the type (`std::string` helpers, factory methods, counters shared by all instances).

## Static data members (preview)

Classes can also have **`static`** data shared by all objects (instance counts, shared config). Definition usually goes in a `.cpp` file. Details appear when you need them.

## Summary

| Keyword | Typical use |
|---------|-------------|
| **`inline`** | Small functions in headers; avoid ODR violations |
| **`static`** (member function) | Utility tied to type, no object instance required |

## Try it now

### Exercise 1: Call static helper

Prompt: Add `static bool isPositive(int n)` to `MathUtil` and print the result of `MathUtil::isPositive(-1)` and `MathUtil::isPositive(5)`.

```cpp
#include <iostream>

class MathUtil
{
public:
    // TODO: static bool isPositive(int n)
};

int main()
{
    // TODO: print two results
    return 0;
}
```

Expected: `0` then `1` (or `false` / `true` with `std::boolalpha`)
