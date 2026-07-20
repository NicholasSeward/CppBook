# Dangling Pointers and Memory Leaks

Manual memory has two classic hazards: using memory after you released it (**dangling pointers**), and never releasing it (**memory leaks**). Both are easy to cause and worth recognizing even though modern C++ helps you avoid them.

## Dangling pointers

A **dangling pointer** points at memory you no longer own (usually after `delete`, or to a local that has gone out of scope). Reading or writing through it is **undefined behavior**: it might work, might print garbage, might crash, or might quietly corrupt other data.

```cpp
int* p = new int{10};
delete p;          // memory released
std::cout << *p;   // DANGER: p is dangling, undefined behavior
```

> PROTIP: Set a pointer to **`nullptr`** right after `delete`. A null pointer is easy to test for, and using it fails loudly instead of silently corrupting memory.

A `nullptr` reads as `false` in a condition, so you can guard access:

```cpp
#include <iostream>

int main()
{
    int* p = new int{7};

    if (p != nullptr)
    {
        std::cout << *p << '\n';
    }

    delete p;
    p = nullptr;

    delete p;   // safe: deleting nullptr does nothing
    return 0;
}
```

Two rules that example shows:

- **Deleting `nullptr` is safe** and does nothing.
- **Deleting the same real pointer twice** is a **double free**, which is undefined behavior. Setting the pointer to `nullptr` after the first `delete` turns a dangerous double free into a harmless no-op.

### Ways pointers dangle by accident

- Returning the address of a **local** variable (its stack frame is gone when the function returns).
- Keeping a pointer to a `std::vector` element after the vector grows (it may move its data to new heap memory).
- Two pointers to the same object, then deleting through one and using the other.

## Memory leaks

Forgetting a `delete` for a `new` is a **memory leak**: the memory stays reserved but you have lost the only pointer to it, so it can never be freed.

A single small leak often does no visible harm; it might take days or weeks to matter. The real danger is the cumulative effect of many leaks across a long-running program (or many programs), which can slowly starve a system of memory.

You do not need to stress about this as a beginner, but you should know:

- Tools can find leaks for you: **Valgrind**, **AddressSanitizer / LeakSanitizer** (`-fsanitize=address`), and **Dr. Memory**, among others.
- The best defense is to **not write `new` / `delete` at all**. Use `std::vector`, `std::string`, and smart pointers so cleanup is automatic. The next section shows the mechanism that makes that possible.

## Try it now

### Exercise 1: Spot the dangling pointer

Prompt: What is wrong with this code, and what could happen when it runs?

```cpp
int* p = new int{3};
delete p;
std::cout << *p << '\n';
```

:::details Answer

`p` is **dangling**: the memory was released by `delete`, so `*p` reads memory you no longer own. That is **undefined behavior** (it might print `3`, print garbage, or crash). Setting `p = nullptr;` after `delete` would at least make the misuse fail loudly.

:::

### Exercise 2: Leak or not?

Prompt: Does this function leak? If so, how would you fix it?

```cpp
void process()
{
    int* buffer = new int[100];
    // ... use buffer ...
}
```

:::details Answer

**Yes**, it leaks: `buffer` is never freed, and when `process` returns the only pointer to that heap memory is lost. Add `delete[] buffer;` before returning, or better, use a `std::vector<int> buffer(100);` that frees itself.

:::

### Exercise 3: Double free

Prompt: Why is the second `delete` dangerous, and what one line prevents it?

```cpp
int* p = new int{1};
delete p;
delete p;   // problem
```

:::details Answer

Deleting the same real pointer twice is a **double free** (undefined behavior). Writing `p = nullptr;` after the first `delete` makes the second `delete` a harmless no-op.

:::
