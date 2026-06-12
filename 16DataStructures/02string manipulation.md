# String Manipulation

Once you can store text in `std::string`, you need tools to search, slice, change, and convert it.

## Common string functions

| Function | Typical use | Returns / notes |
|----------|-------------|-----------------|
| `s.size()` / `s.length()` | how many characters | `int` (store the count) |
| `s.empty()` | any characters? | `bool` |
| `s.clear()` | remove all characters | void |
| `s[i]`, `s.at(i)` | character at index | `char&` |
| `s.front()`, `s.back()` | first / last character | `char&` |
| `s + t`, `s += t` | join strings | new string / append in place |
| `s.append(str)` | add text at end | void |
| `s.insert(pos, str)` | insert at index | void |
| `s.erase(pos, count)` | remove substring | void |
| `s.replace(pos, len, str)` | swap substring | void |
| `s.pop_back()` | remove last character | void |
| `s.substr(pos, count)` | copy part of string | new `string` |
| `s.find(needle)` | first match | index or `npos` |
| `s.rfind(needle)` | last match | index or `npos` |
| `s.find_first_of(chars)` | first char from a set | index or `npos` |
| `s.find_first_not_of(chars)` | first char not in set | index or `npos` |
| `s.find_last_not_of(chars)` | last char not in set | index or `npos` |
| `s.compare(other)` | three-way compare | `<0`, `0`, `>0` |
| `==`, `!=`, `<`, `>` | lexicographic compare | `bool` |
| `std::getline(cin, s)` | read full line | includes spaces |
| `std::stoi(s)`, `std::stol(s)` | text to integer | throws on bad input |
| `std::to_string(n)` | number to text | `string` |

`std::string::npos` means "not found" from `find` and `rfind`.

## Parse an email into user and domain

```cpp
#include <iostream>
#include <string>

int main()
{
    std::string email{"ada.lovelace@example.com"};

    int atPos{email.find('@')};

    if (atPos == std::string::npos)
    {
        std::cout << "Not an email\n";
        return 0;
    }

    std::string user{email.substr(0, atPos)};
    std::string domain{email.substr(atPos + 1)};

    std::cout << "user: " << user << '\n';
    std::cout << "domain: " << domain << '\n';
    return 0;
}
```

`find` locates `@`. `substr` copies the parts before and after it.

## Trim whitespace

```cpp
#include <iostream>
#include <string>

int main()
{
    std::string line{"  yes  "};

    int start{line.find_first_not_of(' ')};
    int end{line.find_last_not_of(' ')};
    std::string trimmed{line.substr(start, end - start + 1)};

    if (trimmed == "yes")
    {
        std::cout << "Confirmed\n";
    }

    return 0;
}
```

## Build text and parse a number

```cpp
#include <iostream>
#include <string>

int main()
{
    std::string label{"Score: "};
    int points{42};
    std::string message{label + std::to_string(points)};

    std::cout << message << '\n';

    std::string input{"87"};
    int value{std::stoi(input)};
    std::cout << value + 1 << '\n';

    return 0;
}
```

## Try it now

### Exercise 1: Split a filename

Prompt: Given `report_2026.txt`, use `find` and `substr` to print the base name and extension separately.

```cpp
// @file: main.cpp
#include <iostream>
#include <string>

int main()
{
    std::string filename{"report_2026.txt"};

    // TODO: find '.' and split into base + extension

    return 0;
}
```

### Exercise 2: Count substring occurrences

Prompt: Count how many times `"the"` appears in a sentence using `find` in a loop.

```cpp
// @file: main.cpp
#include <iostream>
#include <string>

int main()
{
    std::string text{"the cat and the hat"};
    std::string needle{"the"};
    int count{0};

    // TODO: loop with find, advance start position after each match

    std::cout << "count: " << count << '\n';
    return 0;
}
```
