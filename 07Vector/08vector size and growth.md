# Vector Size and Growth

A vector can grow and shrink while your program runs.

## `resize`

`resize` changes how many elements the vector currently holds.

```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> values{10, 20, 30};

    std::cout << "Before resize: " << values.size() << "\n";

    values.resize(5);

    std::cout << "After resize: " << values.size() << "\n";
    std::cout << "First value: " << values.at(0) << "\n";
    return 0;
}
```

If `resize` makes the vector larger and new slots need a value, pass a second argument to set the default.

```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> values{10, 20, 30};

    values.resize(6, 99);

    for (int value : values)
    {
        std::cout << value << " ";
    }

    std::cout << "\n";
    return 0;
}
```

## `capacity` vs `size`

- `size()` tells you how many elements are currently stored
- `capacity()` tells you how much space is reserved

You can only index valid elements with `size()`, not `capacity()`.

## `reserve`

If you know you will add many values soon, `reserve` can grow the capacity ahead of time and avoid repeated reallocations.

```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> values;

    values.reserve(1000000);

    std::cout << "Capacity after reserve: " << values.capacity() << "\n";
    std::cout << "Size after reserve: " << values.size() << "\n";
    return 0;
}
```

## Stack and queue behavior

Two common ways to use a collection are as a **stack** or a **queue**. The difference is which end you add to and which end you remove from.

### Stack (LIFO)

A **stack** is **last in, first out** (LIFO).

Think of a stack of plates. You add a plate on top and you take a plate from the top. The last plate you put down is the first one you pick up.

With a `std::vector`, you get stack behavior by adding and removing at the **back**:

- `push_back` adds on top
- `pop_back` removes from the top

That is fast because the vector does not need to shift other elements.

### Queue (FIFO)

A **queue** is **first in, first out** (FIFO).

Think of a line at a store. The first person in line is the first person served. New people join at the back.

Queue behavior means adding at one end and removing from the **other** end. For a vector, adding or removing at the **front** with `insert` or `erase` is slow because every other element must shift.

For queue behavior, another container type such as `std::deque` or `std::list` is often a better fit. C++ also provides `std::queue` as a wrapper around one of those containers.

### When to use each pattern

| Pattern | Order | You add at | You remove from | Common uses |
|---------|-------|------------|-----------------|-------------|
| Stack (LIFO) | Last in, first out | One end (top) | Same end (top) | Undo/redo, browser back, nested function calls, matching brackets, depth-first search |
| Queue (FIFO) | First in, first out | Back | Front | Print jobs, task scheduling, waiting lines, breadth-first search, message buffers |

### When to use each container

| Behavior                         | Best container(s) for the job                       | Why                                                                  |
|-----------------------------------|-----------------------------------------------------|-----------------------------------------------------------------------|
| Stack (LIFO)                     | `std::vector`, `std::deque`, `std::stack`           | Fast `push_back`/`pop_back`; stack adapts to any container with these methods |
| Queue (FIFO)                     | `std::deque`, `std::list`, `std::queue`             | Fast insertion/removal at both ends; `std::queue` adapts as needed            |
| Random access                     | `std::vector`, `std::deque`                         | Fast lookup by index (O(1))                                           |
| Frequent insert/erase at front   | `std::deque`, `std::list`                           | No need to shift other elements; efficient front operations           |
| Frequent insert/erase in middle  | `std::list`                                         | Linked list supports fast insert/delete at any point in the sequence  |
| Only need back insert/remove and random access | `std::vector`               | Simplest, most efficient if only using the end and index access       |

A `std::vector` works well as a stack. It is a poor default choice for a queue when you must add or remove from the front often.

## Performance note

When a vector runs out of room, it often allocates a larger block of memory and copies the old elements into the new block. That work is hidden inside the abstraction, but it can matter in performance-sensitive programs.

> PROTIP: If you are adding many elements with `push_back`, consider calling `reserve()` first when you know the final size in advance.

## Try it now

### Exercise 1: Grow and shrink

Prompt: Start with three values, resize to five with default `0`, then print the new size and first value.

```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> values{10, 20, 30};

    // TODO: Resize to 5 elements with default value 0.
    // TODO: Print the size and the first element.

    return 0;
}
```

### Exercise 2: Reserve before a big push

Prompt: Reserve space for one million elements, then report capacity and size before adding anything.

```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> values;

    // TODO: Reserve space for 1000000 elements.
    // TODO: Print capacity and size.

    return 0;
}
```
