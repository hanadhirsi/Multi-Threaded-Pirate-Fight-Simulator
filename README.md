Author: Hanad Hirsi

Purpose: This program simulates a battle between a tortoise and a hare to fight againts pirates.
the program runs 100 simulations by default of 3 different scenarios where the tortoise and hare fight:
one where the tortoise has a sword, one where the hare has it, and one where they are both unarmed. After
simulating every battle, the program then returns the percentages of how often the tortoise and the hare
defeated all pirates together (success), how many times they won with only one of them left standing (part success), and how many times
they lost (failure)

Header files: 
defs.h contains all forward refrences, structure definitions and libraries used

Source files:
deque.c contains all deque manipulation functions

fighter.c contains all fighter and pirate manipulation functions

fightspecs.c contains functions to simulate the one battle agains 10 pirates

runspecs.c contains functions to run a single scenario and get the result

stats.c contains functions to calculate successes, part successes, and failures

main.c contains the main function and function to calculate random values

Makefile contains the compilation and linking commands



Compilation and Launching instructions:
To compile the program, unzip the file and type the command
"make" in command line in the project's directory.
This will run the Makefile that handles both the compiling 
and linking of the source files to create an executable called fp

To run the program, you must open the terminal in the directory the 
fp executable is contained, type the command ./fp (number of runs you would like)
to simulate the battle. if you do not type a number for the amount of runs 
you would like, it will default to 100.
