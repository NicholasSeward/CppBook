# Default, Delegating, and Copy Constructors

Constructors can be **omitted**, **overloaded**, **chained**, or **copied**. C++ also generates some for you automatically.

## Default constructor

A **default constructor** takes no arguments (or all parameters have defaults). If you declare **no constructors**, the compiler generates one that default-initializes members.

```cpp
#include <iostream>

class Widget
{
private:
    int count{};

public:
    int value() const
    {
        return count;
    }
};

int main()
{
    Widget w{};
    std::cout << w.value() << '\n';
    return 0;
}
```

If you write **any** constructor yourself, the compiler **does not** generate a default unless you provide one:

```cpp
#include <iostream>

class Widget
{
private:
    int count{};

public:
    Widget(int start)
        : count{start}
    {
    }

    Widget()
        : count{0}
    {
    }

    int value() const
    {
        return count;
    }
};

int main()
{
    Widget w{};
    std::cout << w.value() << '\n';
    return 0;
}
```

Here `Widget()` sets `count` directly. Later, **Delegating constructors** shows how to forward to `Widget(int)` instead of repeating that logic.

> PREFERENCE: Prefer a constructor that sets sensible initial state over "default construct then call five setters." 

Compare:

```
Widget w{};
w.setSize(10);
w.setColor("red");
```

vs

```
Widget w{10, "red"};
```

One line at creation is clearer and harder to forget.

## Overloading and default arguments

```cpp
#include <iostream>
#include <string>

class Greeter
{
private:
    std::string message;

public:
    Greeter()
        : message{"Hello"}
    {
    }

    Greeter(std::string msg)
        : message{std::move(msg)}
    {
    }

    void print() const
    {
        std::cout << message << '\n';
    }
};

int main()
{
    Greeter a{};
    Greeter b{"Hi there"};
    a.print();
    b.print();
    return 0;
}
```

Or one constructor with defaults:

```cpp
#include <iostream>
#include <string>

class Greeter
{
private:
    std::string message;

public:
    Greeter(std::string msg = "Hello")
        : message{std::move(msg)}
    {
    }

    void print() const
    {
        std::cout << message << '\n';
    }
};

int main()
{
    Greeter a{};
    Greeter b{"Hi there"};
    a.print();
    b.print();
    return 0;
}
```

> PREFERENCE: Before adding many delegating overloads, ask whether **one constructor with default parameters** is enough.

## Delegating constructors

One constructor can **forward** to another in the **initializer list**. The target constructor runs first and owns the member initialization. The delegating constructor body runs after.

```cpp
#include <iostream>

class Widget
{
private:
    int count{};

public:
    Widget(int start)
        : count{start}
    {
    }

    Widget()
        : Widget{0}  // delegate to Widget(int)
    {
    }

    int value() const
    {
        return count;
    }
};

int main()
{
    Widget w{};
    std::cout << w.value() << '\n';
    return 0;
}
```

`Widget()` does not assign `count` itself. It calls `Widget{0}`, so the `int` constructor's logic runs in one place.

When several constructors share setup, delegation avoids copy-pasting initializer lists:

```cpp
#include <iostream>
#include <string>

class User
{
private:
    std::string name;
    int id{};

public:
    User(std::string userName, int userId)
        : name{std::move(userName)}
        , id{userId}
    {
    }

    User()
        : User{"guest", 0}
    {
    }

    User(std::string userName)
        : User{std::move(userName), 0}
    {
    }

    void print() const
    {
        std::cout << name << " (" << id << ")\n";
    }
};

int main()
{
    User guest{};
    User named{"Ada"};
    guest.print();
    named.print();
    return 0;
}
```

Both `User()` and `User(std::string)` delegate to `User(std::string, int)`. Change how new users get an `id` in that one constructor and every path picks it up.

> NOTE: A delegating constructor's initializer list must contain **only** the call to another constructor of the same class, not a mix of member initializers and delegation.

## Copy constructor

A **copy constructor** builds a new object as a copy of an existing one:

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

    Rectangle(const Rectangle& other)
        : width{other.width}
        , height{other.height}
    {
    }

    double area() const
    {
        return width * height;
    }
};

int main()
{
    Rectangle a{3.0, 4.0};
    Rectangle b{a};
    std::cout << b.area() << '\n';
    return 0;
}
```

If you do not write one, the compiler generates an **implicit copy constructor** that copies each member (member-wise copy). For simple classes with `int`, `double`, and `std::string` members, that is often enough.

```cpp
#include <iostream>

class Point
{
private:
    int x{};
    int y{};

public:
    Point(int xVal, int yVal)
        : x{xVal}
        , y{yVal}
    {
    }

    void print() const
    {
        std::cout << x << ", " << y << '\n';
    }
};

int main()
{
    Point a{1, 2};
    Point b{a};  // copy constructor (compiler-generated)
    b.print();
    return 0;
}
```

> NOTE: When classes manage raw resources (pointers, file handles), the implicit copy may be wrong. The "Rule of Three / Five" comes later. For now, simple value-like classes are fine with the implicit copy.

## Try it now

### Exercise 1: Default message

Prompt: Add a default constructor to `Greeter` so `Greeter g{};` prints `Hello` when `g.print()` runs.

```cpp
#include <iostream>
#include <string>

class Greeter
{
private:
    std::string message;

public:
    Greeter(std::string msg)
        : message{std::move(msg)}
    {
    }

    // TODO: default constructor

    void print() const
    {
        std::cout << message << '\n';
    }
};

int main()
{
    Greeter g{};  // should default to "Hello"
    g.print();
    return 0;
}
```

:::details Hint

The compiler will not generate a default constructor because `Greeter(std::string)` already exists. Add `Greeter()` with `: message{"Hello"}` or delegate to `Greeter{"Hello"}`.

:::

:::details Solution

**Reasoning:** Once you declare any constructor, you must supply a no-argument constructor yourself if you want `Greeter g{}`. Initializing `message` in that constructor avoids a separate setter call.

```cpp
Greeter()
    : message{"Hello"}
{
}
```

Or with delegation:

```cpp
Greeter()
    : Greeter{"Hello"}
{
}
```

:::
