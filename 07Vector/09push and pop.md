# Push and Pop

Once a vector has room for elements, you can add and remove values at the ends.

## `push_back`

`push_back` adds a new element at the end of the vector.

```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> values{10, 20, 30};

    values.push_back(40);
    values.push_back(50);

    for (int value : values)
    {
        std::cout << value << " ";
    }

    std::cout << "\n";
    return 0;
}
```

## `pop_back`

`pop_back` removes the last element.

```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> values{10, 20, 30, 40, 50};

    values.pop_back();

    for (int value : values)
    {
        std::cout << value << " ";
    }

    std::cout << "\n";
    return 0;
}
```

## `push_front` and queues

`push_front` adds to the front, but it is expensive for `std::vector` because existing elements must shift.

For queue behavior, another container type such as `std::list` is often a better fit.

## Amortized cost

Most `push_back` calls are very fast. Occasionally the vector must reallocate and copy everything, which is slower. Over many insertions, the average cost stays low.

> NOTE: Hidden costs still matter in important programs. Benchmark when performance is critical.

## Try it now

### Exercise 1: Stack behavior

Prompt: Push three values, pop one from the end, then print what remains.

```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> values;

    // TODO: Push 10, 20, and 30.
    // TODO: Pop the last value.
    // TODO: Print the remaining values.

    return 0;
}
```

### Exercise 2: Build a list from input

Prompt: Read integers until the user enters `0`, store them in a vector, then print them in reverse order using `pop_back`.

```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> values;
    int input{};

    // TODO: Read integers until 0 is entered.
    // TODO: Print the values in reverse order using pop_back.

    return 0;
}
```
