# Interface and Implementation

The **public** members of a class are its **interface**: what callers may depend on. **Implementation** is how you honor that contract inside member functions and private helpers.

Good interfaces stay stable. Implementations can change.

## Same interface, different internals

Both stacks expose `push`, `pop`, and `top`. One uses a `vector`, one uses a linked list. Callers who only use the public methods should not need to know which.

```cpp
#include <iostream>
#include <vector>

class IntStackVector
{
private:
    std::vector<int> data{};

public:
    void push(int value)
    {
        data.push_back(value);
    }

    void pop()
    {
        if (!data.empty())
        {
            data.pop_back();
        }
    }

    int top() const
    {
        return data.back();
    }

    bool empty() const
    {
        return data.empty();
    }
};

int main()
{
    IntStackVector s{};
    s.push(10);
    s.push(20);
    std::cout << s.top() << '\n';
    s.pop();
    std::cout << s.top() << '\n';
    return 0;
}
```

A linked-list version could swap `std::vector` for nodes and pointers but keep **`push` / `pop` / `top` / `empty`** with the same meanings. Tests written against the interface still pass.

That separation is the practical payoff of encapsulation: **define the lines of interaction**, hide the rest.

## Public interface vs private workers

| Public | Private |
|--------|---------|
| What users call | Data members |
| Constructors | Helper functions |
| Methods that define behavior | Details callers should not touch |

Users should not need to know whether your rectangle stores cached area or recomputes it on every `area()` call, as long as results stay correct.

## When internals still matter

Sometimes efficiency depends on representation:

- `std::vector` adds fast at the end, slow at the front
- `std::deque` adds fast at both ends
- Choosing the wrong container shows up in benchmarks, not in small homework sizes

> NOTE: You do not need to master every abstraction layer before writing code. Build something that works, measure if it matters, then research and improve. Stay curious; treat coding as a craft that improves with practice, not a checklist you finish once.

## Encapsulation vocabulary

- **Encapsulate** literally means "put in a capsule."
- In CS it almost always means **data hiding**: private state, public operations.

Smaller, well-behaved interfaces mean **less to test** and fewer ways for callers to break your types accidentally.

## Try it now

### Exercise 1: Interface sketch

Prompt: List three **public** function names you would put on a `Timer` class (start, stop, elapsed seconds). Do not implement them. Focus on names a caller would understand without knowing internals.

Example answers: `start()`, `stop()`, `elapsedSeconds()`
