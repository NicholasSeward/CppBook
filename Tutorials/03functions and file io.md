# Tutorial: Functions and File I/O (Module 3)

Go play with and run the code below. You can use CodeBin, Codespaces, or whatever environment you like. Run it and get a feel for the code before you answer each question.

Work through each section in order. Change only what each question asks for unless a question says to keep earlier edits.

---

## Function basics

### Starter code

```cpp
#include <iostream>

int add(int a, int b);

int main()
{
    int result{add(5, 3)};
    std::cout << "Result: " << result << "\n";
    return 0;
}

int add(int a, int b)
{
    return a + b;
}
```

### 1.

What function signature is needed for a `multiply` function that takes two `int` values and returns their product?

- A. `void multiply(int a, int b)`
- B. `int multiply(int a, int b)`
- C. `int multiply(int a, int b, int result)`
- D. `multiply(int a, int b)`

### 2.

What should `multiply` return?

- A. `return;`
- B. `return a + b;`
- C. `return a * b;`
- D. `return multiply(a, b);`

---

## Function overloading

### Starter code

```cpp
#include <iostream>

int add(int a, int b)
{
    std::cout << "Integer add called\n";
    return a + b;
}

double add(double a, double b)
{
    std::cout << "Double add called\n";
    return a + b;
}

int main()
{
    std::cout << add(3, 4) << "\n";
    std::cout << add(3.5, 4.2) << "\n";
    return 0;
}
```

### 3.

What `add` function is called for `add(3.0f, 4.0f)`?

- A. Integer `add`
- B. Double `add`
- C. Compilation error
- D. Runtime error

### 4.

What happens for `add(3L, 4L)`? (Use the `L` suffix for `long` literals.)

- A. Integer `add` is called
- B. Double `add` is called
- C. Compilation error (ambiguous)
- D. Runtime error

---

## Default arguments

### Starter code

```cpp
#include <iostream>
#include <string>

void greet(const std::string& name, int times = 1, char punctuation = '!')
{
    for (int i{0}; i < times; ++i)
    {
        std::cout << "Hello " << name << punctuation << " ";
    }
    std::cout << "\n";
}

int main()
{
    greet("Alice");
    greet("Bob", 2);
    greet("Charlie", 3, '?');
    return 0;
}
```

### 5.

Can you change the punctuation without specifying how many times? For example: `greet("Alice", '?')`

- A. Yes
- B. No

### 6.

Can you call `greet()` with no arguments?

- A. Yes
- B. No

---

## Forward declarations

### Starter code

```cpp
#include <iostream>

int calculate(int x);

int main()
{
    int result{calculate(5)};
    std::cout << "Result: " << result << "\n";
    return 0;
}

int calculate(int x)
{
    return x * 2 + 1;
}
```

### 7.

Will this compile if you comment out the forward declaration?

- A. Yes
- B. No

### 8.

Will this compile if you move the full definition of `calculate` above `main` and remove the forward declaration?

- A. Yes
- B. No

---

## Multiple files and headers

### Starter code

```cpp
// @file: main.cpp
#include <iostream>
#include "math_utils.h"

int main()
{
    std::cout << add(3, 4) << "\n";
    std::cout << multiply(3, 4) << "\n";
    return 0;
}

// @file: math_utils.h
#pragma once

int add(int a, int b);
int multiply(int a, int b);

// @file: math_utils.cpp
#include "math_utils.h"

int add(int a, int b)
{
    return a + b;
}

int multiply(int a, int b)
{
    return a * b;
}
```

Compile `main.cpp` and `math_utils.cpp` together.

### 9.

Why do we use `#pragma once` in the header?

- A. To prevent multiple inclusion of the same header in one translation unit
- B. To make the code compile faster
- C. To include the standard library automatically
- D. To define constants

### 10.

What files must you edit to add a `subtract` function?

- A. Only the header file
- B. Only the source file
- C. Both the header file and the source file
- D. Only `main.cpp`

---

## File writing

### Starter code

```cpp
#include <fstream>
#include <iostream>

int main()
{
    std::ofstream output{"test.txt"};

    if (output.is_open())
    {
        output << "Hello World\n";
        output << 42 << "\n";
        output.close();
        std::cout << "File written successfully\n";
    }
    else
    {
        std::cout << "Could not open file\n";
    }

    return 0;
}
```

### 11.

If you remove the `close()` line, does the file still get written eventually when the program ends?

- A. Yes
- B. No

### 12.

If you run the program again (same code, no `app` mode), what happens to `test.txt`?

- A. New lines are appended to the end
- B. The file is overwritten
- C. A compile error occurs
- D. Nothing happens to the file

---

## File reading

### Starter code

Run the **File writing** starter first so `test.txt` exists, or create `test.txt` with a few lines of text.

```cpp
#include <fstream>
#include <iostream>
#include <string>

int main()
{
    std::ifstream input{"test.txt"};
    std::string line{};

    if (input.is_open())
    {
        while (std::getline(input, line))
        {
            std::cout << "Read: " << line << "\n";
        }
        input.close();
    }
    else
    {
        std::cout << "Could not open file\n";
    }

    return 0;
}
```

### 13.

What happens if you try to open a file that does not exist?

- A. The program crashes immediately
- B. `is_open()` returns false and the program can continue
- C. A new empty file is created automatically
- D. The program waits for keyboard input

### 14.

Is `close()` required on the input stream?

- A. Yes, always
- B. No

---

## String stream parsing

### Starter code

```cpp
#include <iostream>
#include <sstream>
#include <string>

int main()
{
    std::string data{"John 25 3.14"};
    std::stringstream ss{data};

    std::string name{};
    int age{};
    double value{};

    ss >> name >> age >> value;

    std::cout << "Name: " << name;
    std::cout << ", Age: " << age;
    std::cout << ", Value: " << value << "\n";

    return 0;
}
```

### 15.

What does the starter program print?

- A. `Name: John, Age: 25, Value: 3.14`
- B. `Name: John, Age: 25, Value: 3`
- C. `Name: John, Age: 25, Value: 3.1`
- D. Compilation error

### 16.

Change `data` to `""` and run again. What is a reasonable output?

- A. `Name: , Age: 0, Value: 0`
- B. `Name: , Age: 0, Value: 0.0` (always distinct from A on every system)
- C. Undefined behavior only
- D. Compilation error

### 17.

What should you do for stronger input validation when parsing from a string stream?

- A. Check whether each extraction succeeded
- B. Use `eof()` to ensure the whole string was consumed
- C. Both A and B
- D. No validation is ever needed

---

## String stream validation

### Starter code

```cpp
#include <iostream>
#include <sstream>
#include <string>

bool isValidInteger(const std::string& input)
{
    std::stringstream ss{input};
    int value{};
    return (ss >> value) && ss.eof();
}

int main()
{
    std::cout << std::boolalpha;
    std::cout << isValidInteger("123") << "\n";
    std::cout << isValidInteger("12.5") << "\n";
    std::cout << isValidInteger("abc") << "\n";
    return 0;
}
```

### 18.

Why is `eof()` needed in `isValidInteger`?

- A. To check whether the stream object is empty
- B. To ensure every character was consumed (no extra characters after the number)
- C. To make the function run faster
- D. To prevent compilation errors

### 19.

If you remove `eof()`, which input would be wrongly accepted as valid?

- A. `"123abc"`
- B. `"123"`
- C. `"abc"`
- D. `"0"`

---

## Complete file processing

### Starter code

```cpp
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

int main()
{
    std::ofstream out{"students.txt"};
    out << "Alice 85 92 78\n";
    out << "Bob 90 88 95\n";
    out.close();

    std::ifstream in{"students.txt"};
    std::string line{};

    while (std::getline(in, line))
    {
        std::stringstream ss{line};
        std::string name{};
        int grade1{};
        int grade2{};
        int grade3{};

        ss >> name >> grade1 >> grade2 >> grade3;
        int average{(grade1 + grade2 + grade3) / 3};

        std::cout << name << ": " << average << "\n";
    }

    return 0;
}
```

### 20.

Is `out.close()` needed for this program to write data before `in` opens `students.txt`?

- A. Yes
- B. No

### 21.

Why?

- A. The output buffer may not be flushed to disk until the stream is closed or flushed
- B. It is only good style, never required for correctness
- C. The program will not compile without `close()`
- D. `close()` prevents memory leaks

---

## Error handling

### Starter code

```cpp
#include <fstream>
#include <iostream>

int main()
{
    std::ifstream input{"nonexistent.txt"};

    if (input.is_open())
    {
        std::cout << "File opened successfully\n";
        input.close();
    }
    else
    {
        std::cout << "File could not be opened\n";
    }

    return 0;
}
```

### 22.

Create a file named `test.txt`, then change the code to open `"Test.txt"` instead. What happens?

- A. It always opens on every operating system
- B. It never opens on any operating system
- C. It depends on the operating system (case sensitivity)

---

## Function scope

### Starter code

```cpp
#include <iostream>

int globalVar{10};

void testFunction()
{
    int localVar{5};
    std::cout << "Global: " << globalVar << "\n";
    std::cout << "Local: " << localVar << "\n";
}

int main()
{
    int localVar{20};
    testFunction();
    std::cout << "Main local: " << localVar << "\n";
    return 0;
}
```

### 23.

Does `testFunction` change the `localVar` in `main`?

- A. Yes
- B. No

### 24.

If `testFunction` changes `globalVar`, will `main` see the new value when it prints `globalVar` afterward?

- A. Yes
- B. No
