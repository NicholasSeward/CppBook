# Introduction to Smart Pointers

Raw pointers work, but there are many ways to forget a `delete` (a [memory leak](03dangling%20pointers%20and%20memory%20leaks.md)) or to use memory after freeing it (a [dangling pointer](03dangling%20pointers%20and%20memory%20leaks.md)). If only the cleanup could happen automatically.

It can. A **smart pointer** is a class that manages dynamically allocated memory for you, using [RAII](04destructors%20and%20raii.md): it frees the memory in its destructor when it goes out of scope.

## Wrapping a raw pointer

You already saw the idea with `IntBox`. Here it is as a small **template** so it can wrap a pointer to any type. It prints when it acquires and releases memory:

```cpp
#include <iostream>

template <typename T>
class AutoPtr
{
public:
    explicit AutoPtr(T* ptr)
        : ptr_{ptr}
    {
        std::cout << "acquired\n";
    }

    ~AutoPtr()
    {
        delete ptr_;
        std::cout << "released\n";
    }

    T& operator*() const { return *ptr_; }
    T* operator->() const { return ptr_; }

    AutoPtr(const AutoPtr&) = delete;             // see the next section
    AutoPtr& operator=(const AutoPtr&) = delete;

private:
    T* ptr_;
};

int main()
{
    AutoPtr<int> p{new int{42}};
    std::cout << *p << '\n';
    return 0;   // destructor deletes the int automatically
}
```

Output:

```
acquired
42
released
```

`operator*` and `operator->` make the wrapper feel like a real pointer. The `delete` in the destructor runs on its own when `p` leaves scope.

## Do not build your own

That example is instructive, but it is **not** production quality. It does not handle ownership when you copy or move it, so you could still get double frees or dangling pointers. Solving all of that correctly takes care.

Good news: the standard library already did it. C++ ships three ready-made smart pointers:

| Smart pointer | Header | One-line summary |
|---------------|--------|------------------|
| `std::unique_ptr` | `<memory>` | One exclusive owner |
| `std::shared_ptr` | `<memory>` | Shared ownership, reference counted |
| `std::weak_ptr` | `<memory>` | Non-owning observer of a `shared_ptr` |

The rest of this chapter uses these, not a hand-rolled version.

> HISTORY: An older `std::auto_ptr` tried to do this before C++11 but had surprising copy behavior. It was deprecated and removed in favor of the modern, move-aware smart pointers above.

The mechanism that makes safe ownership transfer possible is **move semantics**, which the next section covers.

## Try it now

### Exercise 1: When does it free?

Prompt: Run the program. In what order do the three lines print (`acquired`, `hi`, `released`)? At what moment is the wrapped `int` deleted?

```cpp
// @file: main.cpp
#include "AutoPtr.h"
#include <iostream>

int main()
{
    AutoPtr p{new int{1}};
    std::cout << "hi\n";
    return 0;
}

// @file: AutoPtr.h
#pragma once

class AutoPtr
{
public:
    explicit AutoPtr(int* ptr);
    ~AutoPtr();

    int& operator*() const;
    int* operator->() const;

    AutoPtr(const AutoPtr&) = delete;
    AutoPtr& operator=(const AutoPtr&) = delete;

private:
    int* ptr_;
};

// @file: AutoPtr.cpp
#include "AutoPtr.h"
#include <iostream>

AutoPtr::AutoPtr(int* ptr)
    : ptr_{ptr}
{
    std::cout << "acquired\n";
}

AutoPtr::~AutoPtr()
{
    delete ptr_;
    std::cout << "released\n";
}

int& AutoPtr::operator*() const
{
    return *ptr_;
}

int* AutoPtr::operator->() const
{
    return ptr_;
}
```

:::details Answer

Order: **`acquired`**, then **`hi`**, then **`released`**.

The `int` is deleted when `p` goes out of scope at the end of `main` (after `return 0;`), when `AutoPtr`'s destructor runs.

:::

### Exercise 2: Which smart pointer?

Prompt: You want exactly one owner of a heap object, with automatic cleanup and no reference counting overhead. Which standard smart pointer fits?

:::details Answer

**`std::unique_ptr`** (single exclusive owner).

:::
