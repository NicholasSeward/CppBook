# Type Aliases

Sometimes a type name is long, noisy, or tied to a specific meaning in your program.

A type alias gives an existing type another name.

## A Simple Alias

Use `using` to create a type alias.

```cpp
#include <iostream>

int main()
{
    using Score = int;

    Score playerScore{100};

    std::cout << "Score: " << playerScore << "\n";
    return 0;
}
```

`Score` is not a brand-new kind of number. It is another name for `int`.

This can make code read more clearly when the meaning matters.

## Do Not Hide Simple Types

Aliases can also make code harder to read when they hide something simple.

```cpp
#include <iostream>

int main()
{
    using Number = int;

    Number age{20};

    std::cout << age << "\n";
    return 0;
}
```

This works, but `Number` does not tell us much. `int age{20};` is probably clearer.

PREFERENCE: Do not alias fundamental types unless the alias communicates real meaning. `Health`, `Score`, or `UserId` can be useful. `Number` usually is not.

## Aliases for Long Types

Aliases are more useful when a type name gets long.

```cpp
#include <iostream>
#include <vector>

int main()
{
    using Matrix = std::vector<std::vector<int>>;

    Matrix grid{
        {1, 2, 3},
        {4, 5, 6}
    };

    std::cout << grid.at(0).at(0) << "\n";
    std::cout << grid.at(1).at(2) << "\n";

    return 0;
}
```

Without the alias, the variable declaration would be much longer:

```
std::vector<std::vector<int>> grid
```

The alias lets the code say `Matrix`, which is closer to the idea the program is using.

## Aliases Do Not Add Type Safety

An alias is just another name for the same type.

```cpp
#include <iostream>

int main()
{
    using Health = int;
    using Score = int;

    Health health{100};
    Score score{50};

    health = score;

    std::cout << "Health: " << health << "\n";
    return 0;
}
```

C++ allows `health = score;` because both aliases are still `int`.

If you need a value to be one of a fixed set of named choices, use an enumeration. If you need to group multiple values together, use a struct.
