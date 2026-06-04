# Extraction and Whitespace

The extraction operator `>>` pulls formatted data **out of an input stream** and into a variable.

You used it with `std::cin` before.  The same rules apply to file and string streams later.

## How `>>` behaves

For built-in types like `int` and `double`, `>>`:

1. skips leading **whitespace** (spaces, tabs, newlines)
2. reads characters that fit the target type
3. stops at the first character that does not fit

```cpp
#include <iostream>

int main()
{
    int a{};
    int b{};

    std::cout << "Enter two integers: ";
    std::cin >> a >> b;

    std::cout << "a = " << a << ", b = " << b << "\n";
    return 0;
}
```

Input `3   14` works. Extra spaces between tokens are fine.

## Whitespace can surprise you

`>>` reads **one word at a time** when the target is a `std::string` without `std::getline`.

```cpp
#include <iostream>
#include <string>

int main()
{
    std::string word{};

    std::cout << "Enter a phrase: ";
    std::cin >> word;

    std::cout << "You entered: " << word << "\n";
    return 0;
}
```

If you type `hello world`, only `hello` is stored. The space stopped the read. `world` stays in the input buffer for a later `>>`.

That is why full names and full lines need `std::getline`, covered in the next chapter.

## Reading the wrong type

If the stream cannot parse the value, the read **fails** and the stream enters a **fail** state.

```cpp
#include <iostream>

int main()
{
    int age{};

    std::cout << "Enter your age: ";
    std::cin >> age;

    if (std::cin.fail())
    {
        std::cout << "Input failed.\n";
    }
    else
    {
        std::cout << "Age: " << age << "\n";
    }

    return 0;
}
```

Type `Asdf` when the program expects an `int`. The read fails. You will learn to recover in later in this chapter.

## Leftover input stays in the buffer

After a failed or partial read, extra characters may still wait in the stream.

Example: user types `42abc` for an integer read.

- `42` may be stored
- `abc` may remain for the next operation

Always think about what is still in the buffer after `>>`.

## Insertion with `<<`

Output uses `<<` to **insert** values into an output stream.

```cpp
#include <iostream>

int main()
{
    int wins{3};
    int losses{1};

    std::cout << "Record: " << wins << "-" << losses << "\n";
    return 0;
}
```

Chaining works because each `<<` returns the stream on the left.

## Try it now

### Exercise 1: Two tokens

Prompt: Read two words with `>>` and print both. Type `alpha beta` and then `alpha beta gamma` on separate runs. What is left in the buffer the second time?

```cpp
#include <iostream>
#include <string>

int main()
{
    std::string first{};
    std::string second{};

    std::cout << "Enter two words: ";
    std::cin >> first >> second;

    std::cout << first << " | " << second << "\n";
    return 0;
}
```

### Exercise 2: Predict the failure

Prompt: Before running, predict what happens if you type `ten` when asked for an `int`.

```cpp
#include <iostream>

int main()
{
    int n{};

    std::cout << "Enter n: ";
    std::cin >> n;

    std::cout << "n = " << n << "\n";
    return 0;
}
```
