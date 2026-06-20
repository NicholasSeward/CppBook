# Encapsulation and Invariants

Member functions help organize code. They do not, by themselves, stop someone from breaking your object's rules. For that you need **encapsulation**.

## Invariants

An **invariant** is something that should **always** be true for a valid object.

Examples:

- A rectangle's stored **area** should match `width * height`
- A bank account balance should never go negative (if that is your rule)
- A percentage field should stay between 0 and 100

If any code anywhere can change member variables directly, invariants are one typo away from breaking.

## When a struct is too open

Suppose you track width, height, and cached area:

```cpp
#include <iostream>

struct Rectangle
{
    double width{};
    double height{};
    double area{};
};

int main()
{
    Rectangle r{4.0, 5.0, 20.0};

    r.width = 10.0;  // height and area unchanged

    std::cout << "Width: " << r.width << '\n';
    std::cout << "Area:  " << r.area << '\n';  // still 20, wrong

    return 0;
}
```

Nothing stopped you from changing `width` without updating `area`. The struct is **consistent by convention only**, and conventions fail under pressure.

## Encapsulation: hide data, expose operations

**Encapsulation** (in CS, almost always **data hiding**) means keeping some members **private** and forcing callers to go through **member functions**. Those functions can enforce rules before and after each change.

A **`class`** is the usual C++ tool for this. Structurally it is like a `struct`, but **members default to `private`**.

```cpp
#include <iostream>

class Rectangle
{
private:
    double width{};
    double height{};
    double area{};

    void updateArea()
    {
        area = width * height;
    }

public:
    Rectangle(double w, double h)
        : width{w}
        , height{h}
    {
        updateArea();
    }

    void setWidth(double w)
    {
        width = w;
        updateArea();
    }

    double getArea() const
    {
        return area;
    }
};

int main()
{
    Rectangle r{4.0, 5.0};
    r.setWidth(10.0);

    std::cout << "Area: " << r.getArea() << '\n';

    return 0;
}
```

`r.setWidth(10.0)` updates width **and** recalculates area. Callers cannot assign to `r.width` directly because it is private.

> NOTE: You could mark every member `public` in a class and get a struct in disguise. If everything is public, prefer `struct` for honesty. The point of `class` is controlled access.

## What you gain

| Open struct | Encapsulated class |
|-------------|-------------------|
| Fast to write for tiny examples | Slightly more syntax upfront |
| Any code can break invariants | Changes go through functions you control |
| Hard to change internals later | Easier to swap implementation behind the same interface |

We will cover `public` / `private` syntax in detail soon. For now: **`class` = struct with private-by-default**, and you use constructors plus member functions to keep objects valid.
