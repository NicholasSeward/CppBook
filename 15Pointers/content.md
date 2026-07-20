pointer are great but a lot of ways to forget to delete them and get memory leak and dangling pointers. if only there was a better way

smart pointers can do that

[example with a class Auto ptr with template typename T that shows how to wrap a pointer in a class prints on construction and destructions]

but we don't have to make it.  the stl already has it

a smart pointer is a class designed to manage dynamicall allocated memory

that and in our simple example we didn't think of all the isues such no guarenteed ownership ...we can still get dangling pointers and double frees.  we could solve this with more tooling but we will just use the already made ones.

one mechanism that makes this all work is the move semantic of transfering ownership.

[example of Auto ptr with move semantic has all sorts of printed telling what is done]

there use to be an std::auto_ptr but it wasn't perfect and it was deprecated in favor of our modern move aware smart pointers   unique weak and shared

talk about lvalues, rvalues, lvalue references, and rvalue references.  tie into how that helps us. take about when a rvalue ref is useful

[example of useful rvalue reference]

if we are building our own auto ptr we need move constuctors and move assignment
[example]


for the most part we don't need to do move constuctors and move assignments.   we will use the prebuilt machinery and take advantage of the rule of zero

talk about the rule of 3 and rule of 5

talk about std::move... what it does and how it is helpful

[example]

talk about unique ptr.  how it is usueful and how it works.

[example]

preference: unique ptrs are almost always the smart pointer/pointer you want

you can derefence use -> like normal.  you can even get a raw pointer to pass to something that isn't smart award.

[example]

make sure to talk about make unique and how it works

[example]

you can return rvalue unique ptr from functions
you can also pass a unique ptr but you have to use std::move to convert lvalues to rvalues essentially
it is all about passing ownership and only one thing owns it

[example]

however you typically you will probably archetict a system that unique pointers can stay put and if something else need access...you can pass a raw pointer.

two ways you can misuse unique
while it allows it wrapping a raw pointer that already exists can lead to isses...use make_unique
those issues are it would let you make two unique ptr for same memory chunk and you could potentially delete the memory out from under the smart pointer.

shared ptr is similiar but it counts how many scopes own it and won't be freed until none.  

note: you typically just want unique ptr...remember you can pass over a raw pointer to anyone that wants it or even a reference to a unique pointer.

[example]

make_shared

with shared or unique you can make a circular dependency.  in that case they will reinforce each other and provent automatic memory management

[example]

the solution is to no do that.  there is a 3rd type of smart pointer called a weak ptr that will allow for this.  weak pointers don't get counted but they are better than a raw pointer because you can see if the underlying sharedpointer is still valid.  

[example with doubly ended linked list]

it is not uncommon to just use unique ptr and raw pointers for all non ownership pointing needed.  for a linked list...you own the next but you just need to know about the previous one.

[example with unique and raw pointer]

weakptr is only usuable with shared.  there is no version that is usuable with uniqueptr.  

weakptr allows dangling pointers to be avoid

[example with lock]




