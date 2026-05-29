# Testing and Debugging

A program that **runs** is not automatically **correct**. Running is the first bar. You still have to check behavior.

## Testing

**Testing** means running your program (or parts of it) and checking that results match what you expect.

Examples:

- Does `2 + 2` print `4`?
- Does your program handle empty input?
- Does it stop cleanly on bad input?

Start testing as soon as you have something runnable. Tie testing to the [programming process](04the%20programming%20process.md): build small, test, repeat.

> PREFERENCE: After each small change, run the program. If it fails, you know the last change is the likely cause.

## Debugging

**Debugging** is the work of finding and fixing errors. Errors come in several flavors (you will see more in later chapters):

- **Syntax / compile errors** before the program runs
- **Runtime errors** (crashes, exceptions)
- **Logic errors** (wrong answer, no crash)

Debugging tools include:

- reading compiler messages
- adding print statements
- using a debugger to pause and inspect variables

> PROTIP: Focus on the **first** error message from the compiler, later messages may just be consequences of that first mistake.

## If compilation fails

When your code doesn't compile:

1. Carefully read the error message, it often points to the exact line and explains the issue.
2. Fix one problem at a time.
3. Recompile after each fix.

Some error messages can be confusing. If needed, use AI or online resources to help interpret them.

> AI: This course emphasizes learning the core concepts. Use AI to help explain errors, provide small examples, or quiz your understanding. Instead of simply asking "fix it," try asking "What does this error mean?" or "Why is this line incorrect?" to build your skills.