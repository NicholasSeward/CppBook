# Passing Vectors

Vectors can be large. Passing them the wrong way can copy more data than you intend.

## Pass by value

Passing by value makes a copy of the whole vector.

```cpp
#include <iostream>
#include <vector>

void printSize(std::vector<int> values)
{
    std::cout << "Inside function, size = " << values.size() << "\n";
}

int main()
{
    std::vector<int> values{1, 2, 3, 4, 5};

    std::cout << "Before call, size = " << values.size() << "\n";
    printSize(values);
    std::cout << "After call, size = " << values.size() << "\n";
    return 0;
}
```

Use pass by value only when the copy is cheap or when you truly need an independent copy.

## Pass by reference

Passing by reference lets the function work with the original vector.

```cpp
#include <iostream>
#include <vector>

void doubleAll(std::vector<int>& values)
{
    for (int count{0}; count < values.size(); ++count)
    {
        values.at(count) *= 2;
    }
}

int main()
{
    std::vector<int> values{1, 2, 3};

    doubleAll(values);

    for (int value : values)
    {
        std::cout << value << " ";
    }
    std::cout << "\n";
    return 0;
}
```

Use a non-const reference when the function should modify the vector.

## Pass by const reference

Passing by const reference gives read-only access without making a copy.

```cpp
#include <iostream>
#include <vector>

void printTotal(const std::vector<int>& values)
{
    int total{0};

    for (int value : values)
    {
        total += value;
    }

    std::cout << "Total: " << total << "\n";
}

int main()
{
    std::vector<int> values{10, 20, 30};

    printTotal(values);
    return 0;
}
```

Use a const reference when the function only needs to read the vector.

| Goal | Parameter type |
|------|----------------|
| Function may change the vector | `std::vector<T>&` |
| Function only reads the vector | `const std::vector<T>&` |
| Function needs its own copy | `std::vector<T>` by value |

## Try it now

### Exercise 1: Modify in a function

Prompt: Pass a vector to a function by reference and double every value in place.

```cpp
#include <iostream>
#include <vector>

void doubleValues(...)
{
    // TODO: Double every value in the vector.
}

int main()
{
    std::vector<int> values{1, 2, 3, 4, 5};

  // TODO: Call doubleValues and print the updated vector.

    return 0;
}
```

### Exercise 2: Read without copying

Prompt: Pass a vector by const reference and print the total without changing the original values.

```cpp
#include <iostream>
#include <vector>

int printTotal(...)
{
    int total{0};

    // TODO: Add up all values and print the total.
    // TODO: Do not change the vector.

    return total;
}

int main()
{
    std::vector<int> values{10, 20, 30};

    std::cout << printTotal(values) << "\n";
    return 0;
}
```
