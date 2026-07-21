# Allocating with `new` and `delete`

[Where Your Data Lives](01where%20memory%20lives.md) explained that heap memory is the pool **you** manage. The tools for that are **`new`** (take memory) and **`delete`** (give it back).

## Allocating with `new`

The `new` keyword asks the heap for memory, constructs a value there, and returns its **address** as a pointer:

```cpp
#include <iostream>

int main()
{
    int* p = new int{42};   // heap memory for one int, holding 42

    std::cout << *p << '\n';  // 42  (dereference to read the value)

    delete p;   // give the memory back
    p = nullptr;
    return 0;
}
```

What happens in the machine: `new int{42}` finds a free spot on the heap big enough for an `int`, stores `42` there, and hands back that location. The pointer `p` (itself a small stack variable) holds that heap address.

## Releasing with `delete`

Heap memory stays reserved until you release it. **For every `new`, you need exactly one `delete`.**

```
delete p;   // release the heap memory p points to
```

`delete` does **not** erase the pointer. It releases **ownership** of the memory so the system can hand it to something else later. The pointer `p` still holds the old address, but that address is no longer yours to use. (The next section covers what goes wrong when you use it anyway.)

## Arrays on the heap

`new` can allocate an array. A C-style heap array uses `new[]` and must be freed with `delete[]` (note the brackets):

```cpp
#include <iostream>

int main()
{
    int* arr = new int[3]{10, 20, 30};

    for (int i = 0; i < 3; ++i)
    {
        std::cout << arr[i] << ' ';
    }
    std::cout << '\n';

    delete[] arr;   // must match new[] with delete[]
    return 0;
}
```

> PREFERENCE: Prefer **`std::vector`** over `new[]`. It sizes itself, grows on demand, and frees its memory automatically. Raw heap arrays are shown here so you recognize them, not because you should reach for them.

## Try it now

### Exercise 1: Match every `new`

Prompt: This program leaks. Add the missing cleanup so every `new` has exactly one `delete`, and null the pointer afterward.

```cpp
#include <iostream>

int main()
{
    int* score = new int{100};
    std::cout << *score << '\n';

    // TODO: release score and set it to nullptr

    return 0;
}
```

:::details Answer

```cpp
delete score;
score = nullptr;
```

Without the `delete`, the heap `int` stays reserved after `main` loses its only pointer to it.

:::

### Exercise 2: Array cleanup

Prompt: What is wrong with freeing this array with `delete arr;`?

```
int* arr = new int[5]{};
// ...
delete arr;   // ?
```

:::details Answer

An array made with **`new[]`** must be freed with **`delete[]`** (`delete[] arr;`). Using plain `delete` on an array is undefined behavior.

:::
