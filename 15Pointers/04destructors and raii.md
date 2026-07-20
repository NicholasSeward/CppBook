# Destructors and RAII

The safest way to handle heap memory is to **not** track `new` and `delete` by hand. Instead, let an object clean up after itself. The mechanism behind that is the **destructor**, and the pattern is called **RAII**.

## Destructors run automatically

A **destructor** is a special member function that runs automatically when an object is destroyed: it goes out of scope, or you `delete` a pointer to it.

A destructor has the class name with a leading **`~`**, takes **no arguments**, and has **no return type**:

```cpp
#include <iostream>

class IntBox
{
public:
    IntBox(int value)
        : data_{new int{value}}   // acquire heap memory
    {
        std::cout << "acquired\n";
    }

    ~IntBox()
    {
        delete data_;             // release it automatically
        std::cout << "released\n";
    }

    int get() const { return *data_; }

    IntBox(const IntBox&) = delete;             // keep the example simple
    IntBox& operator=(const IntBox&) = delete;

private:
    int* data_;
};

int main()
{
    IntBox box{5};
    std::cout << box.get() << '\n';
    return 0;   // box goes out of scope here: destructor runs, memory freed
}
```

Output:

```
acquired
5
released
```

The `delete` happens on its own when `box` leaves scope. You cannot forget it.

## RAII

This pattern has a name: **RAII** (Resource Acquisition Is Initialization). You **acquire** a resource in the constructor and **release** it in the destructor, so cleanup is tied to the object's lifetime.

RAII is not just for memory. A `std::ofstream` closes its file in its destructor; a lock releases in its destructor. Scope ends, objects die, resources tidy themselves up.

A **smart pointer** is a small class that wraps a raw pointer and calls `delete` in its destructor, exactly like `IntBox` does. That is why smart pointers and containers let you avoid manual memory management. (See [Destructors](../12Classes/18destructors.md) for more on the destructor itself.)

> PREFERENCE: Follow the **rule of zero**: design classes so their members (vectors, strings, smart pointers) handle cleanup, and you write no destructor at all. Reach for raw `new` / `delete` only when you have a specific reason.

## Try it now

### Exercise 1: Cleanup order

Prompt: Using the `IntBox` class above, create **two** boxes in `main` (`first` then `second`). Predict the order of the `released` messages.

:::details Answer

`second` is released first, then `first`. Local objects are destroyed in **reverse** order of construction, so the last one built is the first to clean up.

:::

### Exercise 2: Write a destructor

Prompt: Complete the destructor so this class frees its heap array and prints `cleaned up`.

```cpp
#include <iostream>

class Buffer
{
public:
    Buffer(int size)
        : data_{new int[size]{}}
    {
    }

    // TODO: destructor that deletes data_ and prints "cleaned up"

private:
    int* data_;
};

int main()
{
    Buffer b{10};
    return 0;
}
```

:::details Answer

```cpp
~Buffer()
{
    delete[] data_;
    std::cout << "cleaned up\n";
}
```

Because `data_` came from `new[]`, it must be freed with `delete[]`. (A real class would just use a `std::vector<int>` member and need no destructor at all.)

:::
