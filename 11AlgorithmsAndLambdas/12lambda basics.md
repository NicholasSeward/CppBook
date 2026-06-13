# Lambda Basics

Sometimes a helper function is **short** and used **once**. A named function still works, but it adds clutter to your file.

**Lambdas** (lambda expressions) let you write a small **anonymous function** inline, often right where you pass it to an algorithm.

## Motivation: `find_if` without a permanent helper

Find the first string that contains `"nut"`:

```cpp
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

bool containsNut(const std::string& word)
{
    return word.find("nut") != std::string::npos;
}

int main()
{
    std::vector<std::string> words{"apple", "donut", "pear", "walnut"};

    auto it{std::find_if(words.begin(), words.end(), containsNut)};

    if (it != words.end())
    {
        std::cout << "Found: " << *it << '\n';
    }

    return 0;
}
```

`containsNut` is fine, but you may never call it again. It still lives in the namespace for the whole translation unit.

## Lambda syntax

General form:

```
[ capture ] ( parameters ) -> returnType
{
    statements;
}
```

For now:

- leave **capture** empty: `[]`
- **parameters** like a normal function
- omit **`-> returnType`** and let the compiler deduce it
- **body** in `{ }`

Start with this skeleton when you forget details: `[](){}`. Parameters go in `()`, body in `{}`.

## Named function vs lambda

Square a number two ways:

```cpp
#include <iostream>

int squareNamed(int n);

int main()
{
    auto squareLambda = [](int n)
    {
        return n * n;
    };

    int value{6};

    std::cout << "Named:  " << squareNamed(value) << '\n';
    std::cout << "Lambda: " << squareLambda(value) << '\n';

    return 0;
}

int squareNamed(int n)
{
    return n * n;
}
```

Both print `36`. The named version lives at file scope. The lambda is created **inside `main`**, so it does not add a permanent name outside that function.

Storing a lambda in a variable is less "anonymous," but it still keeps the helper local to one scope instead of a file-wide name.

## Pass a lambda directly to an algorithm

The sweet spot: a **short lambda** as an argument. No extra named function.

Sort strings by **length**:

```cpp
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int main()
{
    std::vector<std::string> words{"pear", "fig", "apple", "kiwi", "banana"};

    std::sort(words.begin(), words.end(),
        [](const std::string& a, const std::string& b)
        {
            return a.size() < b.size();
        });

    for (const std::string& word : words)
    {
        std::cout << word << '\n';
    }

    return 0;
}
```

## Formatting for readability

Long lambdas can use normal brace layout so they read like small functions:

```cpp
#include <iostream>
#include <numeric>
#include <vector>

int main()
{
    std::vector<int> values{1, 2, 3, 4};

    int sumOfSquares{std::accumulate(values.begin(), values.end(), 0,
        [](int total, int n)
        {
            return total + n * n;
        })};

    std::cout << sumOfSquares << '\n';
    return 0;
}
```

> PREFERENCE: Keep lambdas **short and obvious**. Aim for just a few lines. If your lambda gets long or complex, write a named function instead.

> PREFERENCE: With great power comes the need for great restraint. Lambdas can do a lot; most of the time you only need a few lines.

## Try it now

### Exercise 1: `find_if` with lambda

Prompt: Find the first string longer than 5 characters using `find_if` and a lambda.

```cpp
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int main()
{
    std::vector<std::string> words{"cat", "banana", "dog"};

    // TODO: find_if with [](const std::string& s) { ... }

    return 0;
}
```

### Exercise 2: Sort by numbers at the start with lambda

Prompt: Use a lambda with `std::sort` to sort the `words` vector by the leading number at the start of each string (for example, "10cats" should come after "2dogs").

```cpp
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <sstream>

int extractLeadingNumber(const std::string& s) {
    std::stringstream ss(s);
    int num = 0;
    ss >> num;
    return num;
}

int main()
{
    std::vector<std::string> words{"10cats", "2dogs", "7birds"};

    // TODO: sort `words` using lambda comparing leading numbers of each string

    return 0;
}
```
