you can make your own types

explain using

[example of alias for int]

prefence: just use the fundamentials so you don't obscure meaning.

this is great mean dealing with a type with a long name like a 2d vector

[example of Matrix alias for vector vector int]

besides aliases we can make our own types.  enumerations and struct/classes.  we will save classes for their own chapter

struct can do lots but for how purposes you can basically group differnt things into one compound type

[example of fraction]

It is convento to name custom types with TitleCase t.  while this is different from the fundamential types this is standard across many programming languages and also for classes when we get tehre


enum can help you give meaning but only store simple ints

here is an example where the programmer has to remember what 0 1 2 mean for
[example]

it is better if we at least have some variables
[example]

however it is even better if you use an enum
[example]

this is a plan enum and should only be used in a namespace or class because it polutes the namespace.  it basically makes new int variables
[example]

While plain enums are great we have class enums to fix usage when they can't easily or doesn't make sense to put them in a namespace or class.
[example]

it is more to write but less chance for getting a name collision

old style is with enum element naming is all SCREAMING_SNAKE_CASE which is pretty common across most languages but C++ use screaming snake case for preprosser macros so we will use TitleCase
[example]

Enums are great to use with ifs and even switch statements.
[example for plain enum]
[example for class enum]

enums are good for functions that will return a status from a menu of options.
[example]

in programming there is a concept of magic numbers.  magic numbers sound good but they are actually bad.  they are unexplained (magic) values (not just number).  that is hard on the future programmer to know what they are and how to interface with them.  enums can help (at least use variables)

[bad example with magic number]
[good example using an class enum]


prefence: use class enum unless it is in namespace
[example of plain enum in a simple class]

enums typically have int values behind the scene
[example with some casting to print]

If you want you can give specific values that are meaningful and useful
[example with colors and hexcode]

the first value defaults to zero.  unspecified will be one more than last
[example with sparse assignment]

if you print a plain enum.. no issues converting to int
[example of it in print]

class enums require a cast.
[example]

some people want to get name in string form.  this isn't built in but you can do a function like this.
[example with ifs and func]

you can't also use cin directly but you can have an intermediate
[example with plain enum]
[example with class enum]

preference: use class enums unless you can stick it in a namespace/class.

You also can't take a string and go directly to the enum value but you can make a function.

[example with func and ifs]


structs

often you have variables that need to be grouped.  we can use structs or classes.  for now we will just use structs.  (class are largely the same but have the ability to have private members...we will cover them in the future)

[simple example]

note: don't forget the ; after your definition. That doesn't follow what we do for functions or normal code blocks.

the things in the struct are call data members, member variables, instance variables...there are a lot of names.  sometimes just member

this is a map of how your struct type stores stuff.  it is generic.  later you will make specific items from this blueprint.

you intialize by just listing what goes in each member in order in the {}
[example]

you can give defaults
[example]

you can get member values with the . operator (member selction operator)
[example]


you can even change the stored value.  
[example]

you should make sure everything is initialized not doing so can lead to undefined behavior
[example with no defaults and blank initializtion...print a member]

That could have worked but never count on the values you will get from it

you can initialize later but don't forget
[example with blank initialize but then use cin to grab values]

you can't print an struct
[example of what happens]

You can provide a function that tells << what to do if the left is an outputstream cout and the right is your struct...we can talk more about operator overloading in the future
[example]

You can make a copy of a struct with simple copy initializtion...fancy way of saying =
[example]

structs can make functions cleaner
[example with function that requires multiple args]
[same example with a function that take a struct]

you can also pass by reference instead of copyign the struct
[example]

const reference if you don't need to change anything
[example]

preference: if struct is simple and you don't need to modify the original...pass by value.  if struct is big and you don't need to modify the orignial...const ref.  if struct is big or you need to modify...use reference

performance: reference are faster because you don't need to make a copy to a new chunk of member

you can also retur structs
[example with an add 2d vector]

since it know the type a function can just use {} to make it clean
[example]

You can have structs in structs
[example]

don't go crazy






