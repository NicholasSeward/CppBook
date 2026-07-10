# When to Overload

Overloading is a readability tool. Use it when the operator spelling matches the idea; skip it when a named function is clearer.

## Clear uses

| Expression | Feels natural because |
|------------|----------------------|
| `a + b` for fractions, vectors | Addition |
| `out << point` | Printing |
| `a < b` for sorting | Comparison |
| `matrix(row, col)` | Indexing with two coordinates |

## Unclear uses

```
// Hard to read: what does "string - 2" mean?
customString - 2;

// Clearer as a named function:
removeEnd(customString, 2);
```

> PREFERENCE: Overload **`operator+`** when you are really adding things. Do **not** overload operators to save typing when the meaning is obscure.

## Keep overloads near the type

Most operator overloads belong **with the class they operate on**: inside the class as members, or beside it as friends/free functions in the same header.

Readers should find `Point` and `operator<<` for `Point` in one place.

## Try it now

### Exercise 1: Name vs operator

Prompt: You want to remove the last two characters from a `MyString` class. `operator-` or `removeEnd`?

:::details Answer

**`removeEnd`** (or similar). Subtraction does not suggest “trim from the end.”

:::

### Exercise 2: Printing

Prompt: Why is `std::cout << p` a common overload for a `Point` class?

:::details Answer

**`<<`** already means “send to output stream” for built-in types. Extending it to `Point` matches how programmers read printing code.

:::
