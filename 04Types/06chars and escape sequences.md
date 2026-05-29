# Characters and Escape Sequences

`char` stores a single character.

## `char` and character literals

A character literal uses single quotes:

```
char letter{'A'};
char digit{'5'};
```

## ASCII and code points

Computers store characters as numbers. A common historical mapping is [ASCII](https://en.wikipedia.org/wiki/ASCII). In ASCII:

- `'A'` is 65
- `'0'` is 48

You can convert a `char` to an `int` to see the numeric code:

```cpp
#include <iostream>

int main()
{
    char c{'A'};
    std::cout << c << '\n';
    std::cout << static_cast<int>(c) << '\n';
    return 0;
}
```

> NOTE: The conversion uses `static_cast<int>(c)`. That is a safe, explicit conversion. You will learn more in the conversions chapter.

## `'5'` is not `5`

This is a classic beginner confusion:

- `5` is an integer literal with value five
- `'5'` is a character literal, usually with numeric code 53 in ASCII

```cpp
#include <iostream>

int main()
{
    std::cout << 5 << '\n';
    std::cout << '5' << '\n';
    std::cout << static_cast<int>('5') << '\n';
    return 0;
}
```

## Reading a `char` with `std::cin`

`std::cin >> c` reads the next non whitespace character (it skips spaces and newlines).

```cpp
#include <iostream>

int main()
{
    char c{};
    std::cout << "Type a character: ";
    std::cin >> c;
    std::cout << "You typed: " << c << '\n';
    return 0;
}
```

If you want to read the next character even if it is a space, use `std::cin.get(c)`:

```cpp
#include <iostream>

int main()
{
    char c{};
    std::cout << "Type a character (space allowed): ";
    std::cin.get(c);
    std::cout << "You typed: [" << c << "]\n";
    return 0;
}
```

> NOTE: In beginner code you usually read tokens (words and numbers), not single raw characters. This section is here to show what the tools do.

## Escape sequences

Some characters are hard to type directly, such as a newline or a tab. C++ uses escape sequences that start with a backslash (`\`).

Common ones:

| Escape | Meaning |
|--------|---------|
| `\n` | newline |
| `\t` | tab |
| `\r` | carriage return |
| `\b` | backspace |
| `\a` | bell |
| `\\` | a literal backslash |
| `\'` | a literal single quote |
| `\"` | a literal double quote |

`'\n'` is a valid character literal. It represents one character (newline).

Example:

```cpp
#include <iostream>

int main()
{
    std::cout << "Column1\tColumn2\n";
    std::cout << "A\tB\n";
    std::cout << "Backslash: \\ \n";
    return 0;
}
```

### Hex and Unicode escapes

There are also escape forms for raw byte values and Unicode code points:

| Escape | Example | Meaning |
|--------|---------|---------|
| `\xNN` | `\x41` | a byte value in hex (implementation details apply) |
| `\uNNNN` | `\u2665` | a Unicode code point (16 bit form) |
| `\UNNNNNNNN` | `\U0001F600` | a Unicode code point (32 bit form) |

> NOTE: Unicode output depends on your terminal and font. It may print correctly, print as squares, or not print at all.

#### Example: Printing Unicode Playing Card Suits

You can use Unicode escape sequences to print symbols:

```cpp
#include <iostream>

int main()
{
    // Unicode code points for card suits
    std::cout << "Spades: \u2660\n";   // ♠
    std::cout << "Hearts: \u2665\n";   // ♥
    std::cout << "Diamonds: \u2666\n"; // ♦
    std::cout << "Clubs: \u2663\n";    // ♣
    return 0;
}
```

On a supporting terminal, this produces:
```
Spades: ♠
Hearts: ♥
Diamonds: ♦
Clubs: ♣
```

### Using Color in Output

You can also change the color of your terminal output by printing ANSI escape codes. Commonly, these are supported in terminals on Linux, macOS, and some Windows setups.

- `\033[31m` sets the text color to red.
- `\033[0m` resets formatting to default.

#### Example: Printing Suits with Color

```cpp
#include <iostream>

int main()
{
    // Print heart and diamond in red,
    // spade and club in default color

    std::cout << "Spades: \u2660\n";
    std::cout << "\033[31mHearts: \u2665\n";
    std::cout << "Diamonds: \u2666\n\033[0m";
    std::cout << "Clubs: \u2663\n";
    return 0;
}
```

To print both hearts and diamonds in red, reset the color after them:
```
std::cout << "\033[31mHearts: \u2665\nDiamonds: \u2666\n\033[0m";
```
(And print the others normally.)

> NOTE: Not all terminals support color codes, but most modern ones do. If the colors do not show as expected, check your terminal settings.