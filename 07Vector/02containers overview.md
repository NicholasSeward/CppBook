# Containers Overview

A **container** is a type that holds many values of the same type.

Think of a container as a labeled box that can grow or shrink while your program runs.

## Elements and indices

Elements inside a container do not have individual variable names. You access them typically by **index**.

The first element is at index `0`, the second is at index `1`, and so on.

```cpp
#include <iostream>
#include <string>
#include <vector>

int main()
{
    std::vector<std::string> words{"cat", "dog", "fish"};

    std::cout << words.at(0) << "\n";
    std::cout << words.at(2) << "\n";
    return 0;
}
```

> HISTORY: Not every programming language uses zero-based indexing. Some famous examples use one-based indexing. For example, Fortran, Lua, and MATLAB use one-based indexing, while languages like C, C++, Java, and Python use zero-based indexing. Neither style is universally "right." Some expressions are easier in one style than the other.

## Size and length

The number of elements currently in a container is its **size** or **length**.

```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> values{10, 20, 30, 40, 50};

    std::cout << values.size() << "\n";
    return 0;
}
```

C++ also has `sizeof`, but that answers a different question.

`sizeof` tells you how many **bytes** a type or object uses. That is not the same as how many elements are inside a container.

## Common container operations

Most containers support the operations you would expect:

| Operation | Meaning |
|-----------|---------|
| Create | Make a new container |
| Access | Read one element by index |
| Add | Put a new value in the container |
| Remove | Delete a value from the container |
| Size | Ask how many elements are stored |

## Homogeneous containers

Most containers require every element to have the same type.

You cannot put an `int`, a `double`, and a `std::string` in the same standard container.

## Containers in C++

C++ has many container types. This book will focus on `std::vector` for most list and array needs.

| Container        | Typical use in this book                    |
|------------------|---------------------------------------------|
| `std::vector`    | General-purpose dynamic array               |
| `std::string`    | Sequence of characters                      |
| `std::array`     | Fixed-size array wrapper                    |
| `std::list`      | Doubly-linked list for frequent insert/erase |
| `std::map`       | Store key-value pairs (like a dictionary)   |
| `std::set`       | Unique values, no duplicates                |

## Try it now

### Exercise 1: First and last

Prompt: Create a vector of three words and print the first and last elements.

```cpp
#include <iostream>
#include <string>
#include <vector>

int main()
{
    std::vector<std::string> animals{"cat", "dog", "fish", "bird"};

    // TODO: Print the first and last animals.

    return 0;
}
```

### Exercise 2: Report the size

Prompt: Create a vector of integers and print how many values it currently holds.

```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> values{2, 4, 6, 8};

    // TODO: Print the number of elements in the vector.

    return 0;
}
```
