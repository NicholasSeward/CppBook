# Why Vectors

So far, most of our programs have used a small number of named variables.

That works when the program only needs a few values. It stops working well when the program needs many values of the same type.

## A small example

Imagine you want to store scores for five students.

```cpp
#include <iostream>

int main()
{
    int score1{92};
    int score2{88};
    int score3{95};
    int score4{81};
    int score5{90};

    std::cout << score1 << " " << score2 << " " << score3 << " " << score4 << " " << score5 << "\n";
    return 0;
}
```

This works, but it does not scale well.

## The repetition problem

What if you want the average of thirty scores? One hundred? One million?

At some point, writing a separate variable for each value becomes painful to maintain.

You could also make a `struct` that holds several student scores as separate `int` members, like this:

```cpp
#include <iostream>
#include <string>

struct ClassScores
{
    std::string class_name{};
    int score1{};
    int score2{};
    int score3{};
    int score4{};
    int score5{};
};

int main()
{
    ClassScores math_scores{"Math", 92, 88, 95, 81, 90};

    std::cout << math_scores.class_name << " scores:\n";
    std::cout << "Student 1: " << math_scores.score1 << "\n";
    std::cout << "Student 2: " << math_scores.score2 << "\n";
    std::cout << "Student 3: " << math_scores.score3 << "\n";
    std::cout << "Student 4: " << math_scores.score4 << "\n";
    std::cout << "Student 5: " << math_scores.score5 << "\n";

    return 0;
}
```

But this still means writing out each score by name, which gets tedious when there are many scores.

A struct helps group related values, but printing or processing many separate values is still awkward.

## Containers

C++ gives us **containers** for this job.

A container holds many values of the same type. In most cases, the container is **homogeneous**: every element has the same type.

Containers also commonly give you common operations:

- create a container
- get an element
- add or remove an element
- check how many elements it holds

Different container types behave differently. This chapter focuses on `std::vector`.