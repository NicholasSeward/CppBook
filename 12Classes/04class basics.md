# Class Basics

A **`class`** is a user-defined type, like a `struct`. In C++ they are almost the same feature with different **default access**.

| | `struct` | `class` |
|---|----------|---------|
| Default member access | `public` | `private` |
| Typical use in this book | Plain data grouping | Data + constructor + member functions |

> NOTE: C++ was originally described as "C with classes." Most of the STL is implemented with classes.

## Three parts of a typical class

Most classes you write need three ideas:

| Part | Role | Example (`Rectangle`) |
|------|------|------------------------|
| **Data members** | What makes *this* object different from others of the same type | `width`, `height` |
| **Constructor** | How the object is **born** and members get initial values | `Rectangle(double w, double h)` |
| **Member functions** | Read, write, or compute using those members | `area()`, `setWidth()` |

You do not store facts that every object of the type already shares. All rectangles have 90° corners; you do not need a `angle` field. The name `Rectangle` carries that assumption.

A function that neither reads nor writes the object's members probably belongs elsewhere (a free function or another type).

## Anatomy of a class (sketch)

```
class Rectangle
{
private:
    double width;      // data members
    double height;

public:
    Rectangle(double w, double h);   // constructor

    double area() const;             // member functions
    void setWidth(double w);
};
```

- **`class`** keyword starts the definition.
- **`private:`** section: only member functions (and friends, later) can touch these.
- **`public:`** section: the **interface** callers use.
- Trailing **`;`** after the closing `}` (same rule as `struct`).

## Why `{}` initialization fails on a private class

With a public struct, brace initialization works directly:

```cpp
#include <iostream>

struct OpenRect
{
    double width{};
    double height{};
};

int main()
{
    OpenRect r{4.0, 5.0};
    std::cout << r.width << ' ' << r.height << '\n';
    return 0;
}
```

With a **private** class, the same brace syntax calls a **constructor** (once you define one):

```cpp
#include <iostream>

class Rectangle
{
private:
    double width{};
    double height{};

public:
    Rectangle(double w, double h)
        : width{w}
        , height{h}
    {
    }

    double area() const
    {
        return width * height;
    }
};

int main()
{
    Rectangle r{4.0, 5.0};  // constructor, not direct member fill
    std::cout << r.area() << '\n';
    return 0;
}
```

This fails when you only declare private members and never add a constructor:

```cpp
#include <iostream>

class Box
{
    int value{};  // private by default
};

int main()
{
    Box b{};  // error: no accessible constructor
    return 0;
}
```

## Class vs instance

- **`Rectangle`** (the class) is the **blueprint** or **type**. Think "classification" or "class of thing."
- **`r`** (a variable of type `Rectangle`) is an **object** or **instance**: one concrete rectangle in memory.

Since you have seen unit testing: the **class** is often the **unit** you test. You construct objects, call methods, and check results.

## Minimal working class

```cpp
#include <iostream>

class Counter
{
private:
    int count{};

public:
    Counter()
        : count{0}
    {
    }

    void increment()
    {
        ++count;
    }

    int value() const
    {
        return count;
    }
};

int main()
{
    Counter c{};
    c.increment();
    c.increment();
    std::cout << c.value() << '\n';
    return 0;
}
```

Everything outside `Counter` uses `increment()` and `value()`. `count` stays private.

Next section builds a full **`Rectangle`** class and explains **`this->`**.
