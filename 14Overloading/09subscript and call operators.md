# Subscript and Call Operators

## `operator[]`

`operator[]` makes indexing syntax work: `container[i]`.

Rules:

- **One parameter** only (no `operator[](i, j)`; use `operator()` for that).
- Parameter type is up to you: `int`, `std::string`, enum, etc.
- Often returns a **reference** so `obj[i] = value` works.

```cpp
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

class LabeledValues
{
public:
    void add(const std::string& key, int value)
    {
        keys_.push_back(key);
        values_.push_back(value);
    }

    int& operator[](const std::string& key)
    {
        for (std::size_t i = 0; i < keys_.size(); ++i)
        {
            if (keys_[i] == key)
            {
                return values_[i];
            }
        }
        throw std::out_of_range{"unknown key"};
    }

    const int& operator[](const std::string& key) const
    {
        for (std::size_t i = 0; i < keys_.size(); ++i)
        {
            if (keys_[i] == key)
            {
                return values_[i];
            }
        }
        throw std::out_of_range{"unknown key"};
    }

private:
    std::vector<std::string> keys_;
    std::vector<int> values_;
};

int main()
{
    LabeledValues stats;
    stats.add("wins", 3);
    stats.add("losses", 1);

    stats["wins"] = 4;
    std::cout << stats["wins"] << '\n';
    return 0;
}
```

Provide **const** and **non-const** overloads when reads and writes both matter.

## `operator()`

The **function call** operator lets objects behave like functions. That is useful for functors and multi-index access.

```cpp
#include <iostream>
#include <vector>

class Matrix
{
public:
    Matrix(int rows, int cols, int fill = 0)
        : data_(rows * cols, fill)
        , rows_{rows}
        , cols_{cols}
    {
    }

    int& operator()(int row, int col)
    {
        return data_[row * cols_ + col];
    }

    int operator()(int row, int col) const
    {
        return data_[row * cols_ + col];
    }

    int rows() const { return rows_; }
    int cols() const { return cols_; }

private:
    std::vector<int> data_;
    int rows_{};
    int cols_{};
};

int main()
{
    Matrix m{2, 3, 0};
    m(0, 1) = 42;

    for (int row = 0; row < m.rows(); ++row)
    {
        for (int col = 0; col < m.cols(); ++col)
        {
            std::cout << m(row, col) << ' ';
        }
        std::cout << '\n';
    }
    return 0;
}
```

`m(row, col)` reads like a function call but invokes `operator()`.

## Try it now

### Exercise 1: Two indices

Prompt: Can you write `matrix[i][j]` with a single `operator[]` taking two `int`s?

:::details Answer

**No.** `operator[]` takes **one** argument. Use **`operator()(row, col)`** or nest types (e.g. row proxy with its own `operator[]`).

:::

### Exercise 2: Return type

Prompt: Why does non-const `operator[]` return `int&` instead of `int`?

:::details Answer

So **`obj[i] = 5`** modifies the stored element. Returning `int` would modify a copy.

:::
