# Why Sort and Binary Search

Sorting is one of the classic tasks in computer science. A **sorting algorithm** rearranges items into order. Race results, grade lists, and file names all benefit from order.

Sorting also unlocks other algorithms. Once data is sorted, you can **binary search**: check the middle item, decide whether your target is before or after it, and throw away half the remaining data each step.

## Halving a million items

With about 1,048,576 (2^20) items in sorted order, binary search might look at roughly this many items left after each step:

```
1048576 → 524288 → 262144 → 131072 → 65536 → 32768 → 16384 → 8192
→ 4096 → 2048 → 1024 → 512 → 256 → 128 → 64 → 32 → 16 → 8 → 4 → 2 → 1
```

That is about **20 comparisons** to find one target among a million items. Linear search might need a million.

Binary search needs sorted data first. That is one reason sorting matters so much.

## What you will learn in this module

1. Build a simple sort by hand so the steps make sense.
2. Describe cost with **Big O notation**.
3. Use the **STL algorithms** library (`std::sort`, `std::find`, and more).
4. Work with **iterators**, the handles STL algorithms use to reach your data.
5. **Time** code to compare approaches.

You already know `std::vector` and loops from earlier chapters. This chapter connects those tools to named algorithms.

## Try it now

1. Name one real program feature that needs sorted data (not just search).
