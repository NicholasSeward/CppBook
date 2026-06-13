# STL Algorithm Reference

The C++ Standard Library ships dozens of algorithms in `<algorithm>` (and a few related helpers in `<numeric>`). They all take **iterator ranges** so the same names work on `vector`, `list`, `deque`, and more.

You have already used iterators, `std::sort`, and `find` / `count`. This section is a **catalog** of the rest, grouped by role. Later sections cover custom sort order, `for_each`, and timing.

## Three categories

| Category | Job | Changes container? |
|----------|-----|--------------------|
| **Inspector** | read and report | no |
| **Mutator** | change order or values in place | yes |
| **Facilitator** | run your logic, often writing somewhere else | maybe |

When in doubt: if the container looks different after the call, it is a mutator. If your function might change elements, the facilitator might too.

---

## Inspectors (read-only)

These algorithms look at a range and return an answer. They do not rearrange the container.

| Algorithm | What it does |
|-----------|--------------|
| `std::find` | first element equal to a value |
| `std::find_if` | first element where a predicate is true |
| `std::count` | how many equal a value |
| `std::count_if` | how many satisfy a predicate |
| `std::min_element` | iterator to smallest in a range |
| `std::max_element` | iterator to largest in a range |
| `std::all_of` | true if predicate true for **every** element |
| `std::any_of` | true if predicate true for **at least one** element |
| `std::binary_search` | is value present in a **sorted** range? |
| `std::equal` | do two ranges match element by element? |

### Example: min_element and max_element

```cpp
#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> scores{88, 72, 95, 61};

    auto smallest{std::min_element(scores.begin(), scores.end())};
    auto largest{std::max_element(scores.begin(), scores.end())};

    std::cout << "Lowest score: " << *smallest << '\n';
    std::cout << "Highest score: " << *largest << '\n';

    return 0;
}
```

### Example: all_of and any_of

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
    std::vector<int> teamA{90, 85, 72};
    std::vector<int> teamB{90, 55, 72};

    std::cout << std::boolalpha;
    std::cout << "Team A all passing: "
              << std::all_of(teamA.begin(), teamA.end(), isPassing) << '\n';
    std::cout << "Team B any passing: "
              << std::any_of(teamB.begin(), teamB.end(), isPassing) << '\n';

    return 0;
}
```

---

## Mutators (change in place)

These algorithms modify the container (or the elements inside it).

| Algorithm | What it does |
|-----------|--------------|
| `std::sort` | sort entire range ascending (or custom order) |
| `std::reverse` | reverse element order in place |
| `std::rotate` | shift a subrange so a middle element becomes first |
| `std::fill` | set every element to one value |
| `std::replace` | swap each match of one value for another |
| `std::replace_if` | swap values that satisfy a predicate |
| `std::remove` | move non-matching items to front (does not shrink size alone) |
| `std::remove_if` | same, with a predicate |
| `std::unique` | collapse consecutive duplicates (often after sort) |

> NOTE: `remove` and `remove_if` do not erase from the container. Pair them with `erase` on the container (the **erase-remove idiom**). You will see that pattern once iterators are comfortable.

### Example: sort and reverse

```cpp
#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> values{5, 1, 4, 3, 8};

    std::sort(values.begin(), values.end());
    std::cout << "Sorted: ";
    for (int n : values)
    {
        std::cout << n << ' ';
    }
    std::cout << '\n';

    std::reverse(values.begin(), values.end());
    std::cout << "Reversed: ";
    for (int n : values)
    {
        std::cout << n << ' ';
    }
    std::cout << '\n';

    return 0;
}
```

### Example: fill and replace

```cpp
#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> values(5, 0);

    std::fill(values.begin(), values.end(), 7);
    std::replace(values.begin(), values.end(), 7, 3);

    for (int n : values)
    {
        std::cout << n << ' ';
    }
    std::cout << '\n';

    return 0;
}
```

---

## Facilitators (run your logic)

Facilitators walk a range and **apply your function**. Unlike inspectors, they are meant for side effects or building a result through repeated work.

This course focuses on two:

| Algorithm | Header | What it does |
|-----------|--------|--------------|
| `std::for_each` | `<algorithm>` | call a function on each element |
| `std::accumulate` | `<numeric>` | fold a range into one value (sum by default) |

Others in the same spirit include `std::transform`, `std::copy`, and `std::copy_if`. They copy or map into another range. You will see `for_each` again in the next section on custom sort.

Whether the original container changes depends on **your** callback. Pass by reference to modify in place; pass by value to read only.

### Example: for_each (read only)

```cpp
#include <algorithm>
#include <iostream>
#include <vector>

void printSquare(int n)
{
    std::cout << n * n << ' ';
}

int main()
{
    std::vector<int> values{1, 2, 3, 4};

    std::cout << "Squares: ";
    std::for_each(values.begin(), values.end(), printSquare);
    std::cout << '\n';

    return 0;
}
```

`printSquare` takes `int n` **by value**. The vector is not changed.

### Example: for_each (modify in place)

Pass **`int&`** when you want to update each element:

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

After `for_each`, the vector holds `2 4 6 8`. Same pattern as the Try it now exercise below.

`for_each` does not return a new container. It runs your function once per element.

### Example: accumulate (sum)

```cpp
#include <iostream>
#include <numeric>
#include <vector>

int main()
{
    std::vector<int> values{10, 20, 30, 40};

    int total{std::accumulate(values.begin(), values.end(), 0)};

    std::cout << "Sum: " << total << '\n';

    return 0;
}
```

The third argument is the **starting value** (`0` here). By default, `accumulate` **adds** each element into that running total.

> NOTE: `accumulate` is a general **fold**: combine a range into one value. With the default `+` you get a sum. Pass a custom function as the fourth argument and you can compute a **product**, a **sum of squares**, count matching letters, or any other running combination.

### Example: accumulate (product)

Use `1` as the starting value and multiply each step:

```cpp
#include <iostream>
#include <numeric>
#include <vector>

int multiplyStep(int total, int n)
{
    return total * n;
}

int main()
{
    std::vector<int> values{2, 3, 4};

    int product{std::accumulate(values.begin(), values.end(), 1, multiplyStep)};

    std::cout << "Product: " << product << '\n';

    return 0;
}
```

Output: `24` (because `1 * 2 * 3 * 4`).

### Example: accumulate (count letters)

The range does not have to be a `vector<int>`. Walk a `string` and fold into a count:

```cpp
#include <iostream>
#include <numeric>
#include <string>

int countLetterE(int count, char c)
{
    if (c == 'e')
    {
        return count + 1;
    }
    return count;
}

int main()
{
    std::string word{"letter"};

    int eCount{std::accumulate(word.begin(), word.end(), 0, countLetterE)};

    std::cout << "e count: " << eCount << '\n';

    return 0;
}
```

Output: `2` (the two `'e'` characters in `"letter"`).

Each step passes two values to your function: the **running result so far** and the **next element**. For letter counting, the running result starts at `0` and your function returns `count + 1` when the character matches, otherwise `count` unchanged.

That same shape works for other folds:

- **Sum of squares:** start at `0`, add `n * n` each step
- **Product:** start at `1`, multiply by each `n`
- **Running maximum:** start at the first value (or a sentinel), keep the larger of running and next

Always: **starting value**, **begin/end range**, and a **combine function** `(running, element)`.

---

## Quick pick guide

| You need to… | Start with |
|--------------|------------|
| Sort data | `std::sort` |
| Find one item | `std::find` or `std::find_if` |
| Count matches | `std::count` or `std::count_if` |
| Smallest / largest in range | `std::min_element` / `std::max_element` |
| Check a condition on all items | `std::all_of`, `any_of`, `none_of` |
| Run code on each item | `std::for_each` |
| Sum (or fold) a range | `std::accumulate` |
| Search sorted data fast | `std::binary_search`|

> PREFERENCE: Learn the names in this table first. When a job matches, use the algorithm instead of rewriting the loop.

## Try it now

### Exercise 1: Inspector combo

Prompt: Given a vector of scores, print the highest score (`max_element`) and whether **every** score is at least 0 (`all_of`).

```cpp
// @file: main.cpp
#include <algorithm>
#include <iostream>
#include <vector>

bool isNonNegative(int score)
{
    return score >= 0;
}

int main()
{
    std::vector<int> scores{90, 85, 72, 100};

    // TODO: max_element and all_of

    return 0;
}
```

### Exercise 2: Facilitator combo

Prompt: Use `for_each` to double each value in place, then `accumulate` to print the sum.

```cpp
// @file: main.cpp
#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

void doubleInPlace(int& n)
{
    n *= 2;
}

int main()
{
    std::vector<int> values{1, 2, 3, 4};

    // TODO: for_each with doubleInPlace, then accumulate starting from 0

    return 0;
}
```
