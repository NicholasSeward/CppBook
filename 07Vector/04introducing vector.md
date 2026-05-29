# Introducing std::vector

`std::vector` is a dynamic array-like container from the C++ Standard Library.

It is usually the best default choice when you need a collection that can change size while the program runs.

## Creating a vector

You choose the element type inside angle brackets.

```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> values{};

    std::cout << "Empty vector size: " << values.size() << "\n";
    return 0;
}
```

You can also create a vector with values already inside it.

```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> values{10, 20, 30};

    std::cout << values.at(0) << "\n";
    return 0;
}
```

## List initialization and constructors

Curly braces `{}` can initialize a vector directly. Parentheses `()` call a constructor instead.

### One-argument constructor

The one-argument form creates a vector with a given number of elements. Each new slot is default-initialized.

```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> values(5);

    std::cout << "Size: " << values.size() << "\n";
    std::cout << "First value: " << values.at(0) << "\n";
    return 0;
}
```

This creates five `int` elements, each starting at `0`.

### Two-argument constructor

The two-argument form also sets the size, but it lets you choose the value used for every new slot.

```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> values(5, 7);

    std::cout << "Size: " << values.size() << "\n";
    std::cout << "First value: " << values.at(0) << "\n";
    return 0;
}
```

This creates five `int` elements, each initialized to `7`.

### Compare the two forms

| Form | Meaning |
|------|---------|
| `std::vector<int>(5)` | Five elements, default value `0` |
| `std::vector<int>(5, 7)` | Five elements, default value `7` |

Use the two-argument form when you want a specific starting value instead of zero.

## Try it now

### Exercise 1: Make vector

Prompt: Create a vector with the values 10, 20, and 30. Print them.

```cpp
#include <iostream>
#include <vector>

int main()
{
    // TODO: Create a vector with 10, 20, and 30.
    std::vector<int> values{};

    // TODO: Print each value.

    return 0;
}
```

### Exercise 2: Start with defaults

Prompt: Create a vector with five default values of `7`.

```cpp
#include <iostream>
#include <vector>

int main()
{
    // TODO: Create a vector with 5 elements, each initialized to 7.
    // TODO: Print the first and last values.

    return 0;
}
```
