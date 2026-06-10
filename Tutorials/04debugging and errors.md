# Tutorial: Debugging and Errors (Module 4)

Go play with and run the code below. You can use CodeBin, Codespaces, TxtBook, or whatever environment you like. Run it and get a feel for the code before you answer each question.

Work through each section in order. Change only what each question asks for unless a question says to keep earlier edits.

Related chapters: [03 Debugging And Errors](../03DebuggingAndErrors/README.md).

---

## Informal testing

### Starter code

```cpp
#include <iostream>

double add(double a, double b)
{
    return a + b;
}

int main()
{
    std::cout << "Test 1: " << ((add(2, 3) == 5) ? "Pass" : "Fail") << ' ';
    std::cout << "Test 2: " << ((add(-1, -1) == -2) ? "Pass" : "Fail") << ' ';
    std::cout << "Test 3: " << ((add(-.1, -1) == -1.1f) ? "Pass" : "Fail") << '\n';
    return 0;
}
```

### 1.

What will this program output?

- A. Test 1: Pass; Test 2: Pass; Test 3: Pass
- B. Test 1: Pass; Test 2: Pass; Test 3: Fail
- C. Test 1: Pass; Test 2: Fail; Test 3: Pass
- D. Test 1: Pass; Test 2: Fail; Test 3: Fail
- E. Test 1: Fail; Test 2: Pass; Test 3: Pass
- F. Test 1: Fail; Test 2: Pass; Test 3: Fail
- G. Test 1: Fail; Test 2: Fail; Test 3: Fail

### 2.

If any test failed, is it a fault in the test or the `add` function?

- A. faulty test
- B. faulty function

---

## Code coverage

### Starter code

```cpp
#include <iostream>

int divide(int a, int b)
{
    if (b == 0)
    {
        std::cout << "Error: Division by zero\n";
        return 0;
    }

    return a / b;
}

int main()
{
    std::cout << divide(10, 2) << '\n'; // Test case 1
    std::cout << ____________ << '\n'; // Test case 2
    return 0;
}
```

### 3.

What call should replace `____________` to complete branch coverage? (The error message should get printed.)

- A. `divide(2, 10)`
- B. `divide(2, 0)`
- C. `divide(2, -1)`
- D. `divide(1, 1)`

---

## Logic errors

### Starter code

```cpp
#include <iostream>

bool isEven(int n)
{
    return n % 2;
}

int main()
{
    std::cout << std::boolalpha << isEven(4) << '\n';
    return 0;
}
```

### 4.

What will this program print?

- A. `true`
- B. `false`
- C. `1`
- D. `0`

### 5.

Pick **all** options you could replace `return n % 2;` with to remove the logic error.

- A. `return n % 2 == 1;`
- B. `return n % 2 == 0;`
- C. `return n % 2 < 1;`
- D. `return 1 - n % 2;`

---

## Exceptions

### Starter code

```cpp
#include <iostream>
#include <stdexcept>

void checkValue(int x)
{
    if (x < 0)
    {
        throw std::runtime_error("Negative value error");
    }

    std::cout << "Valid number: " << x << '\n';
}

int main()
{
    try
    {
        checkValue(5);
        checkValue(-1);
    }
    catch (const std::exception& e)
    {
        std::cout << "Caught: " << e.what() << '\n';
    }

    return 0;
}
```

### 6.

The last line of the output will be: ___________

### 7.

`checkValue(5)` executes fully with no errors.

- A. True
- B. False

---

## `std::cin` failure

### Starter code

```cpp
#include <iostream>

int main()
{
    int num{};

    std::cout << "Enter a number: ";
    std::cin >> num;

    if (std::cin.fail())
    {
        std::cout << "Invalid input detected\n";
    }
    else
    {
        std::cout << "You entered: " << num << '\n';
    }

    return 0;
}
```

### 8.

What happens if the user enters `abc`?

- A. The program crashes
- B. It prints `You entered: abc`
- C. It prints `Invalid input detected`
- D. It asks for input again

---

## Recovering from `std::cin` failure

### Starter code

```cpp
#include <iostream>

int main()
{
    int num{};

    std::cout << "Enter a number: ";
    std::cin >> num;

    if (std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cout << "Invalid input cleared!\n";
    }

    return 0;
}
```

### 9.

What does `std::cin.ignore(10000, '\n')` do?

- A. Clears only the error flag
- B. Ignores up to 10,000 characters or until a newline
- C. Ends the program
- D. Resets `num` to zero

---

## `assert`

### Starter code

```cpp
#include <cassert>
#include <cmath>
#include <iostream>

double findHypotenuse(double a, double b)
{
    double hypotenuse{std::sqrt(a * a + b * b)};
    assert(hypotenuse > 0);
    return hypotenuse;
}

int main()
{
    double x{3.0};
    double y{4.0};
    std::cout << "Hypotenuse: " << findHypotenuse(x, y) << '\n';
    return 0;
}
```

### 10.

What will happen when `findHypotenuse(3, 4)` is called?

- A. It prints `Hypotenuse: 5`
- B. The program crashes with an assertion failure
- C. It prints `Hypotenuse: 0`
- D. The program does nothing

### 11.

`findHypotenuse(_____, _____)` will cause the assertion to fail.

Fill in both arguments (two blanks).
