up till now we have been using procedural programming.  exaplian

so far we have variables (state) and function (behaviors) seperate.  if only we could bring it together

nonrunnable snippet   fillTank(car)  

OOP is the marriage of data and behavior.

note: all the stuff we are going to do with OOP can be accomplished without.  it is a boon to dev and makes code more module.  This often comes with an abstraction tax and OOP code often runs slower than a fully optimized program.  but that is very okay.  we can go from 100 ns to 120 ns and not feel it if that means it is easier to put together big programs.

nonrunnable snippet car.fillTank()

note: this new syntax of noun.verb(info) is pervasive in OOP but you can do OOP without it.  It really helps with the mental model of letting you know that the car carries all of its state and you can act on it.

[example procedural with animals and counting legs]

[same example but object oriented (use struct to keep it as simple as possible)]

compare and contrast the examples and point out what is gained

The "software crisis" of the 1960s–1980s was driven by the observation that software effort appeared to grow much faster than system size. As programs became larger, developers spent an increasing amount of time coordinating with one another, understanding existing code, and tracking bugs that emerged from interactions between previously independent components. Rather than growing linearly with lines of code, the cost of development and maintenance often grew superlinearly or worse, leading many researchers to question whether increasingly complex software systems could be built economically.  Some people thought that the hardware was so awesome if only we could write software to fully utilize it.  (This is hardware that is a billionith of todays systems on many metrics.)

Object-oriented programming (OOP) was promoted as a way to change this growth curve. OOP introduces an upfront investment in designing classes, abstractions, and interfaces, making small projects slightly more expensive. However, by reducing coupling, encouraging reuse, and localizing changes behind well-defined boundaries, it reduces the number of interactions that developers must reason about as a system grows. The result is a higher initial cost but a slower increase in development effort, producing a crossover point where OOP becomes the more efficient approach. For many students, that crossover occurs around a second college programming course, where projects become large enough that organizing code into cooperating objects saves more effort than it costs.

[mermaid xychart showing the rough trend]


talk about what it means to be an object

properties and behavior combined in this context

structs can do this

we usually just use them to represent state properties

[example]

but we can add in behavior  which is both easy and immediately helpful

[example with struct with functions inside that gets used]

you may wonder why we don't use functions with these already.  that is because we have another thing called a class meant for that.  The "problem" is that everything in a struct is defaulted to public which means anyone can reach in and change whatever.  we don't know yet but that makes software development much much harder.  We want to be able to maintain invariants and encapsulation.  invariants are things that should always be true but if you just let any modify the data directly...you/they might break things.  if you put the data in a private area (encapsulation) and have to call functions to do anything with the data...you can better preserve these invariants.  You can also reduce the number of ways that the data/class can be interacted with which will drastically reduced testing requirements.  Only provide features that are needed.

[example of a rectangle struct where someone changes the width but the area doesn't agree anymore]

[example of a class with it done properly and no error]

we will talk about the specifics but the class example doesn't let the data members be directly modified and instead you have to call the functions.  we will talke more about the public/private later.

class is just a struct but everything defaults to be private

because of this you can't use {} to direct fill memory and you can't access the membery variables

[example with a class with member variables only and doesn't work to so that everything is private]

you can make everything public but then you should have just used a struct

[example with public for the member variables in the class]

we will need to learn a new thing constructors that fill in the private data members and add public member functions that we can use to read or write the private things.

most of the c++ stl are classes.  C++ originally was named c with classes.  

since you learned a little about testing the class is the units we usually spend our time testing.

classes are blueprints for how to put an object or instance of the class together.  class is from classification or class of thing.  we have a class of objects.  the class is the type.  an object is an instance of that type.

classes need 3 main things.  data member, contructor, member function

data member: what does an object need to know to differentiate it from all the other objects of that class. example: a rectangle object might need to know its width and height to differentiate it from all other rectangles.  note: you don't need to store that the angle is 90 because all rectangles know that so it is backed into the concept and implicite with the name... when we program we will work under that assumption.
constructor: how do we fill in the data members when we birth the object
member function: we need functions that read or write or both the data members.  example: rectangle.getArea()  note: if you have a function that neither writes or reads the typically private data members...it doesn't belong in the class

[make a table]

[non runnable snippet showing the basic parts of a class with those 3 part labelled]

explain all the parts of the standard syntax

[example runnable with rectangle]

explain how the rectangle specifically works


thell how the item before the .  like rectangle.area() gets all the data members for free.  you can just say width or height but in some situations you need to say this-> to get to the specific variable

[example with a setWidth that needs this->]

preference: some peeps like to use prefixes of m_ on all datamembers.  there is no right or wrong approach.  it is the opinion of the book that you should name variables simply with what makes sense.  so in the example above the rectangle has width and the function parameter is also width but they are different.  that can be confusing but if you learn to use this-> in those situations to get to the objects data members then you can continue to use simple names

you can overload member functions and you can have defaults

[example with cup drink, empty, fill, etc percentFull]

class and structs really just the same thing.... you can use them in all sorts of weird (nonstandard ways)

structs can have member functions but that isn't typically don't do that most of the time to make sure we get goo encapsulation.

classes/structs can just be a collection of functions and no data mebers...  probably should use namespaces.

suggest use..struct just collection of variables
class data members, constructor, and member functions

[simple typical struct example]

[simple typical class example]

preference: start and stay here...while you can get much more advanced and wierder...this is the majority of OOP.


const
it is possible to apply const to your custom class.  when you do...any function that is not labelled const can't be called.  also functions even if labelled const can't change member variable

[example]

note: while this can be done...the book will rarely do it.  it is a bit of protection but some langauges like python survive just fine with no const concept and just a naming convention. know what it is so you can interface if you see it but you can safely write code without it and not even know what you are missing.  that said   it is common to pass by const reference so if you are doing that with a custom class of your making you might have to throw a few const labels of functions you need that don't modify the data

[example with const ref]

you can override with const and non const and depending one or the other would get called.  (not normally needed )

we have already seen public and private.  there is also protected

[table]

table about how the labels work and what is defualt for struct vs class

protected can come in handy (list a few examples) but the book will rarely use it.

you don't have to put private at the start of a class but it is nice to be explicit.  since struct is typically all public all the time...we don't list anything even though we could make stuff private but that isn't typical.  But class has both so it is nice to be explicity even though you could leave off the first private.  you don't have to follow this order but the book will do private data members, public constructor, then public functions.  occasionally you might want some private helper functions.

[example of class without private (commented out indicating they can play with it and everything still works) that still works]

naming... class and struct  TitleCase
memberVariables and memberFunctions camelCase

note: lots of people use different conventions such as _ prefix of m_.  consitency is key and picking and sticking with project wide style standards is important so you don't have to thing about naming too much.

[example of how m_ helps with confusion]

[example of same with this-> ]

with all this encapselation and abstraction there are some standard function we like to write

access functions of getters   explain

[example]

setters  explain

[example]

nameing  ... while setWidth and getWidth works and great.  the book will typically keep set for the setters but remove the get for the getters.  rectangle.setWidth(6) and rectangle.width()  explain the motivation because width(6) not clear but setWidth(6) is and width() is just as clear as getWidth()

getters should return by value (reference would be invalid if object dies...be safe) or const lvalue (if too expensive)

explain what an lvalue and rvalue are


if you find you self writing almost exclusively getters maybe a struct is better

[example of class that could be a better struct]

[the struct version]

also maybe you don't want to just have setThis and setThat.  instead of setHP maybe you want damage or heal to be more idomatic to your code.

[example]

also to get and set everything if access isn't actually needed  you can always add them as needed...it is easier to test if you have less public methods

also why private variables if you just go and make a setting...because you can add code to preserve an invariant

[example with rectangle and area data member that gets recalculated on setWidth or scale]

explain why rectangle.width=5 would break it but rectangle.setWidth(5) is fine.

don't return a nonconst reference to a private data member due to breaking encapsulation and potentially the invariant.

[example of bad code that pass a reference and then modifes the data member directly]


why encapsulate...to define the lines of interactions (interface) and seperate that from the implementation.  it actually doesn't matter how things are implemented as long as the interface is understode

[two examples with same interface but big differences in the implementation]

how cool is it that they work completely different but the user of the class doesn't have to know nor should they know the specifics.

note: sometimes for effiency it is important to know how the internals for example deque can have quick adds to beginning and end  while vector only the end.  O(n) O(1)  learn as you go.  write code...get it to work...benchmark...see issues...research...improve.  it would be insane to learn everything down to the smallest level of abstraction...  do you need to know where in memory...how it is distributed.  what assembly calls are generated...how the electrons flow through the transistor.  but we do want to know more and more as it is realvant.  so stay curious...test...improve.  It is a craft.  Code is like art...never done, never complete, could always be improved.  start with stick figures and go from there

the public things in a class is its public interface

the implementation while in the public functions is the private inner workers that the user doesn't actually have to know.

encapsulation can mean to put something in a container but in CS it almost always means data hiding.

we encapsulate to keep the testing/attack surface small and well behaved.  Don't expose what you don't need and you definetly don't want to test.

lets talk about constructors...expain initializer list  the job of a constructor is to construct...fill in the data members

[snippet of how java does]

gets called with ()

c++ has a special syntax so the {} are almost always blank.  it can get confusing with duplicate names but in the initializer list width{width}  is objVar{constructorParameter}

[example]

while you could put code in the {} to do this it isn't convention and technically there are two stages...initialization and then construction.  if you put in the initializer list...once a var is initialized...all data members will be filled.  if you put stuff in the {} then after initializition won't have been constructed yet.  it is subtle and won't likely cause you an issue but for consistent style the book will use initialize lists.

talk about naming constructors 

if you don't add one there is a default one   explain what it does

you can overload or use defaults

[example]

preference: you could use the default constructor (not have one) and rely on setters but then you have to have multiple lines for every object creation.  we obviously want to have a clean syntax

[snippet contrasting default with setters vs a constructor call]

initialize list can get long so you can list tabbe over.  debaut of where : and , go.  just be consistent...to start or not to start lines with the puncuations

[snippet of formatted initializer list]

[snippet of another perfectly fin formatted initialize list with : , the other place]

the order of the inializer list doesn't dictate the order of initialization.  it typically is the order of the data member

[example with expression that failes]

[example with expression and better order so compiles]

just keep the order of data members and inializer list the same to not get confused

talk about delegating constructors and how it is helpful (although defaults can ofter help) 

[delegation example within one class]

preference: while delegation and overloads can be wildly helpful...consider if one well designed constructor with defaults would get the job done.

[example]

talk about the copy constructor and what it is used for

[example]

but it is done for you with the implicite copy constructor

[simplier example]

note: simple classes should be able to get away with the implicit copy constructor.  future rule of 3/5 etc


this is a pointer.  explain the ->

you might return *this for chaining

[example]

you can set *this to a new object for nuclear options

[example]

classes are typically in h cpp pairs. 

[show 3 file example]

explain... ::

[snippet showing class forward.  and fleshing how functions in the cpp]

name files just like the class.  

class definitions are exempt from the ODR

inline (what you should use instead of static) is also exempt from the ODR

explain what inline/static does



[example...something like maxSize]

enum classes solved a problem  but imagine if you want an enum for a specific class...it already has a namespace... so just put a plain enum in the class.  a type in a type

[example]

there is a thing called a destructor.  explain

[example where it prints...I am dying]

with raw memory management this was very important but with RAII we still need destructors but it can all be automated and invisible to the users.  Occasionally you might have a function that is tryly managing some resource and the destructor is there to make sure everything is tidy  it get called on leaving scope or delete...also stuff like save to disk or the like would be a nice thing to use a destructor for

[example]

there is a default implicit do nothing constructor

there can only be one destruct... no args ...no return

a function end will triger object on that scope to destruct  but std::exit won't be careful

you can do classes and templates
[simple example]

or just on a function
[simple example]

all the same power


inline or static functions can't use object data members because these function work at the class level.  since they don't read or write to the data members...these function could typically be more simply just a nonclass plain function. (friend might be needed)

friend is something we can put on a nonmember function that needs to see the data members.  example a print function...a friend function is written in the class but isn't really part of the class...it being there just lets the compiler know that they are fiends.

[example]

also great for operator overloading

[example]

show how it works with multiple files

[example]



you can be fiends with more than one...use forward declarations

[example]

don't get too friendly if you already have getters that get everything.  friends open you up to potential risk so you should only make friends if you really need them.

[example of << overate that doesn't need to be a friend due to getters]

classes can also be friends with each other

[example]

note: pretty rare  friend mostly just for <<

you can also must one function a friend














