# SAT-N

This is a very naive implementation of parsing a boolean formula and creating a parse tree for it. The parsed formula then goes through a Tesitin transformation and into the famous DPLL algorithm for showing if the input formula is satifiable or not.

## How to build
Run the command in the root folder: $ mkdir build && cd build && cmake ..

A make file is created in the build folder, then run command in the build folder: $ make

## How to run
After "make" command runs successfully, an executable name "satn" is created in the build folder.

## Sample input
Sample input is present in the "test" folder

## Other details
Few details in the notes.txt file.
This code is not optimized code, its very badly written currently. It does not work for very large formulae.
