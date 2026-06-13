# Big O Notation

Bubble sort is intuitive, but how expensive is it on a big list? Computer scientists describe growth with **Big O notation**: a simple function that captures how time or memory scales as input size `n` grows.

## Counting comparisons in bubble sort

For `n = 8`, unoptimized bubble sort might compare neighbors this many times per pass:

| Pass | Comparisons |
|------|-------------|
| 1st | 7 |
| 2nd | 6 |
| 3rd | 5 |
| 4th | 4 |
| 5th | 3 |
| 6th | 2 |
| 7th | 1 |

Total: `7 + 6 + 5 + 4 + 3 + 2 + 1 = 28`.

In general that sum is `(n - 1) + (n - 2) + ... + 1`, which equals `n * (n - 1) / 2`.

That expands to `n² / 2 - n / 2`.

For large `n`, the **`n²` term dominates**. Constants like `½` and lower-order terms like `n` are dropped in Big O. Bubble sort is **O(n²)**.

## What O(n²) means in practice

Big O ignores constant factors on purpose. It answers: **if I double the input, what happens to cost?**

If sorting 1 million items takes about 1 second with an O(n²) algorithm:

- 2 million items → about **4 seconds**
- 10 million items → about **100 seconds**

That scaling is why bubble sort is not used on large production datasets.

## Faster sorts exist

**Quicksort** and **mergesort** are typically **O(n log n)**. Logarithms grow very slowly. Sorting 10 million items with O(n log n) is vastly more practical than O(n²).

You do not implement those from scratch every time. Languages ship library sorts tuned for typical use.

> NOTE: [Big O notation](https://en.wikipedia.org/wiki/Big_O_notation) describes upper-bound growth, not exact runtime on your computer. It is a scaling shorthand, not a stopwatch reading.

## Common complexities (intuition)

| Big O | Name | Example |
|-------|------|---------|
| O(1) | constant | `vector.at(i)` |
| O(log n) | logarithmic | binary search on sorted data |
| O(n) | linear | one pass through a vector |
| O(n log n) | linearithmic | good general-purpose sort |
| O(n²) | quadratic | bubble sort (worst case) |

## Try it now

1. With O(n²) sorting, if `n = 1000` takes 1 ms, roughly how long for `n = 1000000`? Hint: minutes
2. Why do we drop the `½` in `n(n-1)/2` when we write O(n²)?
