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

private:
    double value_{};
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
#include <iostream>

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

int main()
{
    Buffer b;
    b[0] = 42;          // non-const operator[] returns int&, so assignment works
    b[1] = b[0] + 1;

    const Buffer& cb{b};
    std::cout << cb[0] << ' ' << cb[1] << '\n';  // const operator[]
    return 0;
}
```

Returning a reference to a **local** variable is undefined behavior. Only return references to members or other storage that outlives the call.

## Assignment vs arithmetic

Assignment mutates the left object and returns `*this` (so `a = b = c` chains); `+` usually produces a new value.

```cpp
#include <iostream>

class Fraction
{
public:
    Fraction(int num = 0, int den = 1)
        : numerator_{num}
        , denominator_{den}
    {
    }

    Fraction& operator=(const Fraction& other)   // returns *this
    {
        numerator_ = other.numerator_;
        denominator_ = other.denominator_;
        return *this;
    }

    Fraction operator+(const Fraction& other) const  // returns a new Fraction
    {
        return Fraction{
            numerator_ * other.denominator_ + other.numerator_ * denominator_,
            denominator_ * other.denominator_};
    }

    void print() const
    {
        std::cout << numerator_ << '/' << denominator_ << '\n';
    }

private:
    int numerator_{};
    int denominator_{};
};

int main()
{
    Fraction a;
    Fraction b;
    Fraction c{1, 4};

    a = b = c;          // chained assignment via operator= returning *this
    a.print();

    Fraction sum{c + Fraction{1, 4}};  // operator+ returns a fresh value
    sum.print();
    return 0;
}
```

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
