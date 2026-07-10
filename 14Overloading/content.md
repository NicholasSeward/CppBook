we can not only overload function but we can overload operators

to do this we have special function

operator+ for example

[example]

resolving works just like for function.  it can be a good match or ambigious.  

almost all operators can be overlaoded except ?:, ::  selector .  list all
you can't make up new operators...laim

you can't overload unless something is userdefined...you can't change how ints add

precedence and associativity stay the same

preference: use overloading if it is clear like operator+ for adding fractions but don't use it if it isn't like using customstring-2 to remove 2 letters.  removeEnd(s,2) would be clearere.

A lot of the time when you have a class you want to put the overloads inside or with it.  there are a few ways to do that

one is with a friend function

explain what a friend function is

[example]

the other is just a normal funtion

[example]

the third is th member funciton way

[example]

prefernce: member function don't always make sense but use this approach whenever it makes sense.

take about member has an understood this for the left of the operand and only works if the thing on the left of operand is the custom class you are currently in.  also you don't need permission (friend status) to see private variables


between normal and friend functions...prefer a normal one if you can make that work

one good use to to make printing work seamlessly.  just overload operator<<

[example of point with operator<< overload]

explain the parts also explain why this can never me a member function

You can also overload operator>> great for reading from a file... if your print and reads mirror each other

[example reading an verifying starts with Point( and throw an error and behave just as if you were trying to read an int but "Asdf" was typed]

explain how it works and how the failure "works"

when to use normal, friend, or member

table
member: = [] () -> unary or binary with left
friend: if need access to private
normal: if don't control class or the left operand isn't a class we control or everything is public that we need

[make mermaid flowdiagram.  does member work  use member, if you need private access use friend else normal]


you can over load unary

talk about what they are

typically member

[example]

you can overload relational operators and even make sorts work

[example that allows a sort to work...also overload operator<< so you can see the sorted results]

if you just implement < and ==  you can build the rest

[example]

you can overload [] but there is no ability to do row column lookups

[example]

however if you overload () can you have any number of args so this is perfect for matrix type work

[example]

you don't even have to put integers in []

[example]

many of these things return references so you can modify the actual item

you can even overload typecasts

[example]




