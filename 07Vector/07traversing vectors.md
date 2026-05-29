# Traversing Vectors

Going through a container one element at a time is called a **traversal**.

You can traverse a vector with a standard `for` loop, a ranged-based `for` loop, or other patterns depending on what you need.

## Standard `for` loop

```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> values{10, 20, 30, 40, 50};

    for (int count{0}; count < values.size(); ++count)
    {
        std::cout << values.at(count) << " ";
    }

    std::cout << "\n";
    return 0;
}
```

This works, but it is easy to make off-by-one mistakes.

```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> values{10, 20, 30, 40, 50};

    for (int count{0}; count <= values.size(); ++count)
    {
        std::cout << values.at(count) << " ";
    }

    std::cout << "\n";
    return 0;
}
```

Here is an example where we print every pair of numbers using a standard for loop. It is easy to make an off-by-one error in this pattern: to print each current element together with the next one, you have to use `values.size() - 1` as the stopping point, so you stop one short of the end. If you go all the way to `values.size()`, you will go out of bounds. Don't worry too much if you get it wrong at first—just test the code until it works.

```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> values{10, 20, 30, 40, 50};

    for (int count{0}; count < values.size() - 1; ++count)
    {
        std::cout << values.at(count) << " ";
        std::cout << values.at(count + 1) << "\n";
    }

    std::cout << "\n";
    return 0;
}
```

> PROTIP: When you need to walk a vector and you are not sure which loop style to reach for, start with this pattern every time. Type it from muscle memory, confirm it runs, then change only what the problem needs (stop one early, step by 2, use the index in a formula, and so on).

```
for (int i{0}; i < values.size(); ++i)
{
    // use values.at(i)
}
```

## Ranged-based `for` loop

When you do not need the index, a ranged-based `for` loop is often the clearest and most readable choice.

#### Anatomy of a ranged-based `for` loop

The structure is:

```cpp
for (element_declaration : container)
{
    // code that uses 'element_declaration'
}
```

- `element_declaration` creates a new variable for each item as the loop progresses.
- `container` is any collection type (like a vector) you want to loop over.
- On each iteration, you get the next item in order, until all elements are processed.

For example:

```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> values{10, 20, 30, 40, 50};

    for (int value : values) // For each element, assign it to 'value'
    {
        std::cout << value << " "; // Use 'value' inside the loop body
    }

    std::cout << "\n";
    return 0;
}
```

In this example:
- The loop automatically visits every element in `values`.
- You do **not** have to manage indexing or worry about off-by-one errors.

> PREFERENCE: Use a ranged-based `for` loop when you do not need the index.

### Tracking the index with a ranged-based loop

Sometimes you want a ranged-based `for` loop but you also need to know which slot you are on. Keep a counter next to the loop and bump it each time through the body.

```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> values{10, 20, 30, 40, 50};

    int index{0};
    for (int value : values)
    {
        std::cout << index << ": " << value << "\n";
        ++index;
    }

    return 0;
}
```

For a `std::vector`, that counter matches the real index: `0`, then `1`, then `2`, and so on, in order.

> NOTE: This trick lines up with the index for `std::vector` because a vector is visited from start to end. Other containers are not guaranteed to do that. Some have no indices at all. When you must rely on a correct index, use the standard `for` loop with `.at(i)` instead.

`auto` lets the compiler figure out the element type for you.

```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> values{1, 2, 3, 4, 5};

    for (auto value : values)
    {
        std::cout << value << " ";
    }

    std::cout << "\n";
    return 0;
}
```

| Loop form | When to use it |
|-----------|----------------|
| `for (int i = 0; i < n; ++i)` | You need a reliable index |
| `for (auto value : container)` | You only need each value |
| `for (const auto& value : container)` | Large elements and read-only traversal |
| `for (auto& value : container)` | You need to modify each element |

## Try it now

### Exercise 1: Standard loop

Prompt: Print every value in a vector using a standard `for` loop and `.at()`.

```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> values{2, 4, 6, 8, 10};

    // TODO: Print each value on its own line.

    return 0;
}
```

### Exercise 2: Ranged-based loop

Prompt: Read five integers into a vector, then print them using a ranged-based `for` loop.

```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> values;

    // TODO: Read five integers into the vector.
    // TODO: Print them with a ranged-based for loop.

    return 0;
}
```
