if we have a obj, pointer, and reference to a derived class
all coll the derived function.  magic

if you use the base as type...stuff gets strange

derived in base ref or base pointer calls base function

talk about problem with cats and dogs.  it would be nice to have an animal list and have each act like what they are

would love to be generic

we need virtual functions
explain what they are

virtual only works with refs and points.  we will talk about object slicing

the idea that different objects can act differently is poly morphism  fancy word for simple concept.  cat->speak or dog->speak use thier functions

just virtual is enough but often on a terminal class like dog you would put override.  override will make sure it is in fact overriding a virtual function in the base class.  

preference: virtual on base, override on derived

if you don't want anything to override in the future you can put final

you will need a virtual desctructor if you do resource management.  just like the constructor build up layer by layer.  you need the destructors to careful tear it down.
preference: the rule of zero using stuff like smart pointers save you from the need.

there is a thing called the virtual table or vtable.  explain what it is and how it works

sometimes you don't know what a virtual function will do.  talk about abstract functions with no body

a class has to define it or als make it abstract

there is a concept of an interface where everything is abstract

talk about object slicing 

tip: just use points if you are storing a different things together.  like cats and dogs in a vector

it gets worse with frankenobjects.  you can have a base reference to a derived class and commit all sorts of sins.  the base ref will only let the base member variable through.

sometimes you have an base pointer but you want to call a function that only the derived class has. you can dynamic cast

prefer points for polymorphism and adjacent work.

you can also make operators like <<  work but not directly.  have it call a polymorphic function like itdentify to get a string to display.

explain why you can't make << directly virtual

