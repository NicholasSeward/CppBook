# Header and Implementation Files

Real projects usually split classes across **`.h`** (declaration) and **`.cpp`** (definition).

| File | Holds |
|------|--------|
| **`Rectangle.h`** | Class declaration: members, function signatures |
| **`Rectangle.cpp`** | Function bodies |
| **`main.cpp`** | Program entry, uses the class |

## Example layout

```cpp
// @file: main.cpp
#include "Rectangle.h"
#include <iostream>

int main()
{
    Rectangle desk{60.0, 30.0};
    std::cout << desk.area() << '\n';
    return 0;
}

// @file: Rectangle.h
#pragma once

class Rectangle
{
private:
    double width{};
    double height{};

public:
    Rectangle(double w, double h);
    double area() const;
};

// @file: Rectangle.cpp
#include "Rectangle.h"

Rectangle::Rectangle(double w, double h)
    : width{w}
    , height{h}
{
}

double Rectangle::area() const
{
    return width * height;
}
```

## The `::` scope operator

Outside the class, define members as **`ClassName::memberName`**.

```
double Rectangle::area() const
```

`Rectangle::` means "the `Rectangle` class's version of `area`."

## Forward declarations

If two classes refer to each other, you may need:

```
class Other;  // forward declaration
```

Use when headers would otherwise `#include` each other in a circle. Full definitions stay in `.cpp` files when possible.

## File naming

Name files after the class: `Rectangle.h`, `Rectangle.cpp`. One primary class per header is a common convention.

## ODR exception for class definitions

The **One Definition Rule (ODR)** says most entities may be defined only once across the program. **Class definitions** in headers are an exception: every `.cpp` that includes the header sees the same class layout. **Member function bodies** in `.cpp` files should appear **once**.

## Try it now

### Exercise 1: Move to `.cpp`

Prompt: Fill in `Circle.h`, `Circle.cpp`, and `main.cpp`. Declare `Circle` in the header (private `radius`, constructor, `area() const`). Define the constructor and `area()` in the `.cpp` using `::`. `main` should build a circle with radius `2.0` and print its area.

```cpp
// @file: main.cpp
#include "Circle.h"
#include <iostream>

int main()
{
    Circle c{2.0};
    std::cout << c.area() << '\n';
    return 0;
}

// @file: Circle.h
#pragma once

// TODO: declare class Circle

// @file: Circle.cpp
#include "Circle.h"

// TODO: define Circle::Circle and Circle::area
```