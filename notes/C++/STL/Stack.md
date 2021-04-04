# Stack

## Introduction

***Stack*** in C++ is implemented using *deque* in C++, if no specific container from *vector*, *list* or *deque* is specified. Thus, the *push_back* function in ***Stack*** may be more efficient than that of ***Vector***, given that ***Vector*** uses an array which requires copy and paste if it is not reserved to the right size. Compared to using ***Deque*** directyly, using a ***Stack*** may save the time to think about member function, since much fewer member functions are supported.



## Member Functions

- **constructor**: can construct using an existing *vector*, *deque*, or *list*. Wec can also initialize an empty *stack* using a specified container:
  `std::stack<int,std::vector<int> >`
  `std::stack<int,std::deque<int> >`
- `push`
- `emplace`: push an element in place without making a copy as what is done with `push`
- `empty`
- `pop`
- `size`
- `swap`: exchange the contents of two stacks by swapping the address, thus the complexity is constant
- `top`