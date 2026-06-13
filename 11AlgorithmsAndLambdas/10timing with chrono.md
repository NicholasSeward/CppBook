# Timing with chrono

When two approaches both work, which is faster? **Benchmark**: run each version and measure elapsed time.

C++ provides `<chrono>` for clocks and time differences. Treat timings as hints, not guarantees.

## now, duration, and count

Three ideas show up in almost every timing snippet:

| Idea | Role | Typical code |
|------|------|--------------|
| **`now()`** | read the clock right now | `auto start = std::chrono::high_resolution_clock::now();` |
| **duration** | time passed between two reads | `auto elapsed = end - start;` |
| **`count()`** | turn that duration into one integer | `std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count()` |

`now()` does not give you a calendar date. It gives a **time point**: a single numeric position on a clock's timeline.

Subtract two time points and you get a **duration** (how long something took). `duration_cast` picks the unit (milliseconds, microseconds, etc.). `count()` pulls out a plain `long` you can print or compare.

```cpp
#include <chrono>
#include <iostream>

long nowMs()
{
    auto now{std::chrono::high_resolution_clock::now()};
    return std::chrono::duration_cast<std::chrono::milliseconds>(
               now.time_since_epoch())
        .count();
}

int main()
{
    long t0{nowMs()};
    long t1{nowMs()};

    std::cout << "Elapsed ms: " << (t1 - t0) << '\n';
    return 0;
}
```

For benchmarking, snapshot **before** and **after** the work, subtract, then `count()`:

```cpp
auto start{std::chrono::high_resolution_clock::now()};
// work here
auto end{std::chrono::high_resolution_clock::now()};

auto ms{std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()};
```

> NOTE: **Epoch time** means storing time as **one number**: how many ticks since a fixed starting instant (often January 1, 1970 UTC on Unix systems). The computer does not store month, day, year, or time zone inside that integer. Display layers convert the number for humans. When two systems use the same epoch and clock definition, you can compare those numbers directly. Time zone and calendar formatting are separate concerns layered on top.

## Time a sort

```cpp
#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
#include <vector>

int main()
{
    const int N{1'000'000};
    std::vector<int> values(N);

    std::mt19937 rng{42};
    std::uniform_int_distribution<int> dist{1, N};
    for (int i{0}; i < N; ++i)
    {
        values.at(i) = dist(rng);
    }

    auto start{std::chrono::high_resolution_clock::now()};
    std::sort(values.begin(), values.end());
    auto end{std::chrono::high_resolution_clock::now()};

    auto ms{std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()};

    std::cout << "Sort " << N << " ints: " << ms << " ms\n";

    return 0;
}
```

## Watch scaling

Double input size until runtime crosses a target (for example 5 seconds). You should see sort grow faster than linear for large random data (roughly O(n log n) behavior).

```cpp
#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
#include <vector>

int main()
{
    int n{1};
    while (n <= 1'000'000)
    {
        std::vector<int> values(n);
        std::mt19937 rng{123};
        std::uniform_int_distribution<int> dist{1, n};
        for (int i{0}; i < n; ++i)
        {
            values.at(i) = dist(rng);
        }

        auto start{std::chrono::high_resolution_clock::now()};
        std::sort(values.begin(), values.end());
        auto end{std::chrono::high_resolution_clock::now()};

        auto ms{std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()};
        std::cout << "n=" << n << " ms=" << ms << '\n';

        if (ms > 5000)
        {
            break;
        }

        n *= 2;
    }

    return 0;
}
```

Your numbers depend on CPU load, compiler flags, and hardware.

## Timing caveats

Measuring changes what you measure. Lab timings are not production timings.

| Factor | Effect |
|--------|--------|
| Debug vs release build | debug can be over 10x slower |
| `std::cout` inside hot loops | I/O dominates |
| Extra function calls | overhead adds up |
| Cache locality | sequential access is faster than random jumps |
| Other programs running | noise in results |
| Timing human input | includes think time, not just code |

> PROTIP: Turn off heavy logging inside timed sections. Build with optimizations when comparing real algorithms. Run several trials and look for a trend, not one magic number.

> NOTE: [Lambda Basics](12lambda%20basics.md) shows shorter inline callbacks for comparators and `for_each`. Named functions and `std::function` work fine in C++17 too.

## Try it now

### Exercise 1: Time bubble vs sort

Prompt: Fill a vector of size 5000 with random ints. Time your bubble sort (or one pass only) vs `std::sort`. Print both millisecond counts.

```cpp
// @file: main.cpp
#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
#include <vector>

void bubbleSort(std::vector<int>& values)
{
    // TODO: or paste from the Building a Sort section
}

int main()
{
    const int N{5000};
    // TODO: build vector, time bubbleSort on a copy, time std::sort on a copy
    return 0;
}
```
