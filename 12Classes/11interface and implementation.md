# Interface and Implementation

The **public** members of a class are its **interface**: what callers may depend on. **Implementation** is how you honor that contract inside member functions and private helpers.

Good interfaces stay stable. Implementations can change.

## Same interface, different internals

Two classes can expose the **same public methods** while storing data differently inside. Callers who only use `deposit`, `withdraw`, and `balanceAmount` should not need to know whether the balance is kept as **integer cents** or **floating-point dollars**.

**Implementation A: balance stored as cents (`int`)**

```cpp
#include <iostream>

class BankAccount
{
private:
    int balanceCents{};

public:
    BankAccount(double startBalance)
        : balanceCents{static_cast<int>(startBalance * 100)}
    {
    }

    void deposit(double amount)
    {
        balanceCents += static_cast<int>(amount * 100);
    }

    void withdraw(double amount)
    {
        balanceCents -= static_cast<int>(amount * 100);
    }

    double balanceAmount() const
    {
        return balanceCents / 100.0;
    }
};

int main()
{
    BankAccount acct{100.0};
    acct.deposit(25.50);
    acct.withdraw(10.25);
    std::cout << acct.balanceAmount() << '\n';
    return 0;
}
```

**Implementation B: balance stored as dollars (`double`)**

```cpp
#include <iostream>

class BankAccount
{
private:
    double balance{};

public:
    BankAccount(double startBalance)
        : balance{startBalance}
    {
    }

    void deposit(double amount)
    {
        balance += amount;
    }

    void withdraw(double amount)
    {
        balance -= amount;
    }

    double balanceAmount() const
    {
        return balance;
    }
};

int main()
{
    BankAccount acct{100.0};
    acct.deposit(25.50);
    acct.withdraw(10.25);
    std::cout << acct.balanceAmount() << '\n';
    return 0;
}
```

Same calls in `main`, same output for this example (`115.25`). Different private fields, different arithmetic inside the methods. You could swap implementations behind the interface without changing caller code.

The cents version avoids some floating-point rounding drift; the `double` version is simpler to write. Both are valid tradeoffs as long as the **public contract** stays clear.

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
