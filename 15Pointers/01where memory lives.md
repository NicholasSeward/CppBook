# Where Your Data Lives: Static, Stack, and Heap

Every value in your program lives somewhere in memory. Understanding **where** helps you reason about lifetime: when memory appears, and when it goes away.

## Three kinds of storage

| Storage | Who manages it | Lifetime |
|---------|----------------|----------|
| **Static / global** | The compiler | The entire program run |
| **Stack** | Automatic | While the function call is active |
| **Heap** | **You** (via `new` / `delete`) | Until you release it |

- **Static / global** memory holds globals and `static` variables. It exists from program start to program end.
- **Stack** memory is automatic. Each function call gets a frame for its local variables. When the function returns, its frame is popped and those locals are gone. You do nothing to clean them up.
- **Heap** memory is a large pool you request from at run time and must give back yourself. The next sections cover how.

```cpp
#include <iostream>

int globalCounter = 0;   // static/global storage

void demo()
{
    int localValue = 5;  // stack storage, gone when demo() returns
    std::cout << localValue << '\n';
}

int main()
{
    demo();
    std::cout << globalCounter << '\n';
    return 0;
}
```

## Why use the heap?

Two reasons:

1. You do **not know the size** at compile time.
2. You want to **control when** memory is allocated and freed, independent of function calls.

Static and stack memory both need their size known at compile time, and both are cleaned up automatically. The heap trades that convenience for flexibility.

> NOTE: The stack is small (often around 1 MB, depending on the system). Large arrays or deep recursion can overflow it. The heap is much larger, which is another reason big data goes there.

## You already use the heap

You might think: a `std::vector` grows and shrinks, so its size is not known at compile time. How does that work?

A `std::vector` keeps a small bookkeeping part on the **stack** (size, capacity, and a pointer), but the actual elements live in a chunk of **heap** memory that the vector allocates and frees for you. You never call `new` or `delete`; the vector does it internally.

**That is the model we want.** Let objects manage their own memory. The next few sections show the raw `new` / `delete` machinery so you understand what containers and smart pointers do under the hood, but in real code you should rarely write `new` and `delete` yourself.

> NOTE: Some systems avoid the heap entirely. NASA's "Power of 10" rules for safety-critical code forbid dynamic allocation after startup, because a slow memory leak on a spacecraft could be catastrophic. They use generously sized fixed buffers instead.

## Try it now

### Exercise 1: Name the storage

Prompt: For each variable, name where it lives: static/global, stack, or heap.

1. A `static int callCount;` inside a function.
2. A local `double total{};` inside `main`.
3. The elements a `std::vector<int>` stores.

:::details Answer

1. **Static/global** (persists for the whole program).
2. **Stack** (gone when `main` returns).
3. **Heap** (the vector allocates them; the vector's own bookkeeping sits on the stack).

:::

### Exercise 2: Why the heap?

Prompt: You need to read an unknown number of scores from a file into memory. Which storage fits, and why?

:::details Answer

The **heap**, because the count is not known at compile time. In practice you would use a **`std::vector`**, which uses the heap for you.

:::
