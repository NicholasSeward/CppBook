# Python to C++ Quick Start (Module 1)

This guide shows common Python patterns and their C++ equivalents for Programming II.

It is meant as a quick bridge if you already know some Python and are starting C++.

## Minimum C++ setup (console programs)

```cpp
#include <iostream>
#include <string>

int main()
{
    // your code here
    return 0;
}
```

Use `std::cout` to print and `std::cin` to read input.

> PREFERENCE: In this course, do not use `using namespace std;`. Write `std::cout`, `std::cin`, `std::string`, and so on.

## Print / output

Python:

```python
x = 42
print("Hello")
print("x =", x)
```

C++:

```cpp
#include <iostream>

int main()
{
    int x{42};
    std::cout << "Hello" << std::endl;
    std::cout << "x = " << x << std::endl;
    return 0;
}
```

Notes:

- `<<` streams values into output.
- `std::endl` prints a newline and flushes.
- You can also use `"\n"` for a newline.

## Input

Python:

```python
name = input("Enter your name: ")
age = int(input("Enter age: "))
```

C++ token input:

```cpp
#include <iostream>
#include <string>

int main()
{
    std::string name;
    std::cout << "Enter your name: ";
    std::cin >> name; // reads one word, stops at whitespace

    int age{};
    std::cout << "Enter age: ";
    std::cin >> age;

    std::cout << "Hello " << name << ", age " << age << std::endl;
    return 0;
}
```

C++ full line input:

```cpp
#include <iostream>
#include <string>

int main()
{
    std::string fullName;
    std::cout << "Enter your full name: ";
    std::getline(std::cin, fullName);

    std::cout << "Hello " << fullName << std::endl;
    return 0;
}
```

Gotcha when mixing `>>` and `std::getline`:

```cpp
#include <iostream>
#include <limits>
#include <string>

int main()
{
    int age{};
    std::string fullName;

    std::cout << "Enter age: ";
    std::cin >> age;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Enter your full name: ";
    std::getline(std::cin, fullName);

    std::cout << fullName << " is " << age << std::endl;
    return 0;
}
```

That consumes the leftover newline before `std::getline`.

## If / elif / else

Python:

```python
score = 85

if score >= 90:
    grade = "A"
elif score >= 80:
    grade = "B"
else:
    grade = "F"

print(grade)
```

C++:

```cpp
#include <iostream>
#include <string>

int main()
{
    int score{85};
    std::string grade;

    if (score >= 90)
    {
        grade = "A";
    }
    else if (score >= 80)
    {
        grade = "B";
    }
    else
    {
        grade = "F";
    }

    std::cout << grade << std::endl;
    return 0;
}
```

Notes:

- C++ uses parentheses around conditions.
- C++ uses braces for blocks.

## For loops

Python with `range`:

```python
for i in range(5):
    print(i)
```

C++:

```cpp
#include <iostream>

int main()
{
    for (int i{0}; i < 5; ++i)
    {
        std::cout << i << std::endl;
    }

    return 0;
}
```

Python looping through a list:

```python
nums = [10, 20, 30]
for n in nums:
    print(n)
```

C++ range-based `for`:

```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> nums{10, 20, 30};

    for (int n : nums)
    {
        std::cout << n << std::endl;
    }

    return 0;
}
```

> NOTE: If you use `std::vector`, add `#include <vector>`.

## While loops

Python:

```python
count = 0
while count < 3:
    print(count)
    count += 1
```

C++:

```cpp
#include <iostream>

int main()
{
    int count{0};

    while (count < 3)
    {
        std::cout << count << std::endl;
        count += 1;
    }

    return 0;
}
```

## Functions

Python:

```python
def add(a, b):
    return a + b

print(add(2, 3))
```

C++:

```cpp
#include <iostream>

int add(int a, int b)
{
    return a + b;
}

int main()
{
    std::cout << add(2, 3) << std::endl;
    return 0;
}
```

No return value in Python:

```python
def greet(name):
    print("Hello", name)

greet("Ada")
```

No return value in C++:

```cpp
#include <iostream>
#include <string>

void greet(const std::string& name)
{
    std::cout << "Hello " << name << std::endl;
}

int main()
{
    greet("Ada");
    return 0;
}
```

Notes:

- C++ functions must declare a return type (`int`, `double`, `void`, etc.).
- `const std::string&` avoids copying and prevents accidental modification.

## Types (big differences from Python)

Python is **dynamically typed**. Types are attached to values.

C++ is **statically typed**. Types are attached to variables.

Common C++ types:

| Type | Meaning | Example |
|------|---------|---------|
| `int` | whole numbers | `-3`, `0`, `42` |
| `double` | decimals | `3.14`, `0.5` |
| `char` | one character | `'A'`, `'7'` |
| `bool` | true / false | `true`, `false` |
| `std::string` | text | `"hello"` |

Examples:

```cpp
#include <iostream>
#include <string>

int main()
{
    int items{5};
    double price{12.99};
    char letter{'A'};
    bool isValid{true};
    std::string name{"Ada"};

    std::cout << items << std::endl;
    std::cout << price << std::endl;
    std::cout << letter << std::endl;
    std::cout << std::boolalpha << isValid << std::endl;
    std::cout << name << std::endl;
    return 0;
}
```

## Integer division vs decimal division

Python:

```python
5 / 2   # 2.5
5 // 2  # 2
```

C++:

```cpp
#include <iostream>

int main()
{
    std::cout << (5 / 2) << std::endl;                       // 2 (int division)
    std::cout << (5.0 / 2) << std::endl;                     // 2.5 (double division)
    std::cout << (static_cast<double>(5) / 2) << std::endl;  // 2.5
    return 0;
}
```

## Converting input types

In C++, you usually read directly into the variable type:

```cpp
#include <iostream>

int main()
{
    int age{};
    std::cout << "Enter age: ";
    std::cin >> age;
    std::cout << age << std::endl;
    return 0;
}
```

Use `static_cast<type>(value)` for safe, explicit conversions:

```cpp
#include <iostream>

int main()
{
    int total{17};
    int count{5};
    double avg = static_cast<double>(total) / count;

    std::cout << avg << std::endl;
    return 0;
}
```

## Quick cheat sheet

| Python | C++ |
|--------|-----|
| `print(x)` | `std::cout << x << std::endl;` |
| `x = input()` | `std::cin >> x;` or `std::getline(std::cin, x);` |
| `if cond:` | `if (cond) { ... }` |
| `for i in range(n):` | `for (int i{0}; i < n; ++i) { ... }` |
| `while cond:` | `while (cond) { ... }` |
| `def f(...):` | `returnType f(...) { ... }` |

> NOTE: The cheat sheet uses compact `{ ... }` to save space. Full examples in this book use vertically aligned braces.

## Try it now

Use each working Python program as the target behavior. Then complete the C++ starter playground.

### 1. Greeting with input

Prompt: Ask for a name, then print a greeting.

```python
name = input("Name? ")
print("Hello, " + name + "!")
```

```cpp
#include <iostream>
#include <string>

int main()
{
    std::string name{};

    // TODO: Ask for the name.
    // TODO: Read the name.
    // TODO: Print the greeting.

    std::cout << "Starter runs.\n";
    return 0;
}
```

### 2. Pass or retry

Prompt: Read a score. Print `"pass"` if the score is at least `70`; otherwise print `"retry"`.

```python
score = int(input("Score? "))

if score >= 70:
    print("pass")
else:
    print("retry")
```

```cpp
#include <iostream>

int main()
{
    int score{};

    // TODO: Ask for the score.
    // TODO: Read the score.
    // TODO: Use if/else to print pass or retry.

    std::cout << "Starter runs.\n";
    return 0;
}
```

### 3. Count and total

Prompt: Print the numbers from `0` through `4`, then print their total.

```python
total = 0

for number in range(5):
    print(number)
    total += number

print("Total:", total)
```

```cpp
#include <iostream>

int main()
{
    int total{0};

    // TODO: Write a zero-based for loop.
    // TODO: Print each number.
    // TODO: Add each number to total.
    // TODO: Print the total after the loop.

    std::cout << "Starter runs.\n";
    return 0;
}
```

### 4. A small function

Prompt: Write a function that doubles a number, then call it from the main part of the program.

```python
def double_number(value):
    return value * 2

number = 6
print(double_number(number))
```

```cpp
#include <iostream>

int doubleNumber(int value)
{
    // TODO: Return value times 2.
    return value;
}

int main()
{
    int number{6};

    // TODO: Print the doubled number.

    std::cout << "Starter runs.\n";
    return 0;
}
```
