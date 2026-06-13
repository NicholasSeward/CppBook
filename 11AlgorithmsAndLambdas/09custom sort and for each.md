# Custom Sort and for_each

You have seen `std::sort` with default ordering and browsed the algorithm catalog. This section goes deeper on **custom sort order** and **`for_each`**.

## Custom sort order

Suppose you want strings sorted by **length**, then lexicographical (alphabetically) when lengths tie.

**Lexicographic order** means dictionary order by character values (ASCII: digits, then uppercase, then lowercase).

```cpp
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

bool shorterFirst(const std::string& a, const std::string& b)
{
    if (a.size() != b.size())
    {
        return a.size() < b.size();
    }
    return a < b;
}

int main()
{
    std::vector<std::string> words{"pear", "fig", "apple", "kiwi", "banana"};

    std::sort(words.begin(), words.end(), shorterFirst);

    for (const std::string& word : words)
    {
        std::cout << word << '\n';
    }

    return 0;
}
```

Return `true` when the first argument should come **before** the second. [Lambda Basics](12lambda%20basics.md) shows the same comparator as an inline lambda.

## std::for_each

`for_each` calls a function on every element in the range. Pass by **reference** to modify values in place.

```cpp
#include <algorithm>
#include <iostream>
#include <vector>

void doubleValue(int& n)
{
    n *= 2;
}

int main()
{
    std::vector<int> values{1, 2, 3, 4};

    std::for_each(values.begin(), values.end(), doubleValue);

    for (int n : values)
    {
        std::cout << n << ' ';
    }
    std::cout << '\n';

    return 0;
}
```

> NOTE: `for_each` on `vector` processes in sequence order. Some algorithms on unordered containers may not visit in a meaningful order. Parallel versions exist in newer C++ standards, but sequential `for_each` on `vector` is ordered.

> NOTE: Function call overhead adds cost. A plain index loop can be faster for hot paths. Prefer clear code first; benchmark if speed matters.

## Index loop vs for_each (timing sketch)

Both can square a million integers. Results vary by compiler and machine, but the pattern shows how to compare.

```cpp
#include <algorithm>
#include <chrono>
#include <iostream>
#include <vector>

void squareRef(int& n)
{
    n *= n;
}

int main()
{
    const int N{1'000'000};
    std::vector<int> values(N);
    for (int i{0}; i < N; ++i)
    {
        values.at(i) = i;
    }

    std::vector<int> copyA{values};
    auto start{std::chrono::high_resolution_clock::now()};
    for (int i{0}; i < static_cast<int>(copyA.size()); ++i)
    {
        copyA.at(i) *= copyA.at(i);
    }
    auto end{std::chrono::high_resolution_clock::now()};
    std::cout << "Index loop ms: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << '\n';

    std::vector<int> copyB{values};
    start = std::chrono::high_resolution_clock::now();
    std::for_each(copyB.begin(), copyB.end(), squareRef);
    end = std::chrono::high_resolution_clock::now();
    std::cout << "for_each ms: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << '\n';

    return 0;
}
```

## C++20: pass the whole container

C++20 adds **range** versions of many algorithms. You pass the container directly instead of `begin()` and `end()`.

C++17 (what this course uses):

```cpp
std::sort(words.begin(), words.end(), shorterFirst);
std::for_each(values.begin(), values.end(), doubleValue);
```

C++20 (`std::ranges::`):

```cpp
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

bool shorterFirst(const std::string& a, const std::string& b)
{
    if (a.size() != b.size())
    {
        return a.size() < b.size();
    }
    return a < b;
}

void doubleValue(int& n)
{
    n *= 2;
}

int main()
{
    std::vector<std::string> words{"pear", "fig", "apple"};
    std::vector<int> values{1, 2, 3, 4};

    std::ranges::sort(words, shorterFirst);
    std::ranges::for_each(values, doubleValue);

    for (const std::string& word : words)
    {
        std::cout << word << '\n';
    }
    for (int n : values)
    {
        std::cout << n << ' ';
    }
    std::cout << '\n';

    return 0;
}
```

Same algorithms, less iterator noise. The range overload still uses iterators behind the scenes.

> NOTE: This book targets **C++17**. Playgrounds here may not compile `std::ranges::` calls unless the compiler is set to C++20. In this course, keep writing `container.begin(), container.end()`.

## Try it now

### Exercise 1: Sort by last letter

Prompt: Write a comparison function that sorts strings by their **last** character, then use `std::sort`.

```cpp
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

bool lastCharFirst(const std::string& a, const std::string& b)
{
    // TODO: compare last characters
    return false;
}

int main()
{
    std::vector<std::string> words{"cat", "dog", "ant", "bee"};
    // TODO: sort and print
    return 0;
}
```
