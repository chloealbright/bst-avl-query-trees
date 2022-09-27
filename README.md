# Project 2

The parts of assignment were completed:
```
The Big 5 (Set to default): default constructor, destructor, copy constructor, copy assignment,
move constructor, move assignment.
SequenceMap Constructor.

Comparison operators: <, >, =
Overload Output operator <<
Overload Input operator >>

Size()
Find()
FindNode()
Depth()
RemoveThirdSeq() (--> Optional, didn't use)


```

Any bugs that you have encountered: 
```
Pointers for 2c gave segmentation fault in avl_tree_mod.
```

The input file (if any) and the output files (if any):
```
README.md
sequence_map.h
avl_tree.h
bst_tree.h
query_tree.cc
test_tree.cc
test_tree_mod.cc
avl_tree_mod.h
sequences.txt (used to test with code)
rebase210.txt (used to test with code)

```

Complete instructions of how to run your program(s):
To compile on terminal, type: 
```
For part 2A:
make all
make clean
g++ query_tree.cc -o query_trees  -std=c++11
./query_trees rebase210.txt AVL < input_part2a.txt

Part2B:
Make all
Make clean
g++ test_tree.cc -o test_tree -std=c++17
./test_tree rebase210.txt sequences.txt AVL

Part2C:
Make all
Make clean
g++ test_tree_mod.cc -o test_tree_mod -std=c++17
./test_tree_mod rebase210.txt sequences.txt 


```

```bash
make clean
make all
```

To delete executables and object files, type:

```bash
make clean
```

To run, type:

```bash
./test_points3d
```

## Providing Input from Standard Input

To run with a given file that is redirected to standard input:

```bash
./test_points3d < test_input_file.txt
```
