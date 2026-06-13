# STL Algorithms and std::sort

Reimplementing every classic algorithm would be wasteful. The C++ **Standard Library** ships a collection of **algorithms** in `<algorithm>` that work on containers through iterators.

> PREFERENCE: Reach for STL algorithms before writing your own loop when the name matches the job. Less code, fewer bugs.

## std::sort basics

`std::sort` needs a range: where to start and where to stop. For a whole `vector`, you pass `begin()` and `end()`:

```cpp
#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> values{5, 1, 4, 3, 8, 2, 6, 7};

    std::sort(values.begin(), values.end());

    for (int n : values)
    {
        std::cout << n << ' ';
    }
    std::cout << '\n';

    return 0;
}
```

That replaces the bubble sort loops with one library call. On large data, the library version is dramatically faster.

The library may pick different internal strategies (quicksort, mergesort, introsort, etc.) depending on the type and size. You usually choose **what** to do, not **which** low-level sort runs.

## Wait: what are begin and end?

We used `values.begin()` and `values.end()` above without explaining them.

- `begin()` marks where to **start** reading or sorting.
- `end()` marks where to **stop**. It points **past** the last element, not at it.

That pair shows up in almost every STL algorithm. The next sections cover **iterators** properly: what they are, how to loop with them, and when they break after you change a container.

For now, copy the pattern: `std::sort(container.begin(), container.end())` sorts the whole container.

## Try it now

### Exercise 1: Sort names

Prompt: Fill a `vector<string>` with three names out of order, sort with `std::sort`, print one per line.

```cpp
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int main()
{
    std::vector<std::string> names{"Zara", "Ada", "Mo"};

    // TODO: std::sort and print

    return 0;
}
```
