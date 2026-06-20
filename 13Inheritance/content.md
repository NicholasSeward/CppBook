we now know how to make basic classes

sometimes we want to make a class similiar to one we have already made.  C++ lets you build off existing classes with inheritance.  

note: some inheritance is good but too many layers of it can be horrible to maintain.  Keep it simple...add if it help not just because the problem could be solved with it.

imagine you have a polygon, triangle, quadrilateral, rectangle, square.

[mermaid diagram]

triangle class can steal all the stuff that polygon already has but add on anything specific to triangle.

same for rectangle and square

[example of rectangle with square inheriting]

explain the parts

have to be careful.  private data members might hide info from a child class.  you can either have getters for what is needed or make them protected

one beautiful thing you get with this is polymorphism.  Way to fancy of a word for a very simple thing.  you can make a vector of polygons and loop through and get the area of each different polygon.  rectangles would call the area function in the rectangle class and triangles would call the area function in the triangle class.  objects can take many (poly) forms (morph)

while this is awesome there are some potential ways to mess this up with object slicing. 

basic inheritance

you have parent or base classes.  sometimes called superclasses

when you inherit from it like square would do with rectangle you get a child/derived/sub class

[diagram with level]

explain the base and sub classes.  how one child can be a parent to another

make a generic person class
[example]

if we have an employee that would need a employeeid and salary in addition to age and name you could solve this in a few ways

- make Employee have 4 data members (simple and often a good choice  depends on what else is going on)
- make Employee have the two specific plus store a person (logically odd but would work)
- inherit and add 2 new data members (clean but have to get access right etc)

[example with Employee inherit from Person]

[diagram]

more than one thing can inherit from Person

[example with Volunteer]

you can inherit from a child like Employee like Supervisor

[example]

if you ever decide to change Person it would change all the other classes too.  This is a pro and a con because it can make the work easier but it could also break more things.

inheritance is like a layer cake...the bottom is the base and as you move up layer by layer you add more data members

[mermaid diagram of supervisor,employee,person data member layers]

[example with 3 layers where it prints when each constructor goes]

you have to instantiate the base before you move up

Something of type Person can only store the bottom layer.  if you put a Employee into a Person memory slot it will slice off the top.  object slicing.  the solution to this and to let polymorphism work is we hold onto pointers for object.  We can have a pointer to a Person but what is actually in memory can be a person, employee or supervisor since there is no need for a set size.  

[example with object slicing]

[example with pointers that does work]

let's talk about construction and getting all the data members set

you call the derived class constructor but it has a job to call the super class parent class constructors.  if you don't do it explicityly it calls the default one.

the initialize list won't let you initialize members from parent classes.  so what you do use a parent constructor in the initialize list

so supervisor would :Employee{blah,blah}, var{var}

you may wonder why supervisor doesn' need to use the Person constructor but Employee can do thst...you only need to worry about your parent.  then yourself

[example]


construction is from base up...so desctrution is from top down

[example with classes A B C D.  in a inheritance chain show construction sequence and destruction sequence]

you may have noticed that we have stuck with public and private and that is what should normally be done.  however  you can make a data member protected and then any derived class can see it which is still some encapsulation

[example with protected]

note: we won't do this much to make each class easy to test in isolation

you may have also noticed we always do :public Base.  This just leaves all access the same as in the base.  :protected downgraded any publics to protected.  :private downgrades any protected and publics to private.  or blank is same as private

[table showing base public protected private and what they get dowgraded to for inheritance type public protected or private]

we will always use public to leave the access unchanged.  

note:there is no way to upgrade access without going into the base class.

note: :private will remove some of the public interface which is almost never what you want


why use inheritance...to add functionality


[example]

solution where can call a base function to build on it in a derived

[example]

you can hide a base version with an overload

there is the ability to upgrade from proteccted to public and delete functions

[example]

note: not common

you can inherit from more than one parent.  sound good and biological but can cause issues.

[diagram with two parents classes]

the problem is a diamond.  does the bottom class have 1 or two copies of the top class.

[diamond diagram PoweredDevice -> Scanner/Printer -> Copier]

while you can do it...don't do it.  it is the suggestion of the book to limit each class to have one parent.

[example of mutliple inheritance]

The things you can gain with multiple inheritance can be solved with other other design patterns. multiple inheritance is generally associated with poor design.

most langauges don't support multiple inheritance so you can safely ignore it.  and use more language agnostic archetecture for your solutions.

