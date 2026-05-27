It is important humans and to some degree AI to have your code well formatted following conventions.  C++ is a whitespace independent language which can allow some truely horrendous code to be made.  Most classes and employers and projects won't accept code unless it follows the specified formatting standard.  we will look at common formatting but make sure you match what is required

for the most part whitespace is ignored but it is need to seperate some elements.

int x vs intx

however where one space can go usually you can put as much whitespace as you want

int
x

single line comments are terminated by newlines

[example of correct but poorly formated code]

[example of properly formated hello world]

guideline
blank lines between functions
try not to make lines over 80 characters
try not to have a statement span more than one line
{} column alligned
body of codeblock{} indented

open curly tab
closed curly untab

note: indents can be tabs or spaces.  doesn't matter. the ide can make the tab button do either.  you can set it if you care but in c++ it doesn't matter.  in python the standard is to use 4 spaces.  again...the ide probably knows this and will just get it right.  but if you copy and paste code with different types of indents to a white space dependent langauge like python...you might get in trouble.

note: There is another style of {} placement and it is probably more common in old code but most langauges and modern c++ suggest the column alligned approach.  This makes match up paired {} easier.  You can do either but you should be consistent.

[example of old {} placement]

protip: the ide typically has a line a 80 characters.  if you go over a couple...leave it...80 is just when you should start thinking about rewriting it.

protip: AI and IDE can easily format code nowdays.  Automatic formatting should be done as part of your process.

official style guide
companies, classes, projects etc might have a published style guild.  

http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines
https://google.github.io/styleguide/cppguide.html
https://llvm.org/docs/CodingStandards.html
https://gcc.gnu.org/codingconventions.html

This text book will very roughly follow the c++ core guidelines
