# Building a Sort

Before calling library sort functions, try sorting a small list yourself. You might invent a reasonable algorithm without memorizing anything.

## A messy list

Work with this vector:

```
5  1  4  3  8  2  6  7
```

It is not in order. How would **you** start fixing it?

Most people look at the **first two** numbers: `5` and `1`. They are out of order (bigger before smaller). The smallest fix is a **swap**:

```
1  5  4  3  8  2  6  7
```

## What next?

Move one slot to the right. Compare the **second and third** numbers: `5` and `4`. Out of order again. Swap:

```
1  4  5  3  8  2  6  7
```

Keep the same rule: walk left to right, compare each **pair of neighbors**, swap when the left one is bigger.

- `5` and `3` → swap → `1  4  3  5  8  2  6  7`
- `5` and `8` → already fine, no swap
- `8` and `2` → swap → `1  4  3  5  2  6  7  8`
- keep going until there is no neighbor pair left to check

After one full trip across the list:

```
1  4  3  5  2  6  7  8
```

Are we done? **No.** But something useful happened: the **largest** value (`8`) ended up at the **end**. It got pushed there step by step as larger numbers swapped past smaller ones.

## One pass is not enough

Run the same neighbor walk again on the new list:

```
1  3  4  2  5  6  7  8
```

Better. Again:

```
1  3  2  4  5  6  7  8
```

Again:

```
1  2  3  4  5  6  7  8
```

Sorted.

Each full left-to-right walk is one **pass**. One pass guarantees at least one more value settles into its final spot at the back (the current largest among what remains).

## How do we know when to stop?

Run one more pass on the sorted list. No swaps would happen. That is a clean stopping rule: **if a pass makes zero swaps, the list is in order.**

In the worst case with `n` items, each pass places at least one more item at the end, so you need at most **`n - 1` passes**.

## A name for what you built

Computer scientists call this **bubble sort**. Large values bubble toward the end of the list one pass at a time. It is not the fastest sort on big data, but you could have discovered the idea yourself: compare neighbors, swap when wrong, repeat.

> NOTE: [Bubble sort](https://en.wikipedia.org/wiki/Bubble_sort) has many optimizations. Even tuned versions are rarely used on huge lists today. The pass-and-swap pattern is still a useful mental model.

## Code one pass

Turn the neighbor walk into a loop:

```cpp
#include <iostream>
#include <vector>

void printVector(const std::vector<int>& values)
{
    for (int n : values)
    {
        std::cout << n << ' ';
    }
    std::cout << '\n';
}

int main()
{
    std::vector<int> values{5, 1, 4, 3, 8, 2, 6, 7};

    std::cout << "Before: ";
    printVector(values);

    for (int i{0}; i < values.size() - 1; ++i)
    {
        if (values.at(i) > values.at(i + 1))
        {
            std::swap(values.at(i), values.at(i + 1));
        }
    }

    std::cout << "After one pass: ";
    printVector(values);

    return 0;
}
```

`i` walks neighbor pairs: `(0,1)`, `(1,2)`, `(2,3)`, and so on. Swap when the left neighbor is larger.

## Code multiple passes

Pull one pass into a function, then call it in a loop and print after each pass:

```cpp
#include <iostream>
#include <vector>

void printVector(const std::vector<int>& values)
{
    for (int n : values)
    {
        std::cout << n << ' ';
    }
    std::cout << '\n';
}

void onePass(std::vector<int>& values)
{
    for (int i{0}; i < values.size() - 1; ++i)
    {
        if (values.at(i) > values.at(i + 1))
        {
            std::swap(values.at(i), values.at(i + 1));
        }
    }
}

int main()
{
    std::vector<int> values{5, 1, 4, 3, 8, 2, 6, 7};

    for (int pass{0}; pass < values.size() - 1; ++pass)
    {
        onePass(values);
        std::cout << "Pass " << pass + 1 << ": ";
        printVector(values);
    }

    return 0;
}
```

You should see the same sequence you worked out by hand.

## Full bubble sort with early exit

Wrap passes in one function. Track whether any swap happened. If a pass swaps nothing, stop early:

```cpp
#include <iostream>
#include <vector>

void bubbleSort(std::vector<int>& values)
{
    for (int pass{0}; pass < values.size() - 1; ++pass)
    {
        bool swapped{false};
        for (int i{0}; i < values.size() - 1 - pass; ++i)
        {
            if (values.at(i) > values.at(i + 1))
            {
                std::swap(values.at(i), values.at(i + 1));
                swapped = true;
            }
        }
        if (!swapped)
        {
            break;
        }
    }
}

int main()
{
    std::vector<int> values{5, 1, 4, 3, 8, 2, 6, 7};

    bubbleSort(values);

    for (int n : values)
    {
        std::cout << n << ' ';
    }
    std::cout << '\n';

    return 0;
}
```

The inner loop shortens each pass because the tail is already sorted. That matches the hand process: once `8` is locked at the end, you stop comparing past it.

## Try it now

### Exercise 1: Count swaps in one pass

Prompt: You discovered the neighbor-swap pass. Add a counter that increments on each swap. Run one pass on `{5, 1, 4, 3, 8, 2, 6, 7}` and print the count.

```cpp
#include <iostream>
#include <vector>

int onePass(std::vector<int>& values)
{
    int swaps{0};
    // TODO: neighbor compare loop, increment swaps on each swap
    return swaps;
}

int main()
{
    std::vector<int> values{5, 1, 4, 3, 8, 2, 6, 7};
    std::cout << "Swaps in one pass: " << onePass(values) << '\n';
    return 0;
}
```

### Exercise 2: Check on paper

Prompt: Without looking at the code, write the next two passes (after pass 1) for `{3, 1, 4, 2}` using the neighbor-swap rule. Then run `onePass` twice in code and check your work.
