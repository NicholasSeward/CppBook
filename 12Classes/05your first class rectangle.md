# Your First Class: Rectangle

Here is a complete **`Rectangle`** class: private dimensions, constructor, and member functions.

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

    void setWidth(double w)
    {
        width = w;
    }

    void setHeight(double h)
    {
        height = h;
    }

    double widthValue() const
    {
        return width;
    }

    double heightValue() const
    {
        return height;
    }
};

int main()
{
    Rectangle desk{60.0, 30.0};

    std::cout << "Area: " << desk.area() << '\n';
    desk.setWidth(80.0);
    std::cout << "New area: " << desk.area() << '\n';

    return 0;
}
```

## How the dot works

In `desk.area()`, **`desk`** is the object. Inside `area()`, the compiler gives member functions access to **`desk`'s** `width` and `height` automatically. You can write `width` instead of `desk.width`.

That is the payoff of OOP syntax: the object carries its data; the member function operates on *this* object's copy of that data.

## When names collide: `this->`

If a parameter has the same name as a data member, the parameter **shadows** the member inside the function body. Use **`this->`** to reach the member (see the full example below).

`this` is a pointer to the current object. `this->width` means "this object's width."

```cpp
#include <iostream>

class Rectangle
{
private:
    double width{};
    double height{};

public:
    Rectangle(double width, double height)
        : width{width}
        , height{height}
    {
    }

    void setWidth(double width)
    {
        this->width = width;
    }

    double area() const
    {
        return width * height;
    }
};

int main()
{
    Rectangle r{4.0, 5.0};
    r.setWidth(10.0);
    std::cout << r.area() << '\n';
    return 0;
}
```

In the **constructor initializer list**, `width{width}` already disambiguates (member vs parameter). Inside the body, `this->` is the usual fix.

> PREFERENCE: Some codebases prefix data members with `m_` (for example `m_width`). There is no universal rule. This book prefers simple names (`width`, `height`) and uses `this->` when a parameter needs the same name.

## Naming conventions

| Kind | Style in this book | Example |
|------|-------------------|---------|
| Class / struct | TitleCase | `Rectangle`, `Player` |
| Data members | camelCase | `width`, `healthPoints` |
| Member functions | camelCase | `setWidth`, `area` |

Consistency matters more than which scheme you pick. Match your project and stop debating on every variable.

## Overloading and defaults on member functions

Member functions follow the same rules as free functions: you can **overload** them and give **default arguments**.

```cpp
#include <iostream>

class Cup
{
private:
    double ounces{};

public:
    Cup()
        : ounces{0.0}
    {
    }

    void fill(double amount = 8.0)
    {
        ounces += amount;
    }

    void drink(double amount)
    {
        if (amount > ounces)
        {
            ounces = 0.0;
        }
        else
        {
            ounces -= amount;
        }
    }

    void empty()
    {
        ounces = 0.0;
    }

    double percentFull(double capacity) const
    {
        if (capacity <= 0.0)
        {
            return 0.0;
        }
        return (ounces / capacity) * 100.0;
    }
};

int main()
{
    Cup mug{};
    mug.fill();           // default 8 oz
    mug.drink(3.0);
    std::cout << mug.percentFull(12.0) << "% full\n";
    mug.empty();
    std::cout << mug.percentFull(12.0) << "% full\n";
    return 0;
}
```

`fill()`, `fill(4.0)`, and overloaded names like `empty()` vs `drink()` read like verbs on the object: "mug, fill yourself; mug, drink three ounces."

## Try it now

### Exercise 1: `setHeight` with `this->`

Prompt: Add `setHeight(double height)` to `Rectangle` using `this->` to assign the member. Test with a 3×4 rectangle, set height to 10, print area.

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

    // TODO: setHeight using this->

    double area() const
    {
        return width * height;
    }
};

int main()
{
    Rectangle r{3.0, 4.0};
    // TODO: set height to 10, print area
    return 0;
}
```

Expected area after change: `30`
