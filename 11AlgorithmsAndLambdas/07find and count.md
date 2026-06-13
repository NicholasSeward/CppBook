# Find and Count

Many STL algorithms are **inspectors**: they read your container without rearranging it. Now that you know iterators, `find`, `find_if`, `count`, and `count_if` are straightforward to use.

`#include <algorithm>`.

## std::find

`find` needs a start iterator, end iterator, and a value to match. It returns an iterator to the **first** match, or **`end`** if nothing matches.

```cpp
#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> values{10, 20, 30, 40};

    auto it{std::find(values.begin(), values.end(), 30)};

    if (it != values.end())
    {
        std::cout << "Found: " << *it << '\n';
    }

    return 0;
}
```

`*it` dereferences the iterator, same as in a manual iterator loop.

## When find misses

```cpp
#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> values{10, 20, 30, 40};

    auto it{std::find(values.begin(), values.end(), 99)};

    if (it == values.end())
    {
        std::cout << "Not found\n";
    }

    return 0;
}
```

Always compare the result to `end()`. There is no valid element to dereference when find fails.

> NOTE: In C++20 and later, `.contains()` checks for existence. In C++17 (used here), use `find` and compare to `end()`. `find` also gives the exact location of the match, which is useful if you need to access neighboring elements.

## std::find_if

`find_if` takes a **predicate**: a function that returns `true` when an element matches.

```cpp
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

bool startsWithA(const std::string& word)
{
    return !word.empty() && word.at(0) == 'A';
}

int main()
{
    std::vector<std::string> names{"Mo", "Ada", "Ali", "Bo"};

    auto it{std::find_if(names.begin(), names.end(), startsWithA)};

    if (it != names.end())
    {
        std::cout << "First A name: " << *it << '\n';
    }

    return 0;
}
```

## std::count and std::count_if

`count` returns how many elements equal a value. `count_if` counts how many satisfy a predicate.

```cpp
#include <algorithm>
#include <iostream>
#include <vector>

bool isEven(int n)
{
    return n % 2 == 0;
}

int main()
{
    std::vector<int> values{1, 2, 3, 4, 2, 6};

    int twos{std::count(values.begin(), values.end(), 2)};
    int evens{std::count_if(values.begin(), values.end(), isEven)};

    std::cout << "Twos: " << twos << '\n';
    std::cout << "Evens: " << evens << '\n';

    return 0;
}
```

## Try it now

### Exercise 1: Find a name

Prompt: Search a `vector<string>` for `"Lin"`. Print the name if found, otherwise print `"Missing"`.

```cpp
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int main()
{
    std::vector<std::string> roster{"Ada", "Mo", "Lin"};

    // TODO: std::find and print result

    return 0;
}
```

### Exercise 2: Count passing scores

Prompt: Count how many scores in a vector are at least 60 using `count_if`.

```cpp
#include <algorithm>
#include <iostream>
#include <vector>

bool isPassing(int score)
{
    return score >= 60;
}

int main()
{
    std::vector<int> scores{55, 72, 90, 48, 61};
    int passCount{0};

    // TODO: count_if into passCount

    std::cout << "Passing: " << passCount << '\n';
    return 0;
}
```
