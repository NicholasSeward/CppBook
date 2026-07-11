# Unary and Relational Operators

## Unary operators

Unary operators take one operand. They are almost always **member functions** because the operand is your object.

| Operator | Meaning (typical) |
|----------|-------------------|
| `-` | Negation |
| `+` | Unary plus (rare) |
| `!` | Logical not |
| `++` `--` | Pre/post increment |
| `*` `&` | Dereference / address (smart pointers) |

```cpp
#include <iostream>

class Counter
{
public:
    explicit Counter(int value = 0)
        : value_{value}
    {
    }

    int get() const { return value_; }

    Counter operator-() const
    {
        return Counter{-value_};
    }

    Counter& operator++()
    {
        ++value_;
        return *this;
    }

    Counter operator++(int)
    {
        Counter before{value_};
        ++value_;
        return before;
    }

private:
    int value_{};
};

int main()
{
    Counter c{5};
    Counter neg{-c};
    std::cout << neg.get() << '\n';

    Counter a{10};
    std::cout << (++a).get() << ' ' << (a++).get() << ' ' << a.get() << '\n';
    return 0;
}
```

`operator++()` is **prefix**; `operator++(int)` is **postfix** (dummy `int` parameter).

## Relational operators

For ordering and equality, overload **`==`** and **`<`** first. Many algorithms (including `std::sort`) need **`<`** or a custom comparator.

```cpp
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

class Student
{
public:
    Student(std::string name, int score)
        : name_{std::move(name)}
        , score_{score}
    {
    }

    const std::string& name() const { return name_; }
    int score() const { return score_; }

    bool operator<(const Student& other) const
    {
        return score_ < other.score_;
    }

    bool operator==(const Student& other) const
    {
        return score_ == other.score_ && name_ == other.name_;
    }

private:
    std::string name_;
    int score_{};
};

int main()
{
    std::vector<Student> roster{
        Student{"Ada", 95},
        Student{"Bob", 88},
        Student{"Cleo", 92}};

    std::sort(roster.begin(), roster.end());

    for (const Student& s : roster)
    {
        std::cout << s.name() << ": " << s.score() << '\n';
    }
    return 0;
}
```

`std::sort` uses `operator<` by default for `Student`.

## Try it now

### Exercise 1: Postfix vs prefix

Prompt: Which overload runs for `c++`, `operator++()` or `operator++(int)`?

:::details Answer

**`operator++(int)`** (postfix). No argument between `++` and `;` still means postfix when the expression uses the old value; the `int` dummy distinguishes the overload.

:::

### Exercise 2: Same score, different names

Prompt: `Student ada{"Ada", 95};` `Student cleo{"Cleo", 95};` What are the values of `ada < cleo`, `cleo < ada`, and `ada == cleo`?

:::details Answer

**`false`**, **`false`**, **`false`**.

**`<`** compares **score** only, so neither student is less than the other when scores match. **`==`** also checks **name**, so Ada and Cleo are not equal even with the same score.

:::
