# Move Semantics and rvalue References

Smart pointers rely on **transferring ownership**: one owner hands memory to another, leaving the first empty instead of making a second owner. C++ expresses that with **move semantics**, built on **rvalue references**.

## lvalues and rvalues

Every expression is either an **lvalue** or an **rvalue**:

- An **lvalue** has a name and a stable address you can refer to again: a variable like `x`.
- An **rvalue** is a temporary with no lasting home: a literal like `10`, or the result of `a + b`.

| Reference | Written | Binds to |
|-----------|---------|----------|
| **lvalue reference** | `int&` | Named objects (lvalues) |
| **rvalue reference** | `int&&` | Temporaries (rvalues) |

An **rvalue reference** (`&&`) binds to temporaries. That lets a function know it received something disposable, so it can safely **steal** its contents instead of copying:

```cpp
#include <iostream>

void inspect(int& lref)
{
    std::cout << "lvalue ref: " << lref << '\n';
}

void inspect(int&& rref)
{
    std::cout << "rvalue ref: " << rref << '\n';
}

int main()
{
    int x = 5;
    inspect(x);    // lvalue ref: 5
    inspect(10);   // rvalue ref: 10  (10 is a temporary)
    return 0;
}
```

Why is this useful? If an argument is a temporary about to be destroyed, a function can take its internals (like a heap pointer) rather than duplicating them. That is the heart of a **move**.

## `std::move`

Sometimes you have a named value (an lvalue) that you are **done with** and want to move from. **`std::move`** casts it to an rvalue reference, giving permission to move:

```cpp
#include <utility>

AutoPtr<int> b{std::move(a)};   // treat a as a temporary; steal its pointer
```

`std::move` does not move anything by itself. It just says "you may treat this as movable." After moving from `a`, leave it alone except to reassign or destroy it.

## Move constructor and move assignment

If you write your own resource-owning class, you provide a **move constructor** and **move assignment operator**. They take an rvalue reference, copy the pointer, and null out the source so only one object owns the resource:

```cpp
#include <iostream>
#include <utility>

template <typename T>
class AutoPtr
{
public:
    explicit AutoPtr(T* ptr = nullptr)
        : ptr_{ptr}
    {
    }

    ~AutoPtr()
    {
        delete ptr_;
    }

    AutoPtr(AutoPtr&& other) noexcept        // move constructor
        : ptr_{other.ptr_}
    {
        other.ptr_ = nullptr;                // source no longer owns it
        std::cout << "moved\n";
    }

    AutoPtr& operator=(AutoPtr&& other) noexcept   // move assignment
    {
        if (this != &other)
        {
            delete ptr_;
            ptr_ = other.ptr_;
            other.ptr_ = nullptr;
        }
        return *this;
    }

    AutoPtr(const AutoPtr&) = delete;          // no copying: one owner
    AutoPtr& operator=(const AutoPtr&) = delete;

    T& operator*() const { return *ptr_; }

private:
    T* ptr_;
};

int main()
{
    AutoPtr<int> a{new int{5}};
    AutoPtr<int> b{std::move(a)};   // ownership moves from a to b
    std::cout << *b << '\n';        // 5
    return 0;
}
```

After the move, `a` holds `nullptr` and `b` owns the memory. Only `b`'s destructor frees it, so there is no double free.

## Rule of three, five, and zero

These rules guide when to write the special member functions (destructor, copy/move constructor, copy/move assignment):

| Rule | Idea |
|------|------|
| **Rule of three** | If you write a destructor, copy constructor, **or** copy assignment, you probably need all three (pre-C++11). |
| **Rule of five** | With move semantics, that list grows to five (add move constructor and move assignment). |
| **Rule of zero** | Best of all: design so you need **none** of them. Let members (smart pointers, `std::vector`, `std::string`) handle resources. |

> PREFERENCE: Aim for the **rule of zero**. In everyday code you rarely write move constructors yourself; you use standard smart pointers and containers, which already implement them correctly.

## Try it now

### Exercise 1: lvalue or rvalue?

Prompt: For each expression, say whether it is an lvalue or an rvalue: (a) `count`, (b) `count + 1`, (c) `42`.

:::details Answer

(a) **lvalue** (a named variable), (b) **rvalue** (a temporary result), (c) **rvalue** (a literal).

:::

### Exercise 2: What `std::move` really does

Prompt: True or false: `std::move(x)` moves `x`'s data immediately.

:::details Answer

**False.** `std::move` only **casts** `x` to an rvalue reference, signaling that it may be moved from. The actual move happens when a move constructor or move assignment runs.

:::
