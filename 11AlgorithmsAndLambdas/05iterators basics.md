# Iterators Basics

You saw `begin()` and `end()` with `std::sort` before we explained them. Here is what they actually are.

STL algorithms need a way to reach elements in a container. The story starts with a simpler idea you have seen before: **raw pointers**.

## Four ways to walk a vector

### Index loop

```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> values{10, 20, 30};

    for (int i{0}; i < values.size(); ++i)
    {
        std::cout << values.at(i) << ' ';
    }
    std::cout << '\n';

    return 0;
}
```

Works well when you need the index number.

### Range-based for loop

```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> values{10, 20, 30};

    for (int n : values)
    {
        std::cout << n << ' ';
    }
    std::cout << '\n';

    return 0;
}
```

Simplest when you only need each value. The compiler uses `begin()` and `end()` iterators behind the scenes.

### Pointer vocabulary (preview)

A type followed by `*` (for example `int*`) is a **pointer**: it holds a **memory address**, not the value itself.

| Syntax | Meaning |
|--------|---------|
| `int* p` | `p` can point at an `int` somewhere in memory |
| `&x` | address of variable `x` |
| `*p` | value stored **at** the address in `p` (**dereference**) |
| `++p` | move `p` to the **next** address (next slot in an array or vector) |

```cpp
int nums[]{10, 20, 30};
int* p{&nums[0]};       // address of first element

std::cout << *p << '\n';  // 10: value at that address
++p;                      // next address (next element)
std::cout << *p << '\n';  // 20
```

We will cover pointers and addresses properly in a later chapter. For this module, the one operation you need often is **dereference**: `*p` or `*it` means “the value here.”

### Raw pointer loop

A `std::vector` stores its elements in contiguous memory. You can get the address of the first element:

```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> values{10, 20, 30};

    int* start{&values.at(0)};
    int* pastEnd{&values.at(0) + values.size()};

    for (int* p{start}; p != pastEnd; ++p)
    {
        std::cout << *p << ' ';
    }
    std::cout << '\n';

    return 0;
}
```

- `start` holds the **address** of the first element (`&` gets that address)
- `pastEnd` holds the address **past** the last element (same idea as `end()`)
- `*p` **dereferences**: read the `int` value at address `p`
- `++p` moves to the **next address** in memory (next element)

You can also write `values.data()` instead of `&values.at(0)` for the start pointer. Both give an address into the vector's storage.

STL algorithms accept raw pointers on contiguous data. This works:

```cpp
std::sort(values.data(), values.data() + values.size());
```

So why not always use pointers?

Raw pointers do not remember which container they came from. Nothing stops you from walking past the end, keeping a pointer after the vector grows, or using pointer math on a `list` where elements are not in one memory block. Pointers are powerful but easy to misuse.

> NOTE: Full pointer rules come in a later chapter. Here, focus on dereference (`*p`) and seeing how `++p` walks forward one address at a time.

## Iterators: pointers with guardrails

An **iterator** is the STL's answer: iterator syntax mirrors pointers (`*`, `++`, `!=`), but the type is tied to the container.

| Raw pointer on `vector`        | Iterator on a container | What it does                                |
|-------------------------------|-------------------------|---------------------------------------------|
| `values.data()`                | `values.begin()`        | Address/iterator to the first element       |
| `values.data() + values.size()`| `values.end()`          | Address/iterator just past the last element |
| `*p`                          | `*it`                   | Dereference: access the current value       |
| `++p`                         | `++it`                  | Move to the next element                    |
| `--p`                         | `--it`                  | Move to the previous element                |
| `p += 2`                      | `it += 2`               | Move forward two elements                   |

Differences that matter:

- **`end()` is tied to the container's size**, not something you calculate by hand (less chance of off-by-one).
- **The same iterator loop works on `list`, `set`, and more**, not only contiguous memory.
- **Invalidation rules** still apply (next section), but the iterator type encodes which container you are walking.

Think of an iterator as a pointer wrapped in a thin safety layer: familiar operations, container-aware behavior.

> NOTE: The usual name for an iterator variable is **`it`** (short for iterator). You will see `it` in examples, library docs, and other people's code.

### Iterator loop

```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> values{10, 20, 30};

    for (auto it{values.begin()}; it != values.end(); ++it)
    {
        std::cout << *it << ' ';
    }
    std::cout << '\n';

    return 0;
}
```

- `begin()` points at the first element.
- `end()` points at the **past-the-end** slot (not the last element).
- `*it` dereferences the iterator to get the value.
- `++it` moves to the next element.

## Moving an iterator by hand

```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> values{10, 20, 30, 40, 50};

    auto it{values.begin()};
    std::cout << *it << '\n';   // 10

    ++it;
    std::cout << *it << '\n';   // 20

    it += 2;
    std::cout << *it << '\n';   // 40

    return 0;
}
```

On `vector`, iterators are often implemented as pointers under the hood. On `list` or `set`, they still support `*`, `++`, and `!= end`, but they follow links instead of jumping through one memory block.

## Why `!= end` instead of `<`?

Index loops and iterator loops use **different** stopping rules. Mixing them up causes bugs.

### Index loops: prefer `i < size`

When you have an integer index, compare against **size**:

```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> values{10, 20, 30, 40, 50, 60, 70, 80, 90, 100};

    for (int i{0}; i < values.size(); i += 3)
    {
        std::cout << values.at(i) << ' ';
    }
    std::cout << '\n';

    return 0;
}
```

`i` visits `0`, `3`, `6`, `9`. The check `i < size` still works even when the step skips over index `10`.

### Do not use `!= size` with a skip step on indices

This loop never stops:

```cpp
#include <iostream>

int main()
{
    for (int i{0}; i != 10; i += 3)
    {
        std::cout << i << ' ';
    }
    // prints 0 3 6 9 12 15 ... forever
    return 0;
}
```

`i` jumps past `10` (`9` → `12`), so `i != 10` stays true. With indices, use **`< size`**, not **`!= size`**, when you step by more than 1.

### Iterator loops: use `it != end`

The usual iterator pattern walks until you reach the **sentinel** `end()`, not until you hit a numeric limit:

```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> values{10, 20, 30, 40, 50, 60, 70, 80, 90, 100};

    for (auto it{values.begin()}; it != values.end(); it += 3)
    {
        std::cout << *it << ' ';
    }
    std::cout << '\n';

    return 0;
}
```

`end()` marks “no more elements.” You stop when `it` **reaches** that sentinel, even if you arrived by skipping (`+= 3`). You do not have to land on an exact index number.

### Why not `it < end`?

On `vector`, `it < values.end()` often works because vector iterators are **random-access** (like pointers in memory).

On `list` or `set`, iterators are **not** random-access. There is no “left of end in memory” ordering, so **`it < end` is not valid**. `it != end` works on every standard container.

| Loop style | Stopping condition | Skip steps (`+= 3`) |
|------------|-------------------|---------------------|
| Index on `vector` | `i < size` | yes |
| Index on `vector` | `i != size` | risky: can skip past size and loop forever |
| Iterator (any container) | `it != end` | yes on `vector` / `string` / `deque`; on `list`, use repeated `++` instead of `+= 3` |

> PREFERENCE: Index loop → `i < container.size()`. Iterator loop → `it != container.end()`. Do not swap those rules.

> PREFERENCE: Use a range-based for loop when you do not need the index or iterator. Use iterators when calling STL algorithms or when there is no index (for example on `std::set`).

## std::begin and std::end

While most STL containers provide `.begin()` and `.end()`, free functions `std::begin` and `std::end` are especially useful because they also work with **C-style arrays** (like `int arr[5]`), not just containers. This allows STL algorithms to operate seamlessly on both containers and traditional arrays by providing a uniform way to get iterators (or pointers) to the start and past-the-end of the sequence.

> PREFERENCE: Prefer STL containers and iterators over raw pointer loops in new code. Raw pointers still matter for C APIs and low-level work later in the course.

## Try it now

### Exercise 1: Iterator walk

Prompt: Print every other character of a string using iterators (`begin`, `end`, `+= 2`, `*`).

```cpp
// @file: main.cpp
#include <iostream>
#include <string>

int main()
{
    std::string word{"iterator"};

    // TODO: iterator loop, step by 2, print each char

    return 0;
}
```
