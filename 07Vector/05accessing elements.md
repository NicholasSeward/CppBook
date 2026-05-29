# Accessing Elements

Once a vector holds values, you need a safe way to read and change them.

## Indexing starts at zero

The first element is at index `0`, not `1`.

```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> values{10, 20, 30, 40, 50};

    std::cout << values.at(0) << "\n";
    std::cout << values.at(4) << "\n";
    return 0;
}
```

## The subscript operator `[]`

You can access elements with `[]`, just like an array.

```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> values{10, 20, 30, 40, 50};

    std::cout << values[0] << "\n";
    std::cout << values[4] << "\n";
    return 0;
}
```

The problem is that `[]` does not check bounds.

```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> values{10, 20, 30};

    std::cout << values[0] << "\n";
    std::cout << values[99] << "\n";
    return 0;
}
```

If the index is out of range, the program has undefined behavior. That can cause serious bugs that are hard to track down later.

> PREFERENCE: Do not use `[]` on vectors when you want memory-safe access. Use `.at()` instead.

> NOTE: You can override `operator[]` for your own types, but that is an advanced topic. For now, use the safe tool the library already gives you.

## Using `.at()`

`.at()` does the same job as `[]`, but it checks the index first.

```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> values{10, 20, 30, 40, 50};

    std::cout << values.at(0) << "\n";
    std::cout << values.at(4) << "\n";
    return 0;
}
```

If the vector has five elements, valid indexes are `0`, `1`, `2`, `3`, and `4`.

## Size and the last element

You can ask a vector how many elements it currently holds with `size()`.

```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> values{10, 20, 30, 40, 50};

    std::cout << "Size: " << values.size() << "\n";
    std::cout << "Last index: " << values.size() - 1 << "\n";
    std::cout << "Last value: " << values.at(values.size() - 1) << "\n";
    return 0;
}
> NOTE: The largest valid index in a vector is always one less than its size. For example, if a vector has 10 elements, the valid indexes go from 0 to 9. The last element is at index 9, not 10.

`size()` returns an unsigned value. Be careful when you subtract `1`. If the vector is empty, subtracting 1 can lead to unexpected results due to unsigned integer underflow.

Here is an example where it goes wrong:

```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> values{};  // empty vector

    std::cout << "Size: " << values.size() << "\n";
    // This will wrap around to a very large number!
    std::cout << "Last index: " << values.size() - 1 << "\n";

    // This line will throw an exception or cause undefined behavior!
    // std::cout << values.at(values.size() - 1) << "\n";
    return 0;
}
```

Output (will look something like this):
```
Size: 0
Last index: 18446744073709551615
```

Trying to use `values.at(values.size() - 1)` here causes an exception (`std::out_of_range`) because there is no element at that index.

Here is an example where it goes right by checking that the vector is not empty:

```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> values{10, 20, 30};

    if (!values.empty()) {
        int size = values.size();
        std::cout << "Last index: " << lastIndex << "\n";
        std::cout << "Last value: " << values.at(size-1) << "\n";
    } else {
        std::cout << "Vector is empty!\n";
    }

    return 0;
}
```

> Preference: If you do math with `size()`, cast it or store it as a signed integer first, just to be safe. This avoids issues with unsigned wraparound and out-of-bounds access.

## Try it now

### Exercise 1: Safe access

Prompt: Create a vector of four integers and print the first and last values with `.at()`.

```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> values{2, 4, 6, 8};

    // TODO: Print the first and last values using at().

    return 0;
}
```

### Exercise 2: Out-of-bounds check

Prompt: Try an invalid index with `.at()` and observe what happens compared to using `[]`.

```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> values{1, 3, 5};

    // TODO: Try values.at(10) and explain what happens.
    // TODO: Compare that to values[10].

    return 0;
}
```
