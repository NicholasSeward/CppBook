# Objects and Struct Behavior

An **object** is a value that combines **properties** (data) and **behavior** (operations on that data). You have already grouped data with `struct`. The next step is to put functions **inside** the type.

## Structs as state

Most of your struct examples so far were **state only**: names, scores, numerators, coordinates.

```cpp
#include <iostream>

struct Point
{
    double x{};
    double y{};
};

int main()
{
    Point origin{0.0, 0.0};
    std::cout << origin.x << ", " << origin.y << '\n';
    return 0;
}
```

That is normal. Structs are a fine way to represent "this thing has these fields."

## Adding behavior to a struct

You can define **member functions** inside a struct. They receive the object automatically (you will see `this` soon).

```cpp
#include <cmath>
#include <iostream>

struct Point
{
    double x{};
    double y{};

    double distanceFromOrigin() const
    {
        return std::sqrt(x * x + y * y);
    }
};

int main()
{
    Point p{3.0, 4.0};
    std::cout << "Distance: " << p.distanceFromOrigin() << '\n';
    return 0;
}
```

`p.distanceFromOrigin()` uses `p`'s `x` and `y` without passing them as extra arguments. The data and the logic that belongs to that data sit in one place.

> NOTE: `const` after the parameter list means the function promises not to modify the object's members. More on that in a later section.

## Why not free functions forever?

You *could* write `distanceFromOrigin(p)` as a free function. Member functions shine when:

- The operation naturally belongs to the type ("a point knows its distance from the origin")
- You want callers to discover behavior through the object (`p.distanceFromOrigin()`)
- You are building toward **encapsulation** (hiding some data, exposing only safe operations)

Structs default to **public** members. Anyone can still write `p.x = -999`. That is fine for simple data bundles. When invalid states matter (negative width, broken invariants), you will want **`class`** and **private** data.

## Try it now

### Exercise 1: Member function on a struct

Prompt: Add a member function `perimeter()` to this `Rectangle` struct. It should return `2 * (width + height)`.

```cpp
#include <iostream>

struct Rectangle
{
    double width{};
    double height{};

    // TODO: add perimeter()
};

int main()
{
    Rectangle r{4.0, 5.0};
    std::cout << "Perimeter: " << r.perimeter() << '\n';
    return 0;
}
```

Expected output: `Perimeter: 18`
