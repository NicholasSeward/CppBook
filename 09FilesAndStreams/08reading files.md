# Reading Files

File input works like keyboard input.

This book will name stream objects `fin` and `fout` to match with `cin` and `cout`.

## Headers and types

| Type | Header | Purpose |
|------|--------|---------|
| `std::ifstream` | `<fstream>` | read from a file |
| `std::ofstream` | `<fstream>` | write to a file |
| `std::fstream` | `<fstream>` | read and write (less common in intro code) |

This chapter focuses on reading with `std::ifstream`.

## Open a file and check success

```cpp
// @file: main.cpp
#include <fstream>
#include <iostream>
#include <string>

int main()
{
    std::ifstream fin{"numbers.txt"};

    if (!fin)
    {
        std::cerr << "Could not open numbers.txt\n";
        return 1;
    }

    int value{};
    int total{};

    while (fin >> value)
    {
        std::cout << value << "\n";
        total += value;
    }

    std::cout << "Total: " << total << "\n";
    return 0;
}

// @file: numbers.txt
3 4 5
10 20
1
```

The loop `while (fin >> value)` reads integers until no more valid reads remain.

## Why the loop stops

`fin >> value` returns the stream. In a condition, the stream converts to `true` when the read succeeded.

At end of file or after a bad read, the condition becomes `false` and the loop ends.

## Reading lines, then parsing pieces

When each line has a different shape, read the **line** first, then parse with `std::istringstream`:

```cpp
// @file: main.cpp
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

int main()
{
    std::ifstream fin{"rows.txt"};

    if (!fin)
    {
        std::cerr << "Could not open rows.txt\n";
        return 1;
    }

    std::string line{};

    while (std::getline(fin, line))
    {
        std::istringstream lineStream{line};
        int value{};
        int rowTotal{};

        while (lineStream >> value)
        {
            std::cout << value << " ";
            rowTotal += value;
        }

        std::cout << "| row total: " << rowTotal << "\n";
    }

    return 0;
}

// @file: rows.txt
3 4 5
10 20
1 2 3 4
```

This pattern matches how many real programs work: one pass through the file, then data lives in variables and containers in RAM for later use.

## Try it now

### Exercise 1: Count integers

Prompt: Open `data.txt`, count how many integers it contains, and print the count.

```cpp
// @file: main.cpp
#include <fstream>
#include <iostream>

int main()
{
    std::ifstream fin{"data.txt"};

    // TODO: Check open, count integers with while (fin >> n).

    return 0;
}

// @file: data.txt
2
5
6
34
2
5
```

### Exercise 2: Line totals

Prompt: For each line in a file there is a string and an int.  Print each string the number of times indicated.

```cpp
// @file: main.cpp
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

int main()
{
    std::ifstream fin{"words.txt"};

    // TODO: getline each row, istringstream to get std::string and int.

    return 0;
}

// @file: words.txt
squirrel 3
owl 5
cat 2
```
