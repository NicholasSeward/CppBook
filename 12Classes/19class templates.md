# Class Templates

You have seen **function templates**. Classes can be templates too: one blueprint, many types.

## Class template

```cpp
#include <iostream>

template <typename T>
class Box
{
private:
    T value{};

public:
    Box(T initial)
        : value{initial}
    {
    }

    T get() const
    {
        return value;
    }

    void set(T v)
    {
        value = v;
    }
};

int main()
{
    Box<int> intBox{42};
    Box<double> doubleBox{3.14};

    std::cout << intBox.get() << '\n';
    std::cout << doubleBox.get() << '\n';

    return 0;
}
```

`Box<int>` and `Box<double>` are **different types**, generated from the same template.

## Template parameters on functions only

You can also template a single member or free function inside a class:

```cpp
#include <iostream>

class Printer
{
public:
    template <typename T>
    void show(const T& value)
    {
        std::cout << value << '\n';
    }
};

int main()
{
    Printer p{};
    p.show(42);
    p.show(3.14);
    p.show("hello");
    return 0;
}
```

The STL uses templates heavily (`std::vector<T>`, `std::optional<T>`, etc.).

## Definitions in headers

Template definitions usually live entirely in **headers** so the compiler can instantiate them for each `T` you use. Splitting template classes across `.h` / `.cpp` is possible but awkward; this book keeps template classes in headers until you hit explicit instantiation later.

## Try it now

### Exercise 1: `Pair` template

Prompt: Complete `Pair<T>` to hold `first` and `second` of the same type and print them.

```cpp
#include <iostream>

template <typename T>
class Pair
{
private:
    T first{};
    T second{};

public:
    Pair(T a, T b)
        : first{a}
        , second{b}
    {
    }

    void print() const
    {
        // TODO: print first and second separated by space
    }
};

int main()
{
    Pair<int> p{1, 2};
    p.print();
    return 0;
}
```

Expected: `1 2`
