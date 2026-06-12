# Nontype Template Parameters

So far, template parameters have been **types** (`typename T`). C++ also allows **nontype** template parameters: values known at compile time, often `int` or `std::size_t`.

## Example with `int N`

```cpp
#include <iostream>

template <typename T, int N>
T sumFixed(const T (&values)[N])
{
    T total{};
    for (int i{0}; i < N; ++i)
    {
        total += values[i];
    }
    return total;
}

int main()
{
    int nums[]{10, 20, 30};
    std::cout << sumFixed(nums) << '\n';
    return 0;
}
```

`N` is deduced from the array size. The compiler generates a different `sumFixed` for each different `N` you use.

## Why this is rare in everyday code

Every distinct `N` can produce a **different function** in the compiled program. That can grow code size if overused.

You see nontype parameters in library code such as `std::array<T, N>`, which stores exactly `N` elements on the stack with no dynamic allocation.

> PREFERENCE: This course prefers `std::vector` for variable-size sequences. You are unlikely to write your own nontype template functions in regular practice. Know the idea exists so library templates make sense when you read them.

## Compile-time work

Nontype parameters can push work to compile time (fixed bounds, fixed-size tables). That can help performance in specialized code. For typical homework and small projects, a `std::vector` and a normal loop are simpler.

> NOTE: Nontype template parameters are useful in advanced and library code. They are not a pattern you need to reach for in every project.

## Try it now

1. In one sentence, explain the difference between `typename T` and `int N` in a template parameter list.
2. Look up `std::array` in a reference. How many template parameters does it take?
