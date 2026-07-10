# Conversion Operators and References

## User-defined conversions

A **conversion operator** lets the compiler convert your type to another type when needed.

```cpp
#include <iostream>

class Meters
{
public:
    explicit Meters(double value)
        : value_{value}
    {
    }

    double value() const { return value_; }

    explicit operator double() const
    {
        return value_;
    }
};

int main()
{
    Meters m{1.5};
    double d{static_cast<double>(m)};
    std::cout << d << '\n';
    return 0;
}
```

`explicit operator double()` blocks silent conversion in many contexts; callers must **`static_cast<double>(m)`** unless the context allows explicit conversion.

Without `explicit`, `double d = m;` could compile. That is sometimes convenient and often surprising.

## Returning references from operators

| Operator | Return | Reason |
|----------|--------|--------|
| `operator[]` (non-const) | `T&` | Allow assignment to element |
| `operator()` (non-const) | `T&` | Same |
| `operator<<` | `std::ostream&` | Chain output |
| `operator=` | `T&` | Chain assignment (`a = b = c`) |
| `operator+` | Usually **by value** | Result is a new object |

```cpp
class Buffer
{
public:
    int& operator[](std::size_t i)
    {
        return data_[i];
    }

    const int& operator[](std::size_t i) const
    {
        return data_[i];
    }

private:
    int data_[10]{};
};
```

Returning a reference to a **local** variable is undefined behavior. Only return references to members or other storage that outlives the call.

## Assignment vs arithmetic

```cpp
Fraction& operator=(const Fraction& other);   // member, returns *this
Fraction operator+(const Fraction& other) const;  // often returns new Fraction
```

Assignment mutates the left object; `+` usually produces a new value.

## Chapter summary

| Topic | Takeaway |
|-------|----------|
| Syntax | `a + b` → `operator+(a, b)` |
| Limits | No new symbols; user types only |
| Style | Member, friend, or free; pick by left operand and access |
| Streams | `<<` / `>>` as non-member; return the stream |
| Compare | Define `==` and `<`; derive the rest |
| `[]` / `()` | One arg vs variadic; references for mutating access |
| Conversions | Use `explicit` unless implicit is truly safe |

## Try it now

### Exercise 1: `explicit` conversion

Prompt: `Meters` has `explicit operator double()`. Does `double d = m;` compile?

:::details Answer

**No** (without another conversion path). Use **`static_cast<double>(m)`** or **`m.value()`**.

:::

### Exercise 2: Reference danger

Prompt: Can `operator+` return `Fraction&` referring to a local `Fraction`?

:::details Answer

**No.** The local is destroyed when the function returns; the reference would dangle. Return **`Fraction`** by value.

:::

### Exercise 3: Pull it together

Prompt: Design `Vec2` with `operator+`, `operator<<`, and `operator<` (sort by length). Which should be member vs friend?

:::details Answer

**`+`**: member or friend. **`<<`**: friend/free (left operand is stream). **`<`**: member comparing `x*x + y*y` or similar. Any approach that keeps private `x`, `y` consistent is fine if `<<` is not a member of `Vec2`.

:::
