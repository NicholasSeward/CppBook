# Debugging Process

**Debugging** is the work of taking code that misbehaves and making it behave correctly.

It is not guessing. It is a repeatable process: find the problem, understand it, fix it, and verify the fix.

## A basic approach

A simple loop that works for most bugs:

1. **Find the root cause.** Where does behavior first go wrong?
2. **Understand why it is wrong.** What did you assume that is not true?
3. **Correct the code.** Change the smallest thing that fixes the real issue.
4. **Retest.** Run the same case again, then run related cases.

Skipping step 2 leads to fixes that hide the symptom but leave the bug elsewhere.

## Incremental programming

One way to have fewer bugs at once is to write in **small, testable chunks**.

1. Add a few lines.
2. Compile and run.
3. Confirm behavior.
4. Add a little more.

This is incremental programming in function design.  The idea is the same: if something breaks, the last small change is the likely culprit.

Learning how big a "chunk" should be is a skill. Start smaller than you think you need.

> PREFERENCE: Commit or save a known-good version before a risky change. That gives you a place to roll back mentally even if you do not use version control yet.

## How to debug

### Code inspection

Sometimes you can find the bug by reading the code slowly, line by line, and asking what each line does.

This works well for small programs and for mistakes you have seen before (missing braces, wrong operator).

### Running and reproducing

If inspection does not find it, run the program and **reproduce** the bug on demand.

- What input triggers it?
- Does it happen every time or only sometimes?
- What is the smallest program that still shows the problem?

**Reproducibility** is central. Intermittent bugs are much harder to fix. If you cannot reproduce a failure, gather more data (prints, logs, fixed random seeds) until you can.

### Homing in

When you know good input works and bad input fails, narrow the gap.

- Add prints: "got here", "value is X".
- Use a debugger to pause between those points (see [Debugging Tools](03debugging%20tools.md)).
- Comment out half the code to see which half contains the bug (binary search through the program).

You are looking for the first moment reality diverges from your mental model.

```cpp
#include <iostream>

int computeTotal(int base, int bonus)
{
    std::cout << "computeTotal: base=" << base << " bonus=" << bonus << '\n';
    return base + bonus;
}

int main()
{
    int score{computeTotal(10, 5)};
    std::cout << "score=" << score << '\n';
    return 0;
}
```

Temporary prints like this are crude and effective. Remove them once you understand the bug.

## When you are stuck

- Explain the code out loud.
- Compare working code to broken code (diff tools help).
- Search through the error messages.
- Take a short break. Fatigue makes you miss obvious typos.

> NOTE: "Rubber duck debugging" is the practice of explaining your code or problem out loud, often to an inanimate object like a rubber duck. Many programmers find that describing the issue—whether to a duck, a pet, or a person with no programming experience—reveals mistakes or new ideas. The act of talking through the problem step by step is often enough to help you find the solution yourself.

> AI: Ask "What does this error mean?" or "What could cause this output?" instead of only "Fix my code." You learn more when you stay in the loop.
