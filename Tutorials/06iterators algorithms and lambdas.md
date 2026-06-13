# Tutorial: Iterators, Algorithms, and Lambdas (Module 6)

Go play with and run the code below. You can use CodeBin, Codespaces, TxtBook, or whatever environment you like. Run it and get a feel for the code before you answer each question.

Work through each section in order. Change only what each question asks for unless a question says to keep earlier edits.

Related chapter: [11 Algorithms And Lambdas](../11AlgorithmsAndLambdas/README.md).

---

## `begin()` and `end()`

Iterators let you walk containers such as `std::vector`, `std::set`, and `std::map`. `begin()` points at the first element; `end()` points **past** the last element.

### Starter code

```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> numbers{1, 2, 3, 4, 5};
    auto it{numbers.begin()};

    std::cout << "First element: " << *it << '\n';

    return 0;
}
```

### 1.

What is the output of the program?

- A. `First element: 0`
- B. `First element: 1`
- C. Compilation error
- D. Segmentation fault

---

## `std::next()` and `std::prev()`

`std::next(it, n)` moves an iterator forward `n` steps. `std::prev(it, n)` moves backward. Include `<iterator>`.

### Starter code

```cpp
#include <iostream>
#include <iterator>
#include <vector>

int main()
{
    std::vector<int> numbers{10, 20, 30, 40, 50};
    auto it{numbers.begin()};
    auto nextIt{std::next(it, 2)};

    std::cout << "Value at nextIt: " << *nextIt << '\n';

    return 0;
}
```

### 2.

What is printed?

- A. `Value at nextIt: 10`
- B. `Value at nextIt: 20`
- C. `Value at nextIt: 30`
- D. Compilation error

---

## Iterator loops

The usual pattern: start at `begin()`, stop when `it != end()`, advance with `++it`.

### Starter code

```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> nums{1, 2, 3, 4, 5};

    for (auto it{nums.begin()}; it != nums.end(); ++it)
    {
        std::cout << *it << ' ';
    }

    std::cout << '\n';

    return 0;
}
```

### 3.

What does the program output?

- A. `1 2 3 4 5`
- B. Compilation error
- C. Undefined behavior
- D. Segmentation fault

---

## `std::accumulate`

`std::accumulate` folds a range into one value. With `0` as the start, it sums the elements. Include `<numeric>`.

### Starter code

```cpp
#include <iostream>
#include <numeric>
#include <vector>

int main()
{
    std::vector<int> values{1, 2, 3, 4, 5};
    int sum{std::accumulate(values.begin(), values.end(), 0)};

    std::cout << "Sum: " << sum << '\n';

    return 0;
}
```

### 4.

What is the output?

- A. `Sum: 10`
- B. `Sum: 15`
- C. `Sum: 20`
- D. Compilation error

---

## `std::for_each`

`std::for_each` runs a function on every element in a range. Lambdas are a common way to pass that function. Include `<algorithm>`.

### Starter code

```cpp
#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> nums{1, 2, 3, 4, 5};

    std::for_each(nums.begin(), nums.end(), [](int n)
    {
        std::cout << n << ' ';
    });

    std::cout << '\n';

    return 0;
}
```

### 5.

What is printed?

- A. `1 2 3 4 5`
- B. Compilation error
- C. Undefined behavior
- D. Segmentation fault

---

## Sorting with a lambda

`std::sort` can take a comparison function as its third argument. A lambda works well when you only need the rule in one place.

### Starter code

```cpp
#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> values{5, 2, 8, 3, 1};

    std::sort(values.begin(), values.end(), [](int a, int b)
    {
        return a > b;
    });

    for (int v : values)
    {
        std::cout << v << ' ';
    }

    std::cout << '\n';

    return 0;
}
```

### 6.

What is the output?

- A. `1 2 3 5 8`
- B. `8 5 3 2 1`
- C. Compilation error
- D. Undefined behavior

---

## A stranger sort rule

Keep the same starter from question 6, but replace the lambda with:

```cpp
[](int a, int b)
{
    return a % 2 < b % 2;
}
```

### 7.

What is the output?

- A. `2 8 5 3 1`
- B. `5 3 1 2 8`
- C. `1 2 3 5 8`
- D. `8 5 3 2 1`
- E. Undefined behavior

This is an odd way to sort, but it works: evens (`a % 2 == 0`) sort before odds (`a % 2 == 1`). When two numbers have the same parity, the comparator treats them as equal, so their relative order is not specified by this rule alone.

That flexibility is the point. You are not stuck with `<` or `>`. Any comparison you can write in a lambda can drive `std::sort`, `find_if`, `for_each`, and the rest of the STL algorithm toolbox.
