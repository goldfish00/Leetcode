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



## Bit Manipulation

```c++
// a number xor itself is always 0
x ^ x  == 0; // evaluates to true

// 0 xor a number yields the number
0 ^ x == 0; // evaluate to true 

// compute the xor result of 1, ..., n
int res = 0
for (int i = 1; i <= n; ++i) {
  res ^= i;
}
// res will be:
// if n % 4 == 0, res == n
// if n % 4 == 1, res == 1
// if n % 4 == 2, res == n + 1
// if n % 4 == 3, res == 0

// if a number is a power of 2
x && (!(x & (x - 1))); // evualtes to true if x is a power of 2

// swap two numbers without extra space
a ^= b;
b ^= a;
a ^= b;

// bit operation with sum
(a|b) = (a+b) - (a&b)
(a+b) = (a^b) + 2*(a&b)
  
// set the first 1 from right of any number
x & (-x)
x - (x & -x)
x ^ (x & (~x + 1))
  
// 
```

