# Formatting Output Streams

`std::cout << value` prints a default representation.

Sometimes you want fixed decimal places, aligned columns, or clearer `bool` output.

C++ formatting applies to **output streams** like `std::cout` and `std::ofstream`.

## Manipulators and flags

You can change format in two main ways:

1. **Manipulators** from `<iomanip>` (friendly for beginners)
2. **Format flags** with `setf` / `unsetf` on the stream

This chapter focuses on manipulators. Flags are the lower-level switchboard behind many manipulators.

```cpp
#include <iomanip>
#include <iostream>

int main()
{
    double pi{3.14159265};

    std::cout << std::fixed << std::setprecision(2) << pi << "\n";
    std::cout << std::defaultfloat << pi << "\n";

    return 0;
}
```

## Common format controls

| Control | Effect |
|---------|--------|
| `std::boolalpha` | print `true` / `false` for `bool` |
| `std::noboolalpha` | print `1` / `0` for `bool` |
| `std::showpos` | show `+` on positive numbers |
| `std::noshowpos` | hide `+` on positives |
| `std::fixed` | fixed-point notation |
| `std::scientific` | scientific notation |
| `std::defaultfloat` | restore default float style |
| `std::setprecision(n)` | digits after decimal (with `fixed`) or significant digits (default) |
| `std::setw(n)` | minimum field width for the **next** output only |
| `std::setfill(ch)` | pad character when width is used |
| `std::left` / `std::right` / `std::internal` | alignment inside the field |

Some flags replace others. For example, `std::fixed` and `std::scientific` fight over how floating-point values print.

```cpp
#include <iomanip>
#include <iostream>

int main()
{
    bool ready{true};

    std::cout << std::boolalpha << ready << "\n";
    std::cout << std::noboolalpha << ready << "\n";

    return 0;
}
```

## Precision

`std::setprecision` changes how many digits appear, but the meaning depends on other flags.

With `std::fixed`, precision is usually **digits after the decimal point**:

```cpp
#include <iomanip>
#include <iostream>

int main()
{
    double price{19.5};

    std::cout << std::fixed << std::setprecision(2) << price << "\n";
    return 0;
}
```

Output: `19.50`

## Width, fill, and justification

Column output is easier with width and fill:

```cpp
#include <iomanip>
#include <iostream>
#include <string>

int main()
{
    std::cout << std::left << std::setw(12) << std::setfill('.') << "Name"
              << std::setw(8) << std::setfill(' ') << 42 << "\n";

    std::cout << std::left << std::setw(12) << "Score" << std::right << std::setw(8) << 97 << "\n";

    return 0;
}
```

`std::setw` affects only the **next** value printed. Set it again for each column if needed.

> PREFERENCE: Use `<iomanip>` manipulators in student programs. They read clearly. Reach for `setf` when you are matching library code that already uses flags.

## Flags with `setf`

Example of the flag style:

```cpp
#include <iostream>

int main()
{
    std::cout.setf(std::ios::fixed);
    std::cout.precision(2);
    std::cout << 3.14159 << "\n";
    return 0;
}
```

Manipulators often expand to similar flag changes.

## Try it now

### Exercise 1: Money format

Prompt: Print `12.5` as `12.50` using `fixed` and `setprecision(2)`.

```cpp
#include <iostream>

int main()
{
    double amount{12.5};

    // TODO: Print with two digits after the decimal point.

    return 0;
}
```

### Exercise 2: Simple table

Prompt: Print two rows of labels and numbers in aligned columns.

```cpp
#include <iomanip>
#include <iostream>
#include <string>

int main()
{
    // TODO: Print "Wins" and 10 in a neat row.
    // TODO: Print "Losses" and 3 in a neat row.

    return 0;
}
```
