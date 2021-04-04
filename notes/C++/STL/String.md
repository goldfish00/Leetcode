# String

## Substring

- erase by index and specified length: 
  `string& erase (size_t pos = 0, size_t len = npos);`
  
- erase a specified character and return the iterator to the character now occupies the postion that belonged to the erased character:
  `iterator erase (iterator p);`
  
- erase a range specified by $[first, last) $, and return the iterator to the character now occupies the postion that belonged to the erased character:
  `iterator erase (iterator first, iterator last);`

  **Complexity**: *O\(the length of the new string\)*, guess what the function does is just generating a new string without specified character(s)

   

## Erase



 

## Append

