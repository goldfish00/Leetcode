[[_TOC_]]



# Leetcode

This repository is used to record leetcode question answers and some notes taken in the process of solving problems.

Now the main language used to solve the problems is C++. The index of the question is commented for later review and search.



## Some Problems That Are Temporarily Jumped over

The ***Linux Shell*** problems: 192 - 195

***SQL*** problems: 196 - 197



# Notes

## Graph

### Tree

For the graph to be a valid tree, it must have *exactly* `n - 1` edges. Any less, and it can't possibly be fully connected. Any more, and it *has* to contain cycles. Additionally, if the graph is fully connected *and* contains exactly `n - 1` edges, it can't *possibly* contain a cycle, and therefore must be a tree.

Therefore, the easiest way to check if a graph is a tree goes:

1. the graph has only `n-1` edges
2. the graph does not have cycles

or:

1. the graph has only `n-1` edges
2. those edges connects all the node together (no missing node)

