# Function Overloading

Imagine you want one function named `add` for integers and another for `double` values.

You could write two different names:

```
addInt
addDouble
```

C++ lets you use the **same function name** when the parameter lists differ. That is **function overloading**.

## Two `add` functions

```cpp
#include <iostream>

int add(int left, int right)
{
    return left + right;
}

double add(double left, double right)
{
    return left + right;
}

int main()
{
    std::cout << add(3, 4) << "\n";
    std::cout << add(3.5, 2.5) << "\n";

    return 0;
}
```

The compiler picks the version based on the argument types.

- `add(3, 4)` uses the `int` version
- `add(3.5, 2.5)` uses the `double` version

## Return type is not part of the choice

Overloading is based on the function name plus the parameter list.

The return type is **not** used to choose which overload wins.

This will not compile:

```cpp
int getValue();
double getValue();
```

Both declarations have the same name and the same parameter list (empty). The compiler treats that as a redefinition, not as overloading.

> PREFERENCE: If two functions do the same job with small differences in inputs, use overloading to keep one clear name. Do not try to overload on return type alone.

## How the compiler chooses

When you call an overloaded function, the compiler roughly follows this order:

1. Match the number of arguments
2. Among those, look for the best type match
3. Ignore the return type

If more than one overload fits equally well, the call is **ambiguous** and the program will not compile.

## Different number of parameters

```cpp
#include <iostream>
#include <string>

void printValue(int value)
{
    std::cout << value << "\n";
}

void printValue(int value, const std::string& label)
{
    std::cout << label << ": " << value << "\n";
}

int main()
{
    printValue(42);
    printValue(42, "Score");

    return 0;
}
```

`printValue(42)` uses the one-argument version.

`printValue(42, "Score")` uses the two-argument version.

## Widening conversions

You may notice that a function taking `double` can be called with an `int`:

```cpp
#include <iostream>

double add(double left, double right)
{
    return left + right;
}

int main()
{
    std::cout << add(3, 4) << "\n";
    return 0;
}
```

`3` and `4` are `int` values, but C++ can convert them to `double` for the call.

That is a **widening** or **promotion** style conversion.

## Ambiguous calls

Ambiguity appears when more than one overload is an equally good match.

```cpp
#include <iostream>

void report(int value)
{
    std::cout << "int: " << value << "\n";
}

void report(double value)
{
    std::cout << "double: " << value << "\n";
}

int main()
{
    report(5);
    return 0;
}
```

`report(5)` is fine. The `int` version is an exact match.

This is ambiguous:

```cpp
#include <iostream>

void scale(int value, int factor)
{
    std::cout << "int version\n";
}

void scale(double value, double factor)
{
    std::cout << "double version\n";
}

int main()
{
    scale(2, 3.0);
    return 0;
}
```

`scale(2, 3.0)` can match more than one overload after conversions. The compiler reports an ambiguous call.

> NOTE: Do not panic when you see an ambiguity error. It usually means you need to make the argument types clearer, often with an explicit cast.

## Fixing ambiguity with a cast

```cpp
scale(static_cast<double>(2), 3.0);
```

The cast tells the compiler which overload you intend.

## Perfect match first

The compiler prefers an exact type match when one exists.

If no exact match exists, it considers conversions. That is when multiple overloads can tie.

If the compiler complains, read the error and adjust the argument types on purpose.

## Try it now

### Exercise 1: Two overloads

Prompt: Write `print` overloads for `int` and `double`. Call each once from `main`.

```cpp
#include <iostream>

// TODO: Write print(int) and print(double).

int main()
{
  // TODO: Call both overloads.

    return 0;
}
```

### Exercise 2: Spot the ambiguity

Prompt: Before compiling, predict whether `pick(1, 2.0)` is valid.

```cpp
#include <iostream>

void pick(int a, int b)
{
    std::cout << "both int\n";
}

void pick(double a, double b)
{
    std::cout << "both double\n";
}

int main()
{
    pick(1, 2.0);
    return 0;
}
```
