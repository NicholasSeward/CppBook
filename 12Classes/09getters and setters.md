# Getters and Setters

**Access functions** read or write private data through the public interface.

| Name | Role |
|------|------|
| **Getter** | Returns a copy of (or read-only view of) a value |
| **Setter** | Updates a value, often with checks |

## Getters

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

    double widthValue() const
    {
        return width;
    }
};

int main()
{
    Rectangle r{4.0, 5.0};
    std::cout << r.widthValue() << '\n';
    return 0;
}
```

## Setters

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

    void setWidth(double w)
    {
        if (w > 0.0)
        {
            width = w;
        }
    }

    double widthValue() const
    {
        return width;
    }
};

int main()
{
    Rectangle r{4.0, 5.0};
    r.setWidth(6.0);
    r.setWidth(-1.0);  // rejected: width stays 6
    std::cout << r.widthValue() << '\n';
    return 0;
}
```

Setters are where you reject bad input, update cached fields, or log changes.

## Naming: `getWidth` vs `width()`

Both styles exist. This book usually:

- **Setters:** keep `set` → `setWidth(6.0)` (clearly an assignment)
- **Getters:** drop `get` → `width()` (reads like a property)

`width(6.0)` would look like you are *calling* width with an argument, not setting it. `width()` alone reads naturally as "give me the width."

## Return types for getters

| Return | When |
|--------|------|
| **By value** (`int`, `double`, small struct) | Safe default; caller gets a copy |
| **`const` reference** (`const std::string&`) | Large object; avoids copy; object must outlive use |

Returning a **non-const reference** to a private member lets callers modify hidden data and break encapsulation. Avoid that unless you deliberately expose a sub-object (advanced).

## lvalues and rvalues (short version)

- An **lvalue** is something with a name you can take the address of (a variable, a member).
- An **rvalue** is a temporary result (like `3 + 4` or the return of a function by value).

Getters that return by value produce an **rvalue** copy. That is fine for `int` and `double`. For big strings, `const std::string&` from a member is common.

## When getters dominate, consider a struct

If a class is mostly `getX` / `setX` with no real behavior or invariants, a public **`struct`** may be simpler.

**Class style (heavy for pure data):**

```cpp
#include <iostream>

class Point
{
private:
    int x{};
    int y{};

public:
    int getX() const { return x; }
    void setX(int v) { x = v; }
    int getY() const { return y; }
    void setY(int v) { y = v; }
};

int main()
{
    Point p{};
    p.setX(3);
    p.setY(4);
    std::cout << p.getX() << ' ' << p.getY() << '\n';
    return 0;
}
```

**Struct style (same data, less noise):**

```cpp
#include <iostream>

struct Point
{
    int x{};
    int y{};
};

int main()
{
    Point p{3, 4};
    std::cout << p.x << ' ' << p.y << '\n';
    return 0;
}
```

## Behavior beats blind setters

Instead of only `setHealth`, model the domain:

```cpp
#include <iostream>

class Fighter
{
private:
    int health{};

public:
    Fighter(int hp)
        : health{hp}
    {
    }

    void damage(int amount)
    {
        health -= amount;
        if (health < 0)
        {
            health = 0;
        }
    }

    void heal(int amount)
    {
        health += amount;
    }

    int healthPoints() const
    {
        return health;
    }
};

int main()
{
    Fighter hero{100};
    hero.damage(30);
    hero.heal(10);
    std::cout << hero.healthPoints() << '\n';
    return 0;
}
```

`damage` and `heal` express intent better than `setHealth(hero.healthPoints() - 30)`.

> PREFERENCE: Do not add getters and setters for every field "just in case." Expose what callers need. Smaller public interfaces are easier to test.

## Try it now

### Exercise 1: Rename getters

Prompt: Rename `getArea()` to `area()` and keep `setWidth` as the setter name. Ensure `main` still compiles.

Use the `Rectangle` pattern from earlier sections with at least `area() const`, `setWidth`, and `width()`.
