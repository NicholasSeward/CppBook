# String Streams

Console I/O uses the keyboard and terminal.

**String streams** use a `std::string` in memory as the data source or destination.

They behave like `std::cin` and `std::cout`, but the data lives in a string you can build, inspect, and reuse.

## Headers and types

| Type | Header | Role |
|------|--------|------|
| `std::istringstream` | `<sstream>` | read from a string |
| `std::ostringstream` | `<sstream>` | write into a string |
| `std::stringstream` | `<sstream>` | both directions |

> PREFERENCE: Use `istringstream` when you only parse, and `ostringstream` when you only build. Use `stringstream` when you truly need both in one object.

## Parse a complicated line after `getline`

Imagine the user types:

```
Ada 42 98.5
```

Read the whole line, then split it:

```cpp
#include <iostream>
#include <sstream>
#include <string>

int main()
{
    std::string line{};

    std::cout << "Enter name, id, and score: ";
    std::getline(std::cin, line);

    std::istringstream lineStream{line};

    std::string name{};
    int id{};
    double score{};

    lineStream >> name >> id >> score;

    std::cout << "Name: " << name << "\n";
    std::cout << "ID: " << id << "\n";
    std::cout << "Score: " << score << "\n";

    return 0;
}
```

`lineStream >> name` uses the same rules as `std::cin >> name`.

## Build a string before printing

```cpp
#include <iostream>
#include <sstream>
#include <string>

int main()
{
    int wins{10};
    int losses{2};

    std::ostringstream builder;
    builder << "Record: " << wins << "-" << losses;

    std::string message{builder.str()};
    std::cout << message << "\n";

    return 0;
}
```

`str()` returns the `std::string` held inside the stream.

## Same operators as console streams

```cpp
#include <sstream>
#include <string>

int main()
{
    std::ostringstream out;
    out << "x = " << 5 << ", y = " << 7;

    std::istringstream in{out.str()};

    std::string label{};
    char equals{};
    int x{};
    char comma{};
    std::string label2{};
    char equals2{};
    int y{};

    in >> label >> equals >> x >> comma >> label2 >> equals2 >> y;

    return 0;
}
```

Formatting manipulators from `<iomanip>` also work on string streams when you need formatted text in memory.

## Try it now

### Exercise 1: Parse three numbers

Prompt: Read one line, then use `istringstream` to read three integers from it.

```cpp
#include <iostream>
#include <sstream>
#include <string>

int main()
{
    std::string line{};

    std::cout << "Enter three integers on one line: ";
    std::getline(std::cin, line);

    // TODO: Parse three ints from line and print their sum.

    return 0;
}
```

### Exercise 2: Build a message

Prompt: Use `ostringstream` to build `"Player 7 scored 120"` without printing until the string is complete.

```cpp
#include <iostream>
#include <sstream>
#include <string>

int main()
{
    int playerNumber{7};
    int points{120};

    // TODO: Build the message in an ostringstream.
    // TODO: Print the final string once.

    return 0;
}
```
