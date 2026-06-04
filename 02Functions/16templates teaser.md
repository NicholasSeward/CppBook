# Templates Teaser

Function overloading and default arguments solve many "same idea, slightly different types or counts" problems.

**Templates** go further. They let the compiler generate the right version of a function from a pattern.

This is a preview. You will study templates in more depth later.

## The problem again

Without templates, you might write:

```cpp
int add(int left, int right)
{
    return left + right;
}

double add(double left, double right)
{
    return left + right;
}

std::string concatenate(const std::string& left, const std::string& right)
{
    return left + right;
}
```

The logic is the same. Only the types change.

## A simple function template

```cpp
#include <iostream>
#include <string>

template <typename T>
T add(T left, T right)
{
    return left + right;
}

int main()
{
    std::cout << add(3, 4) << "\n";
    std::cout << add(3.5, 2.5) << "\n";
    std::cout << add(std::string{"hi"}, std::string{"!"}) << "\n";

    return 0;
}
```

`T` stands for the type the compiler deduces from the arguments.

- `add(3, 4)` uses `int`
- `add(3.5, 2.5)` uses `double`
- the string call uses `std::string`

One pattern. Many concrete functions generated as needed.

## Template vs overloading

| Approach | Idea |
|----------|------|
| Overloading | you write each version by hand |
| Default args | one function, some parameters optional |
| Templates | one pattern, compiler generates versions |

Templates are powerful, but they also add complexity. Errors can become long and harder to read at first.

## What to remember now

- Templates are not magic syntax. They are a way to reuse code across types.
- `template <typename T>` introduces a type parameter.
- The compiler figures out `T` from how you call the function in many simple cases.
- You will return to templates when the book covers generic programming in detail.

> NOTE: Overloading and default arguments are enough for many beginner programs. Templates become important when you want one algorithm to work for many types without writing every version yourself.

## Try it now

### Exercise 1: Use the template

Prompt: Add a call that uses `add` with two `double` values and print the result.

```cpp
#include <iostream>

template <typename T>
T add(T left, T right)
{
    return left + right;
}

int main()
{
    std::cout << add(10, 20) << "\n";

    // TODO: Call add with two doubles.

    return 0;
}
```
