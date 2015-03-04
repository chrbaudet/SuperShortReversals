# SuperShortReversals

This package implements software for computing the distance between two
circular permutations considering the Sorting Circular Permutations by 
Super Short Reversals Problem.

-------------------------------------------------------------------------------- 
GENERAL INFORMATION:

The package is composed by two C/C++ programs and two perl scripts.

The C/C++ programs compute the distance between the given permutation and the
identity permutation.

The perl scripts receive a file containing a list of permutations and 
generate a distance matrix which can be used for generating phylogenetic trees 
using Neighbor Joining.

The file example.csv brings an example of input file for the perl scripts.

-------------------------------------------------------------------------------- 
COMPILING THE CODE:

To compile the code, go to the desired directory (database or heuristics) and
execute make:

make

To clean-up, type:

make clean

If you have problems to compile, edit Makefile and change the line:

STDLIB=c++11

by

STDLIB=c++0x

If it does not work, please, contact us.
