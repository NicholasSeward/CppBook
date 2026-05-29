# Tutorials: Vectors, Loops, Random, Structs, and Enums

Work through each code block in order. Change only what each question asks for unless a question says to keep earlier edits.

> NOTE: In this course, prefer `.at()` over `[]` for vector access when you want bounds checking.

---

## Simple vector

### Starter code

```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> nums{1, 2, 3, 4};
    std::cout << "size=" << nums.size() << " cap=" << nums.capacity() << "\n";
    return 0;
}
```

### 1.

Add `nums.push_back(99);` then print `size` again. What is true about `size()`?

- A. It increases by 1
- B. It stays the same
- C. It becomes 99
- D. Compile error

### 2.

After `push_back(99)`, what is **always** true about `capacity()`?

- A. It increases by exactly 1
- B. It stays the same on every computer
- C. It is always `>= size()`
- D. It always equals `size()`

### 3.

Add and run: `std::cout << "at1=" << nums.at(1) << "\n";` What prints?

- A. `at1=1`
- B. `at1=2`
- C. `at1=3`
- D. Runtime error

### 4.

Add and run: `std::cout << "atNeg=" << nums.at(-1) << "\n";` What happens?

- A. It prints the last element
- B. It throws an out-of-range error at runtime (or terminates)
- C. Compile error
- D. It prints `-1`

### 5.

After `push_back(99)`, add and run: `std::cout << "front=" << nums.front() << " back=" << nums.back() << "\n";` What prints?

- A. `front=1 back=99`
- B. `front=4 back=1`
- C. `front=0 back=0`
- D. Runtime error

### 6.

Replace the initializer with `std::vector<int> nums(5, 20);` (no `push_back`). What are `nums.size()` and `nums.front()`?

- A. size `5`, front `20`
- B. size `6`, front `20`
- C. size `5`, front `5`
- D. size `20`, front `0`

---

## Simple for loop

### Starter code

```cpp
#include <iostream>

int main()
{
    for (int i{0}; i < 4; ++i)
    {
        std::cout << i << "\n";
    }

    return 0;
}
```

### 7.

Change `i < 4` to `i < 10`. How many times does it loop?

- A. `9`
- B. `10`
- C. `8`
- D. Runtime error

### 8.

Change `i < 10` to `i <= 10`. How many times does it loop?

- A. `9`
- B. `10`
- C. `11`
- D. Infinite loop

### 9.

Change the start from `int i{0}` to `int i{1}` (with condition `i <= 10`). How many times does it loop?

- A. `9`
- B. `10`
- C. `11`
- D. Compile error

### decrement in loop

Change `++i` to `--i`. What happens?

- A. `0` loops
- B. `3` loops
- C. Infinite loop
- D. Compile error

### 11.

Which loop header counts down from 10 to 1?

- A. `for (int i{10}; i >= 1; --i)`
- B. `for (int i{10}; i <= 1; --i)`
- C. `for (int i{1}; i <= 10; --i)`
- D. `for (int i{10}; i > 1; ++i)`

---

## Simple while input loop

### Starter code

```cpp
#include <iostream>

int main()
{
    int n{-1};
    while (true)
    {
        std::cout << "Enter a number (1-10): ";
        std::cin >> n;

        if (n >= 1 && n <= 10)
        {
            std::cout << "Good\n";
        }
        else
        {
            std::cout << "Bad\n";
        }
    }
}
```

### bad input forever

If you type `0` forever, what happens?

- A. It prints `Good` once then exits
- B. It prints `Bad` forever (infinite loop)
- C. It prints `Good` forever
- D. Compile error

### 13.

Where should you add `break;` so the program stops after a good input?

- A. Right after printing `Good` (inside the `if` block)
- B. Inside the `else` block after printing `Bad`
- C. Before reading input
- D. After the `while` loop

### loop condition instead of break

Instead of `break`, which loop condition stops when input becomes good (assuming `n` is declared before the loop)?

- A. `while (n < 1 || n > 10)`
- B. `while (n >= 1 && n <= 10)`
- C. `while (true && false)`
- D. This is impossible

---

## Random (Mersenne Twister)

### Starter code

```cpp
#include <iostream>
#include <random>

int main()
{
    std::mt19937 mt{std::random_device{}()};
    std::uniform_int_distribution<int> die6{1, 6};

    std::cout << "mt()=" << mt() << "\n";
    std::cout << "die6(mt)=" << die6(mt) << "\n";
    return 0;
}
```

### 15.

Temporarily change:

```cpp
std::mt19937 mt{std::random_device{}()};
```

to:

```cpp
std::mt19937 mt{0};
```

What is true about the output?

- A. The numbers printed are not random (not pseudorandom).
- B. The numbers are pseudorandom but always the same each run
- C. The numbers are always `0`
- D. Compile error

### 16.

What kind of value does `mt()` produce?

- A. Always `1`–`6`
- B. A large pseudorandom unsigned integer (engine output)
- C. A decimal between `0.0` and `1.0`
- D. Compile error

### 17.

What kind of value does `die6(mt)` produce?

- A. A large engine integer
- B. An integer from `1` to `6` (inclusive)
- C. A decimal from `-100.0` to `100.0`
- D. Always `0`

### 18.

Which distribution gives decimal values between `-100.0` and `100.0`?

- A. `std::uniform_int_distribution<int>{-100, 100}`
- B. `std::uniform_real_distribution<double>{-100.0, 100.0}`
- C. `std::normal_distribution<double>{-100.0, 100.0}`
- D. `std::bernoulli_distribution{0.5}`

---

## Simple struct

### Starter code

```cpp
#include <iostream>
#include <string>

struct Player
{
    std::string name;
    int health{};
    int score{};
};

int main()
{
    Player ada{"Ada", 100, 0};

    std::cout << ada.name << " hp=" << ada.health << " score=" << ada.score << "\n";
    return 0;
}
```

### starter output

What does the starter program print?

- A. `Ada hp=100 score=0`
- B. `Ada hp=0 score=100`
- C. Compile error (missing semicolon after the struct)
- D. Runtime error

### 20.

Change the last line to `std::cout << ada.health << "\n";` then add `ada.health = 50;` and print again. What is the second number printed?

- A. `100`
- B. `50`
- C. `0`
- D. Compile error

### 21.

Add a second player: `Player bob{"Bob", 80, 5};` Which line correctly prints Bob's score?

- A. `std::cout << Player.score << "\n";`
- B. `std::cout << bob.score << "\n";`
- C. `std::cout << score.bob << "\n";`
- D. `std::cout << bob->score << "\n";`

### 22.

A struct definition must end with what token (after the closing `}`)?

- A. A comma `,`
- B. Nothing extra
- C. A semicolon `;`
- D. The keyword `struct` again

---

## enum class

### Starter code

```cpp
#include <iostream>

enum class TrafficLight
{
    Red,
    Yellow,
    Green
};

int main()
{
    TrafficLight light{TrafficLight::Red};

    if (light == TrafficLight::Red)
    {
        std::cout << "Stop\n";
    }

    return 0;
}
```

### starter output

What does the starter program print?

- A. `Stop`
- B. `Go`
- C. `Red`
- D. Compile error

### 24.

Which assignment is valid for `TrafficLight light`?

- A. `light = Red;`
- B. `light = TrafficLight::Green;`
- C. `light = 2;` (without a cast)
- D. `light = "Green";`

### 25.

Change the `if` condition to compare against `Green` without the scope prefix. What happens?

- A. It still compiles and prints `Stop` or `Go`
- B. Compile error (`Green` is not found in scope)
- C. Runtime error
- D. It prints `Green` as text

### 26.

Why does `enum class` help compared to a plain `enum`?

- A. It makes the program run faster
- B. Names like `Red` stay inside the enum type and do not pollute the surrounding scope
- C. It removes the need for `if` statements
- D. It stores values as strings automatically
