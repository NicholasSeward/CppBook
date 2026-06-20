# Access Control

Classes organize members by **access level**: who is allowed to use them.

## Three levels

| Access | Meaning |
|--------|---------|
| **`public`** | Any code can use the member |
| **`private`** | Only member functions (and **friends**, later) of this class |
| **`protected`** | Like `private`, but also visible to **derived classes** (inheritance chapter) |

## Defaults: struct vs class

| Keyword | Default if you write nothing |
|---------|------------------------------|
| `struct` | `public` |
| `class` | `private` |

```cpp
#include <iostream>

struct S
{
    int a{};  // public
};

class C
{
    int a{};  // private
public:
    int b{};  // public
};

int main()
{
    S s{};
    s.a = 1;

    C c{};
    c.b = 2;
    // c.a = 1;  // error: private

    std::cout << s.a << ' ' << c.b << '\n';
    return 0;
}
```

Structs in this book are usually all-public, so we rarely write `public:` explicitly. Classes mix `private` data and `public` interface, so **label sections explicitly** even though the first chunk of a class is private by default.

## Suggested layout

This book usually orders:

1. **`private:`** data members (and sometimes private helper functions)
2. **`public:`** constructors
3. **`public:`** member functions

You may add **`private:`** helper functions below the data members when they should not be part of the public API.

```cpp
#include <iostream>

class Example
{
private:
    int value{};

    void syncInternalState()
    {
        // helper not exposed to callers
    }

public:
    Example(int v)
        : value{v}
    {
        syncInternalState();
    }

    int read() const
    {
        return value;
    }
};

int main()
{
    Example e{42};
    std::cout << e.read() << '\n';
    return 0;
}
```

## Protected (rare in this book)

`protected` helps when subclasses need access to base-class members without exposing them to the whole program. Examples: a `Shape` base class with `protected` coordinates that `Circle` and `Rectangle` reuse.

> PREFERENCE: You can omit the leading `private:` on a class and rely on the default. This book keeps it **explicit** so readers always see the boundary between hidden data and public interface.

## Optional: commented-out `private`

When learning, you might temporarily comment out `private:` and make members public to see that everything still "works" while invariants break. Do not ship code that way.

```cpp
#include <iostream>

class Rectangle
{
    // private:   // commented for experiment only
public:
    double width{};
    double height{};

    double area() const
    {
        return width * height;
    }
};

int main()
{
    Rectangle r{4.0, 5.0};
    r.width = 10.0;  // compiles because width is public
    std::cout << r.area() << '\n';
    return 0;
}
```

With `private:` disabled, outside code can corrupt state. With it enabled and setter functions in place, you control how state changes.

## Try it now

### Exercise 1: Fix access

Prompt: `health` should not be public. Move it to `private` and add a public `healthPoints() const` that returns it.

```cpp
#include <iostream>
#include <string>

class Player
{
public:
    std::string name;
    int health{};  // TODO: make private, add healthPoints()
};

int main()
{
    Player p{"Ada", 100};
    std::cout << p.name << " HP: " << p.healthPoints() << '\n';
    return 0;
}
```
