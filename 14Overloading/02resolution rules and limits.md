# Resolution, Rules, and Limits

Operator overloads follow the same **overload resolution** ideas as ordinary functions: the compiler looks for a **good match**. If more than one overload fits equally well, the call is **ambiguous** and does not compile.

## Good match vs ambiguous

```cpp
#include <iostream>

class Vec2
{
public:
    int x{};
    int y{};
};

Vec2 operator+(const Vec2& a, const Vec2& b)
{
    return Vec2{a.x + b.x, a.y + b.y};
}

Vec2 operator+(const Vec2& a, int offset)
{
    return Vec2{a.x + offset, a.y + offset};
}

int main()
{
    Vec2 a{1, 2};
    Vec2 b{3, 4};

    Vec2 c{a + b};
    Vec2 d{a + 2};

    // Vec2 e{a + 2.5};  // error: ambiguous or no match

    std::cout << c.x << ' ' << d.x << '\n';
    return 0;
}
```

`a + b` picks the two-`Vec2` overload. `a + 2` picks `Vec2 + int`. A call with no clear best overload fails at compile time, same spirit as [function overloading](../02Functions/13function%20overloading.md).

## What you cannot overload

| Cannot overload | Examples |
|-----------------|----------|
| Scope resolution | `::` |
| Member access | `.` `.*` |
| Conditional | `?:` |
| Sizeof / alignof | `sizeof` `alignof` |
| `typeid` | `typeid` |
| `static_cast`, etc. | Built-in cast keywords |

You also **cannot invent** new operator symbols. Only existing C++ operators can be given meaning for your types.

## What stays the same

**Precedence** and **associativity** do not change. `*` still binds tighter than `+` whether or not you overload them.

```
a + b * c   // still multiplies b and c first, then adds a
```

## User-defined types only

Overloading lets you define what `+` means for **your** `Fraction`, not for built-in `int`. The left and right operands must include at least one user-defined type (with a few exceptions for enums).

## Try it now

### Exercise 1: Ambiguity

Prompt: Two `operator+` overloads both take two `Vec2` parameters with different return types. Is that valid?

:::details Answer

**No.** Return type is not part of overload resolution. The declarations conflict.

:::

### Exercise 2: Precedence

Prompt: You overload `+` and `*` for a class `M`. Does `a + b * c` use your overloads with normal precedence?

:::details Answer

**Yes.** Precedence is unchanged; `b * c` is grouped first, then `+`.

:::
