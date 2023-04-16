#### Approach 1: Brute Force

We use the same brute force method as we used in [2D Immutable version](https://leetcode.com/problems/range-sum-query-2d-immutable/solution/) to calculate the sum of region. In addition to the previous problem, here we have to update the value of the matrix as well, which we simply do with `data[row][col] = val`.

**Algorithm**

Below is the implementation of this approach.

- Time Complexity
  - **sumRegion** - O(MN)O(MN)*O*(*MN*) per query. Where MM*M* and NN*N* represents the number of rows and columns respectively, each *sumRegion* query can go through at most M×NM \times N*M*×*N* elements.
  - **update** - O(1)O(1)*O*(1) per query.
- Space Complexity: O(1)O(1)*O*(1).

------

#### Approach 2: Using Binary Indexed Tree

**Intuition**

The problem differs than the [2D Immutable version](https://leetcode.com/problems/range-sum-query-2d-immutable/solution/) as there is an additional update method that changes the values present inside the matrix, hence it's not even a good choice to cache or pre-compute all the results. There is a special data structure called **Binary Indexed Tree** that we will use to solve this problem efficiently which is based on the idea of storing the *partial sums*. We then use these partial sums to obtain the overall sum in the *sumRegion* method. The way we store these partial sums in a Binary Indexed Tree (BIT), a.k.a. Fenwick Tree, allows us to achieve both the update and query to be done in logarithmic time.

Consider the case of 1-D array. Assume we have an array `nums` of size 8 (`nums[1], nums[2] ... nums[8]`) (1-based indexing). We store the partial sums of the array `nums` in another array `bit` of size 8 (`bit[1], bit[2] ... bit[8]`). The idea is to compute each value of `bit` array in a way that allows us to "quickly" compute the sum as well as update the values for the array `nums`. We do it using the idea of bit manipulation.

Each number can be represented as sum of power of two's and this is what will allow us to obtain the overall sum from the partial sums. For example, 7 can be represented as 1+2+4=(20+21+22)1 + 2 + 4 = (2^{0} + 2^{1} + 2^{2})1+2+4=(20+21+22) hence whenever we want to calculate the cumulative sum till 7th index in the **nums array**, we will utilize the values stored in the 1st, 2nd and 4th index in the **bit array**. Here in case of Binary Indexed Tree, the 1st, 2nd and 4th index of the `bit` array will store the **non-overlapping partial sums** which can be added up to obtain the cumulative sum till 7th index in the `nums` array. Hence, we have cum_sum(7)=bit[1]+bit[2]+bit[4]=a[1]+a[2]+...+a[7]cum\_sum(7) = bit[1] + bit[2] + bit[4] = a[1] + a[2] + ... + a[7]*c**u**m*_*s**u**m*(7)=*bi**t*[1]+*bi**t*[2]+*bi**t*[4]=*a*[1]+*a*[2]+...+*a*[7] (where cum_sum(7) refers to cumulative sum till 7th index of `nums` array). But how do we obtain the sum in such a manner? For this, consider the `bit` array as shown below (let's assume that we can efficiently obtain the below mentioned array, we'll discuss later how we can actually do it).

```
bit[1] = nums[1]
bit[2] = nums[1] + nums[2]
bit[3] = nums[3]
bit[4] = nums[1] + nums[2] + nums[3] + nums[4]
bit[5] = nums[5]
bit[6] = nums[5] + nums[6]
bit[7] = nums[7]
bit[8] = nums[1] + nums[2] + nums[3] + nums[4] + nums[5] + nums[6] + nums[7] + nums[8]
```

When we try to calculate cumulative sum till any index *n* the steps that we follow are.

1. Decompose *n* as the sum of power of 2's. Let's say n=n1+n2+...+nkn = n_{1} + n_{2} + ... + n_{k}*n*=*n*1+*n*2+...+*n**k* where each of the number nin_{i}*n**i* is a number which is a power of 2. For example, When n=7n = 7*n*=7, we have n1=1,n2=2,n3=4 (7=1+2+4)n_{1} = 1, n_{2} = 2, n_{3} = 4\ (7 = 1 + 2 + 4)*n*1=1,*n*2=2,*n*3=4 (7=1+2+4)
2. The cumulative sum till index `n` in the `nums` array can then be obtained with the help of `bit` array as cum_sum(n)=bit[n1]+bit[n2]+...+bit[nk]cum\_sum(n) = bit[n_{1}] + bit[n_{2}] + ... + bit[n_{k}]*c**u**m*_*s**u**m*(*n*)=*bi**t*[*n*1]+*bi**t*[*n*2]+...+*bi**t*[*n**k*]

As mentioned before, since we'll store the values in the bit array as **non-overlapping partial sums**, that's why step 2 is possible and gives us the cumulative sum as the sum of the values from the `bit` array. The question that we must ask now is - How can we build the `bit` array in such a manner? For this, we need to do two things.

1. Understand lsb (least significant bit, non-zero) of a number.
2. Observe the pattern of occurence of each number from `nums` array in the `bit` array.

#### LSB (least significant bit)

Consider the binary representation of 5 (`5 -> 101`). The least significant (non-zero) bit of a number is obtained by taking the right most non-zero bit from the binary representation and ignoring all the other bits (i.e. considering all the other bits as 0). Hence `lsb(5) = 001` (considering only the rightmost non-zero bit and ignoring all others). Similarly `lsb(6) = 010`. Why? Since `6 -> 110` and the right most set bit occurs at the second position.

Next, let's notice the occurence of each element of nums array in the bit array as follows.

```rust
nums[1] isPresentIn -> bit[1], bit[2], bit[4], bit[8]
nums[2] isPresentIn -> bit[2], bit[4], bit[8]
nums[3] isPresentIn -> bit[3], bit[4], bit[8]
nums[4] isPresentIn -> bit[4], bit[8]
nums[5] isPresentIn -> bit[5], bit[6], bit[8]
nums[6] isPresentIn -> bit[6], bit[8]
nums[7] isPresentIn -> bit[7], bit[8]
nums[8] isPresentIn -> bit[8]
```

Let's convert all the indices shown above into their binary representation. We then have (indices for nums array on the LHS and bit array on the RHS)

```rust
LHS        -> RHS
nums[0001] -> bit[0001], bit[0010], bit[0100], bit[1000]
nums[0010] -> bit[0010], bit[0100], bit[1000]
nums[0011] -> bit[0011], bit[0100], bit[1000]
nums[0100] -> bit[0100], bit[1000],
nums[0101] -> bit[0101], bit[0110], bit[1000]
nums[0110] -> bit[0110], bit[1000]
nums[0111] -> bit[0111], bit[1000]
nums[1000] -> bit[1000]
```

On seeing the pattern above, we can notice that the sequence of indices on the RHS can be obtained by continuously adding the number to it's lsb, starting from the index on the LHS.

Example

```rust
0101 -> (add 0001) -> 0110 -> (add 0010) -> 1000
```

We can use this observation to build the bit array as we now know all the indices in the `bit` array where a particular value from the `nums` array occurs.

Note: We have used 1-based indexing at all the places in the 1-D BIT explanation part.

```c++
int bit[];  // initialize all entries in bit array to 0
int nums[]; // given nums array
int n;      // size of nums array

int lsb(int n) {
    // the line below allows us to directly capture the right most non-zero bit of a number
    return n & (-n);
}

int buildBIT() {
    for (int k = 1; k <= n; ++k) {
        int i = k, val = this->nums[k];
        // keep adding lsb(i) to i and add val to bit[i]
        while (i <= n) {
            this->bit[i] += val;
            i += lsb(i);
        }
    }
}
```



The process of adding a particular number `val` to the appropriate locations in the `bit` array is what is known as the *update* process in a Binary Indexed Tree. Hence we can re-write the above code as.

```c++
int bit[];  // initialize all entries in bit array to 0
int nums[]; // given nums array
int n;      // size of nums array

int lsb(int n) {
    // the line below allows us to directly capture the right most non-zero bit of a number
    return n & (-n);
}

void updateBIT(int i, int val) {
    // keep adding lsb(i) to i and add val to bit[i]
    for (; i <= n; i += lsb(i)) {
        this->bit[i] += val;
    }
}

int buildBIT(int n) {
    for (int k = 1; k <= n; ++k) {
        int i = k, val = this->nums[k];
        updateBIT(i, val);
    }
}
```



Below is the animation of the `buildBIT` process for the array `[2, 3, 1, 2, 4, 1, 2, 3]`. We initialize all the elements of the `bit` array to zero and then build it.

 

Having a separate update method also allows us to perform the "updates" in a Binary Indexed Tree, i.e. if we want to change the values of `nums[i]` from an old value `a` to new updated value `b`, we simply calculate the difference `b - a` and call the update function as `updateBIT(i, b - a)` (note that we do not change the actual `nums` array, only the `bit` array changes). We still haven't implemented the `sumRegion` for our 1-D example here. This is known as "query" method for a Binary Indexed Tree. When query method is called for a particular index `i` on the Binary Indexed Tree, it returns the cumulative sum till the index `i`. Similar to update method, where we kept adding the lsb of the index to itself, here, we'll keep subtracting the lsb of the index from itself to calculate the cumulative sum from partial sums stored in `bit` array. The code is as follows.

```c++
int bit[];  // initialize all entries in bit array to 0
int nums[]; // given nums array
int n;      // size of nums array

int lsb(int n) {
    // the line below allows us to directly capture the right most non-zero bit of a number
    return n & (-n);
}

int queryBIT(int i) {
    int sum = 0;
    for (; i > 0; i -= lsb(i)) {
        sum += this->bit[i];
    }
    return sum;
}
```



Below is the animation of the query process for the array `[2, 3, 1, 2, 4, 1, 2, 3]` in case of `index = 7`, i.e. we are trying to calculate the cumulative sum till the 7th index of the nums array.

 

We can now use the `queryBIT` and `updateBIT` methods to obtain the sum between any two indices `(i, j)` and can update the value at any given index `i` as follows

```c++
int query(int i, int j) {
    // Subtract the cumulative sum till (i - 1)th index from cumulative sum
    // till jth index to obtain the sum from ith index to jth index.
    // i.e. sum[i..j] = cum_sum[j] - cum_sum[i - 1]
    return queryBIT(j) - queryBIT(i - 1);
}

void update(int i, int val) {
    // Calculate the difference between old value and new value and
    // add the difference to the bit array
    int old_val = query(i, i);
    int diff = val - old_val;
    updateBIT(i, diff);
}
```



**Complexity Analysis**

- Time Complexity
  - Update (1D) - O(log⁡N)O(\log{N})*O*(log*N*)
  - Query (1D) - O(log⁡N)O(\log{N})*O*(log*N*)
  - Build (1D) - O(N⋅log⁡N)O(N \cdot \log{N})*O*(*N*⋅log*N*)
  - Here N denotes the number of elements present in the array. Maximum number of steps that we'll have to iterate for update and query method is upper bounded by the number of bits in the binary representation of the size of the array (N).
- Space Complexity
  - O(N)O(N)*O*(*N*) - Since we'll need an extra `bit` array to store the non-overlapping partial sums.

We now have the required pre-requisites to implement an efficient solution for the case of 2D arrays (or matrix), which we'll see next.

**Note**: The build method can be optimized further and can be done in time O(N)O(N)*O*(*N*). We do this by adding the entry from the nums array to the immediate next entry in the `bit` array, i.e. the next higher index that the value from the nums array contributes to. Below is the implementation for this

```c++
void buildBIT() {
    // copy the nums array in bit array first (1-based indexing)
    // O(N) operation
    for (int i = 1; i <= n; ++i) {
        this->bit[i] = this->nums[i];
    }

    // Build BIT array by adding the value at i'th index to next immediate index
    // O(N)
    for (int i = 1; i <= n; ++i) {
        int j = i + lsb(i);
        if (j <= n) {
            // Add to the immediate next position
            this->bit[j] += this->bit[i];
        }
    }
}
```



#### 2D BIT

Till now, we have seen how to perform "query" and "update" in case of 1-D example. We'll try to extend this to 2D array (matrix) now.

In case of 1D example, we were iterating directly over the indices of the array in 1 direction, but here in the case of a matrix, we have a 2-dimensional indices. Hence in order to use the concept of BIT for 2D case, we'll iterate in both the directions, i.e. over the rows and columns of the matrix to perform the update and query method. If `i` and `j` represents the indices corresponding to rows and columns that are used for iterating over the matrix, we simply increment these variables by `lsb(i)` and `lsb(j)` in the update operation and decrement by `lsb(i)` and `lsb(j)` in decrement operation. Another change that happens in the case of 2D bit is, the partial sums that we store now are corresponding to partial sum of the non-overlapping sub-rectangles or sub-matrix present in the matrix.

The update and the query for the 2D matrix then are as follows.

```c++
int rows; // number of rows in the matrix
int cols; // number of colums in the matrix

void updateBIT(int r, int c, int val) {
   // keep adding lsb(i) to i, lsb(j) to j and add val to bit[i][j]
   // Using two nested for loops, one for the rows and one for the columns
    for (int i = r; i <= rows; i += lsb(i)) {
        for (int j = c; j <= cols; j += lsb(j)) {
            this->bit[i][j] += val;
        }
    }
}

int queryBIT(int r, int c) {
    int sum = 0;
    // keep subtracting lsb(i) to i, lsb(j) to j and obtain the final sum as the sum of non-overlapping sub-rectangles
    // Using two nested for loops, one for the rows and one for the columns
    for (int i = r; i > 0; i -= lsb(i)) {
        for (int j = c; j > 0; j -= lsb(j)) {
            sum += this->bit[i][j];
        }
    }
    return sum;
}
```



The build method in case of 2D array can be implemented as follows.

```c++
int rows; // number of rows in the matrix
int cols; // number of colums in the matrix

void buildBIT() {
    for (int i = 1; i <= rows; ++i) {
        for (int j = 1; j <= cols; ++j) {
            // call update function on each of the entries present in the matrix
            int val = this->matrix[i][j];
            updateBIT(i, j, val);
        }
    }
}
```



We can now use the `queryBIT` and `updateBIT` methods to obtain the sum for any rectangular region, denoted by `(row1, col1)` and `(row2, col2)` and can update the value at any given location `(row, col)` as follows

```c++
int query(int row1, int col1, int row2, int col2) {
    // Sum of the region inside the matrix can be calculated using the logic present [here](https://leetcode.com/problems/range-sum-query-2d-immutable/solution/) in Approach 4
    return queryBIT(row2, col2) + queryBIT(row1 - 1, col1 - 1) - queryBIT(row2, col1 - 1) - queryBit(row1 - 1, col2);
}

void update(int row, int col, int val) {
    // Calculate the difference between old value and new value
    // and add the difference to the bit array
    int old_val = query(row, col, row, col);
    int diff = val - old_val;
    updateBIT(row, col, diff);
}
```



The overall solution code for 2D case is as follows.

Note that there will be some minor modifications in the final implementation from the code snippets provided above as the input that we have here is based on 0-based indexing and not 1-based indexing. Hence we'll take that into account in the final implementation.

```c++
class NumMatrix {
private:
    int rows, cols;
    vector<vector<int>> bit; // The BIT matrix

    int lsb(int n) {
        // the line below allows us to directly capture the right most non-zero bit of a number
        return n & (-n);
    }

    void updateBIT(int r, int c, int val) {
        // keep adding lsb(i) to i, lsb(j) to j and add val to bit[i][j]
        // Using two nested for loops, one for the rows and one for the columns
        for (int i = r; i <= rows; i += lsb(i)) {
            for (int j = c; j <= cols; j += lsb(j)) {
                this->bit[i][j] += val;
            }
        }
    }

    int queryBIT(int r, int c) {
        int sum = 0;
        // keep subtracting lsb(i) to i, lsb(j) to j and obtain the final sum as the sum of non-overlapping sub-rectangles
        // Using two nested for loops, one for the rows and one for the columns
        for (int i = r; i > 0; i -= lsb(i)) {
            for (int j = c; j > 0; j -= lsb(j)) {
                sum += this->bit[i][j];
            }
        }
        return sum;
    }

    void buildBIT(vector<vector<int>> &matrix) {
        for (int i = 1; i <= rows; ++i) {
            for (int j = 1; j <= cols; ++j) {
                // call update function on each of the entries present in the matrix
                int val = matrix[i - 1][j - 1];
                updateBIT(i, j, val);
            }
        }
    }

public:

    NumMatrix(vector<vector<int>>& matrix) {
        rows = matrix.size();
        if (!rows) return;
        cols = matrix[0].size();
        bit.resize(rows + 1);
        // Using 1 based indexing, hence resizing the bit array to (rows + 1, cols + 1)
        for (int i = 1; i <= rows; ++i)
            bit[i].resize(cols + 1, 0);
        buildBIT(matrix);
    }

    void update(int row, int col, int val) {
        int old_val = sumRegion(row, col, row, col);
        // handling 1-based indexing
        row++; col++;
        int diff = val - old_val;
        updateBIT(row, col, diff);
    }

    int sumRegion(int row1, int col1, int row2, int col2) {
        // handling 1-based indexing
        row1++; col1++; row2++; col2++;
        int a = queryBIT(row2, col2);
        int b = queryBIT(row1 - 1, col1 - 1);
        int c = queryBIT(row2, col1 - 1);
        int d = queryBIT(row1 - 1, col2);
        return (a + b) - (c + d);
    }
};
```





**Complexity Analysis**

- Time Complexity
  - Update (2D) - O(log⁡N⋅log⁡M)O(\log{N} \cdot \log{M})*O*(log*N*⋅log*M*)
  - Query (2D) - O(log⁡N⋅log⁡M)O(\log{N} \cdot \log{M})*O*(log*N*⋅log*M*)
  - Build (2D) - O(N⋅M⋅log⁡N⋅log⁡M)O(N \cdot M \cdot \log{N} \cdot \log{M})*O*(*N*⋅*M*⋅log*N*⋅log*M*)
  - Here N denotes the number of rows and M denotes the number of columns.
- Space Complexity
  - O(NM)O(NM)*O*(*NM*) - Since we'll need an extra `bit` matrix to store the non-overlapping partial sums