# Data Structure - GO

This is the note of data structures in GO. 

The syntax of GO is similar to that of C++, except that each statement does not need ending with *;* as it is in C++. 

In terms of declaration, the variables in GO can either be declared using *:=* or be declared using *var*. The difference between *:=* and *var* is taht *:=* declares a variable and gives value to it. When using *var*, different from the declaration in other languages, *var* is followed by the name of the variable and then followed by the type of the object. Examples are given in later part of this passage.

## Array

- Constructor

  ```GO
  // declare an array of size 5
  var array [5]int
  // declare an array of size 5 and elements in each position
  array := [5]int{10, 20, 30, 40, 50}
  // declare an array and specify the values in the array, without specifying the size
  array := [...]int{10, 20, 30, 40, 50}
  // declare an array of size 5, specify the value of the second and the third elements; other elements are initialized to be 0
  array := [5]int{1: 10, 2: 20}
  ```

  - Array of pointers

    Note that when we assign an array of pointers to another array of pointers, we have two array of pointers which point to the same set of element. By changing the value of one element would change the value that the pointer from the other array (shallow copy).

    ``` go
    // initialize array of pointers
    array := [5]*int{0: new(int), 1: new(int)}
    // giving values to the first two elements
    *array[0] = 10
    *array[1] = 20
    ```

- Visit elements in the array

  ```go
  // change the value of element
  array[2] = 10
  ```

- Array Assignment (Deep Copy)

  ```go
  var array1 [5]string // space for 5 string elements are reserved
  array2 := [5]string{"Red", "Blue", "Yellow", "Green", "Orange"}
  array1 = array2 // this copies the values of each element in array2 to the elements in array1
  array2[1] = "Red"
  fmt.Print(array1[1])
  ```

  The output would be *Blue*. Cannot assignment an array to another array whose size is different.

- Array comparator

  ```go
  var array1 [5]string
  array2 := [5]string{"Red", "Blue", "Yellow", "Green", "Orange"}
  array1 = array2
  fmt.Print(array1 == array2, "\n") // true
  array2[1] = "Red"
  fmt.Print(array1 == array2) // false
  ```

  This compares the value of elements in two arrays directly

- 

