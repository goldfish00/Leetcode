# Data Structure - GO

This is the note of data structures in GO. 

The syntax of GO is similar to that of C++, except that each statement does not need ending with *;* as it is in C++. 

In terms of declaration, the variables in GO can either be declared using *:=* or be declared using *var*. The difference between *:=* and *var* is taht *:=* declares a variable and gives value to it. When using *var*, different from the declaration in other languages, *var* is followed by the name of the variable and then followed by the type of the object, but when using *:=*, one should not specify the type of the variable/object since it is implied already. Examples are given in later part of this passage.

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

  - Two dimensional array

    ```go
    // declare a two dimensional array with four rows and two columns
    var array [4][2]int
    // declare and specify the values
    array := [4][2]int{{10, 11}, {20, 21}, {30, 31}, {40, 41}}
    array := [4][2]int{1: {20, 21}, 3: {40, 41}}
    array := [4][2]int{1: {0: 20}, 3: {1: 41}}
    
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

  The output would be *Blue*. We cannot assignment an array to another array whose size is different, and insisting on doing so would result in an error.

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

- Pointer of array: similar to that in C++, we can pass by reference by passing in the pointer of an array. Here is an example:

  ```go
  func foo(array *[10]int){
    ...
  }
  
  var array [10]int
  foo(&array) //by calling &, we get the point to the array
  ```



## Slices

The data structure, *Slice* in GO is very much similar to the *vector* type in C++. The *slice* type has three memebr variables: the starting address, length and capacity. On a 64-bit machine, *slice* need 24 bit.

- Constructor

  ```go
  // decalre a slice with 3 elements and spaces for 5 elements
  // the second parameter is similar to vector.resize() in C++
  // the third parameter is similar to vector.reserve() in C++
  // if the second parameter is larger than the third parameter, an error would show up
  slice = make([]int, 3, 5)
  // declare a nil slice; the nil slice is used to compare; slices can only be compared to nil and cannot
  // be compared to other slices
  var slice []int
  // declare an empty slice
  slice := make([]int, 0)
  slice := []int{}
  // specify the values of the elements
  slice := []int{10, 20, 30, 40, 50}
  ```

- Create *slice* from exsting *slice*: doing so, the new *slice* will still point towards specified element in the old *slice*, *i.e.* change the value of one slice may lead to the change of value in the other *(shallow copy)*

  ```go
  // create a slice of size j - i and volumn of k - i where k is the volumn of the old slice
  slice_new := slice[i : j]
  ```

- Add element to the slice: `append`

  ```go
  // add values to slice using append
  // slice: 10 20 30 40 50
  slice := []int{10, 20 , 30, 40, 50}
  // newSlice: 20 30
  newSlice1 := slice[1: 3]
  // newSlice: 20 30 60
  // slice: 10 20 30 60 50
  newSlice1 = append(newSlice1, 60)
  
  // deep copy using append: add elements and volumn to the slice
  // deep copy will only be triggered when the volumn is consumed
  newSlice2 := append(slice, 50)
  ```

- three indices

  ```go
  // we can create new slice from the old one using three indices
  source := []string{"Apple", "Orange", "Plumb", "Banana", "Grape"}
  // for slice[i:j:k]: i is the starting index; length = j - i; volumn = k - i
  // length 1, volumn 2
  slice := source[2: 3: 4]
  ```

- iteration

  ```go
  // for range iteration
  // *value* is a copy of the elements in slice; thus the address of *value* variable is always the same
  for index, value := range slice {
    ...
  }
  
  // to ignore the index, we can use '_'
  for _, value := range slice{
    ...
  }
  
  // traditional for loop
  // for a slice, len(slice) will return the size of the slice while cap(slice) will return the capacity/volumn of the slice
  for index := 0; index < len(slice); index++{
    ...
  }
  ```

- Multi-dimensional slice

  ```go
  slice := [][]int{{10}, {10, 20}}
  ```

- Pass slices into function

  ```go
  // pass the slice in as parameter and return a slice
  // pass the slice itself will make a copy of the slice (starting address, length and capacity)
  // passing the slice as parameter would not require to make a copy of the array of elements
  func foo(slice []int) []int {
    ...
    return slice
  }
  ```

  

## Map

The *map* type in GO is much the same as the *unordered_map* type in C++ and *dictionary* in Python

```go
// Constructor
// note that *slice* cannot be key
// key: string type; value: int type
dict := make(map[string]int)
dict := map[string]string{"A": "a", "B": "b"}
dict := map[string][]string{}

// cannot add elements to nil map
// create a nil map
var colors[string]string
// this would result in a Runtime error
colors["red"] = "red"

// whether a key is in the map
value, exist := colors["Blue"]
if exist {...}
// or we can use the returned value to decide whether the key is in the map
value = colors["Blue"]
// if the key deos not exist, value will be given the zero value of its type
if value != "" {...}

// Deletion
delete(colors, "Coral")

// Iteration
for key, value := range colors {...}

// Pass into function
// when a map is passed into function, the address of it is passed, which means that operation in the function
// can change the key-value pair stored in the map
func foo(colors map[string]string){...}
```

