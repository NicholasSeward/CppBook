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

If you write **any** constructor yourself, the compiler **does not** generate a default unless you ask:

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
        : Widget{0}  // explicitly provide default via delegation
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

> PREFERENCE: Prefer a constructor that sets sensible initial state over "default construct then call five setters." Compare:

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

One constructor can call another in the same class:

```cpp
#include <iostream>
#include <string>

class User
{
private:
    std::string name;
    int id{};

public:
    User()
        : User{"guest", 0}
    {
    }

    User(std::string userName, int userId)
        : name{std::move(userName)}
        , id{userId}
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
    guest.print();
    return 0;
}
```

The delegating constructor must list the other constructor in the initializer list. Avoid duplicate initialization logic.

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

Use the two-constructor `Greeter` example as a model, or `= default` plus an initializer list.
