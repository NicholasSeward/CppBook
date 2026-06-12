# Vector Costs and `pop_front`

`std::vector` is the workhorse sequence container. It is fast at the **back** and expensive at the **front** for removals.

Full vector tutorials are in [07 Vector](../07Vector/README.md). This chapter focuses on **cost tradeoffs** and what the library deliberately omits.

## How vector works (reminder)

- contiguous dynamic array
- `push_back` is amortized fast
- `at(i)` and `[i]` are O(1) random access
- `pop_back()` is O(1)

## Common vector methods

| Category | Methods |
|----------|---------|
| size / capacity | `size()`, `empty()`, `capacity()`, `clear()` |
| access | `at(i)`, `front()`, `back()` |
| add / remove end | `push_back()`, `pop_back()` |
| insert / erase | `insert()`, `erase()` |

## What vector does not provide (and why)

| Not provided | Why |
|--------------|-----|
| `pop_front()` | removing index 0 shifts all other elements left: O(n) |
| cheap `push_front()` | same shift in the opposite direction |
| O(1) lookup by value | not keyed; linear search unless you sort |

The STL names match real cost. `pop_back` is honest O(1). A `pop_front` on a vector would hide O(n) work.

## Class roster example

```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> scores{90, 85, 72};

    scores.push_back(88);
    std::cout << "Third score: " << scores.at(2) << '\n';

    for (int score : scores)
    {
        std::cout << score << ' ';
    }
    std::cout << '\n';

    return 0;
}
```

## Remove the first element (expensive)

```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> queue{10, 20, 30, 40};

    std::cout << "Before: ";
    for (int n : queue)
    {
        std::cout << n << ' ';
    }
    std::cout << '\n';

    queue.erase(queue.begin());

    std::cout << "After erase front: ";
    for (int n : queue)
    {
        std::cout << n << ' ';
    }
    std::cout << '\n';

    return 0;
}
```

After `erase(queue.begin())`:

1. element at index 0 is destroyed
2. `20`, `30`, `40` shift left
3. `size` drops by 1

For `n` elements, up to `n - 1` moves happen. Fine once. Painful inside a loop that always removes from the front.

> PROTIP: If you need frequent `pop_front`, use `std::deque` or `std::list`, not `std::vector`.

## Vector vs deque vs list (sequence pick)

| | `vector` | `deque` | `list` |
|--|----------|---------|--------|
| `[i]` / `at(i)` | O(1) | O(1) | no |
| `push_back` | fast | fast | fast |
| `pop_front` | O(n) via erase | O(1) | O(1) |
| memory | contiguous | chunked | linked nodes |

## Try it now

### Exercise 1: Front vs back removal

Prompt: Start with `{10, 20, 30}`. Remove the **back** with `pop_back()`, print, then reset and remove the **front** with `erase(begin())`, print. How many elements move in each case?

```cpp
// @file: main.cpp
#include <iostream>
#include <vector>

void printVector(const std::vector<int>& values)
{
    for (int n : values)
    {
        std::cout << n << ' ';
    }
    std::cout << '\n';
}

int main()
{
    std::vector<int> scores{10, 20, 30};

    // TODO: pop_back, print
    // TODO: reset to {10, 20, 30}, erase front, print

    return 0;
}
```
