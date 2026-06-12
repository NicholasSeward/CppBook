templates

it can be annoying to make a bunch of function overloads for different types

[example of a few max functions for different types]

if only there is a better way

if only we can treat a type like a variable itself

we can

[example with max template simple]

explain syntax

explain how the compiler will see what version will be used and make version at compile time.

T is the normal placeholder type.  if you need more use T,U,V in that order

[example with a TU]


you can call the function explicitely with <>

[example of max<int>]

note: this makes template a bit better than overloaded functions because you can specify the version you want

you can also rely on template argument deduction similiar to how function overloading can pick the right match

[example with no <> but it still works]

You can overload and use templates but this can get confusing and wouldn't suggest it unless there isn't a better option

[example with a template and a max(int,int) override...in main show how to call max<int> vs max(int,int)]

you can give certain versions special versions

[example with template and then one that does something special for func<int>]

you can mix template types and regular types

[example]

you can have defaults on nontemplate types

[example]

this concept of template is called generics or generic programming.  explain

preference: use them when it makes sense but keep them simple and easy to think about

you can have more than one template type

[example with max(T,T)]

talk about you can still have ambiguous matches

you can fix with TU

[example with max(T,U)]

but you have to call the return type.  you can get fancier with newer versions of c++ but in general this is probably more complex than makes sense for most programs.

c++20 allows auto
[nonrunnable snippet auto max(auto,auto)]

you can also overload with different number of type parameters

[example ]

preference: keep template simple with just typename T

you can also have nontype tempate parameters like int

[example int N]

preference: since you get a different function for every different int this rarely makes sense.  this is used in std::array but we prefer vector se we never use a function with this in regular practice.

note: nontype parameters can be usueful for performance and to push more work to compile time.  but unlikely to be useful in general


since template are figured out at compile time you can just use our normal forward declaration trick.  We have to break convention and fully define the template functions in header files 

[example where it won't work with forward declartion]

[example with header file that has the full template]

preference: if you need templates in multiple files...define them in the .h header file instead of the .cpp code file.


