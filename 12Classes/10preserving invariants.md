# Preserving Invariants

Getters and setters are not busywork. They are hooks where you **keep objects valid**.

## Cached area example

If area is stored for speed, it must stay in sync whenever width or height changes.

```cpp
#include <iostream>

class Rectangle
{
private:
    double width{};
    double height{};
    double area{};

    void recalculateArea()
    {
        area = width * height;
    }

public:
    Rectangle(double w, double h)
        : width{w}
        , height{h}
    {
        recalculateArea();
    }

    void setWidth(double w)
    {
        width = w;
        recalculateArea();
    }

    void scale(double factor)
    {
        width *= factor;
        height *= factor;
        recalculateArea();
    }

    double areaValue() const
    {
        return area;
    }
};

int main()
{
    Rectangle r{4.0, 5.0};
    r.setWidth(10.0);
    std::cout << r.areaValue() << '\n';
    r.scale(2.0);
    std::cout << r.areaValue() << '\n';
    return 0;
}
```

`rectangle.width = 5` (if it were public) could skip `recalculateArea()`. `setWidth(5)` cannot.

## Do not leak mutable references

This compiles, but callers can bypass setter logic by modifying private data through a reference:

```cpp
#include <iostream>

class BrokenRect
{
private:
    double width{};
    double height{};

public:
    BrokenRect(double w, double h)
        : width{w}
        , height{h}
    {
    }

    double& widthRef()
    {
        return width;  // bad: exposes mutable access to private data
    }

    double area() const
    {
        return width * height;
    }
};

int main()
{
    BrokenRect r{4.0, 5.0};
    r.widthRef() = 100.0;
    std::cout << r.area() << '\n';
    return 0;
}
```

This compiles and prints `500`, but any future invariant logic in `setWidth` is skipped. Prefer returning **by value** or **`const` reference** from getters.

## Add accessors when needed

You can start with fewer public methods and add `width()` or `setWidth` when a real caller needs them. YAGNI ("you aren't gonna need it") applies to public APIs too.

## Why bother with private fields if setters exist?

Because the **setter body** is under your control. You can:

- Validate input
- Update derived fields
- Log or count mutations
- Change internal representation later without breaking callers

Encapsulation is not "hide data forever." It is "force changes through gates you own."
