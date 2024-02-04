#ifndef STRING_H
#define STRING_H

#include <cstring> /* strlen, strncmp */
#include <algorithm> /* std::max, std::min, std::swap */
// DO NOT #INCLUDE ANY OTHER LIBRARIES - YOU WILL LOSE POINTS

// Project Identifer: 5AE7C079A8BF493DDDB6EF76D42136D183D8D7A8

/**************************************************************************************************\
|    EECS 281 Lab 3: String Library                                                                |
|                                                                                                  |
|    During lab, you learned about C++ strings and how they work. In this coding exercise, you     |
|    will be implementing a select few functions from the C++ <string> library. If you do not      |
|    understand everything in this file, do not worry! You will only need to complete the          |
|    functions marked with a TODO, and we will provide you with all the information you need       |
|    to complete this assignment. To locate the portions of this file you need to complete,        |
|    simply find all the TODOs in this file (but feel free to explore the rest, if you wish).      |
|                                                                                                  |
\**************************************************************************************************/

// This lab assignment was written by Jake Hage and Andrew Zhou for Winter 2019 and simplified for
// Fall 2019. For instructions on how to implement this lab, please see the lab assignment.

// a simple class for error exceptions - msg points to a C-string error message
struct Error {
    explicit Error(const char* msg_ = "") : msg(msg_) { }
    const char* const msg;
};

// Simple exception class for reporting String errors
struct String_exception {
    explicit String_exception(const char* msg_) : msg(msg_) { }
    const char* msg;
};

class String {
public:
    // Default initialization is to contain an empty string with no allocation.
    // If a non-empty C-string is supplied, this String gets minimum allocation.
    String(const char* cstr_ = "");
    // The copy constructor initializes this String with the original's data,
    // and gets minimum allocation.
    String(const String& original);
    // Move constructor - take original's data, and set the original String
    // member variables to the empty state (do not initialize "this" String and swap).
    String(String&& original) noexcept;
    // deallocate C-string memory
    ~String() noexcept;

    // Move assignment - simply swaps contents with rhs without any copying
    String& operator= (String&& rhs) noexcept;

    /* Swap the contents of this String with another one.
    The member variable values are interchanged, along with the
    pointers to the allocated C-strings, but the two C-strings
    are neither copied nor modified. No memory allocation/deallocation is done. */
    void swap(String& other) noexcept;

    // Assignment operators
    // Left-hand side gets a copy of rhs data and gets minimum allocation.
    // This operator use the copy-swap idiom for assignment.
    String& operator= (const String& rhs);
    // This operator creates a temporary String object from the rhs C-string, and swaps the contents
    String& operator= (const char* rhs);

    // Return a reference to character i in the string.
    char& operator[] (size_t i);
    const char& operator[] (size_t i) const;    // const version for const Strings

    // Accessors
    // Return a pointer to the internal C-string
    const char* c_str() const;
    // Return size (length) of internal C-string in this String
    size_t size() const;
    // Return current allocation for this String
    int get_allocation() const { return allocation; }

    /* These functions find the first and last characters of a String object. */
    char& front();
    char& back();

    /* Return a String starting with i and extending for len characters
    The substring must be contained within the string.
    If both i = size and len = 0, the input is valid and the result is an empty string.
    Throw exception if the input is invalid. */
    String substr(size_t pos, size_t len = npos) const;

    // Modifiers
    // Set to an empty string with minimum allocation by create/swap with an empty string.
    void clear();

    /* Remove the len characters starting at i; allocation is unchanged.
    The removed characters must be contained within the String.
    Valid values for i and len are the same as for substring. */
    String& erase(size_t pos, size_t len = npos);

    /* Insert the supplied source String before character i of this String,
    pushing the rest of the contents back, reallocating as needed.
    If i == size, the inserted string is added to the end of this String.
    This function does not create any temporary String objects.
    It either directly inserts the new data into this String's space if it is big enough,
    or allocates new space and copies in the old data with the new data inserted.
    This String retains the final allocation.
    The behavior of inserting a String into itself is not specified. */
    String& insert(size_t pos, const String& str);

    /* Replaces the portion of this string that begins at character i and spans
    len characters by new contents. */
    String& replace(size_t pos, size_t len, const String& str);

    /* These functions all find a particular string or character(s) within this String object. */
    size_t find(const String& str, size_t pos = 0);
    size_t find_first_of(const String& str, size_t pos = 0);
    size_t find_last_of(const String& str, size_t pos = npos);

    /* These concatenation operators add the rhs string data to the lhs object.
    They do not create any temporary String objects. They either directly copy the rhs data
    into the lhs space if it is big enough to hold the rhs, or allocate new space
    and copy the old lhs data into it followed by the rhs data. The lhs object retains the
    final memory allocation. If the rhs is a null byte or an empty C-string or String,
    no change is made to lhs String. */
    String& operator += (char rhs);
    String& operator += (const char* rhs);
    String& operator += (const String& rhs);

    /* Monitoring functions - not part of a normal implementation */
    /*used here for demonstration and testing purposes. */

    // Return the total number of Strings in existence
    static int get_number()
    {
        return number;
    }
    // Return total bytes allocated for all Strings in existence
    static int get_total_allocation()
    {
        return total_allocation;
    }
    // Call with true to cause ctor, assignment, and dtor messages to be output.
    // These messages are output from each function before it does anything else.
    static void set_messages_wanted(bool messages_wanted_)
    {
        messages_wanted = messages_wanted_;
    }

    static size_t npos;         // our own npos.
    static char a_null_byte;    // to hold a null byte for empty string representation

private:
    /* Variables for monitoring functions - not part of a normal implementation. */
    /* But used here for demonstration and testing purposes. */
    static int number;                // counts number of String objects in existence
    static int total_allocation;    // counts total amount of memory allocated
    static bool messages_wanted;    // whether to output constructor/destructor/operator= messages, initially false

    // helper for modifiers; call grow_allocation for the requested amount if need be.
    void check_allocation(int amount) {
        if (allocation < amount) {
            grow_allocation(amount);
        }
    }

    // grow the capacity of this cstr by amount.
    void grow_allocation(int amount) {
        total_allocation += (2 * amount) - allocation;
        allocation = 2 * amount;
        char* doubled_alloc = new char[(size_t)allocation];
        strcpy(doubled_alloc, cstr);
        if (cstr && *cstr != a_null_byte) {
            delete[] cstr;
            cstr = nullptr;
        }
        std::swap(doubled_alloc, cstr);
    }

    // allocates a C-string, constructed on the range from begin to end of C-string str.
    char* allocate_string(const char* str, size_t begin, size_t len) const {
        char* alloc_str = new char[len + 1];
        strncpy(alloc_str, str + begin, len);
        alloc_str[len] = a_null_byte;
        return alloc_str;
    }

    char* cstr;
    size_t sz;
    int allocation;

};

using std::max;
using std::min;

// global members
char String::a_null_byte = '\0';
int String::number = 0;
int String::total_allocation = 0;
bool String::messages_wanted = false;
size_t String::npos = std::numeric_limits<size_t>::max();

// Default initialization is to contain an empty string with no allocation.
// If a non-empty C-string is supplied, this String gets minimum allocation.
String::String(const char* cstr_)
    : cstr(&a_null_byte), sz(0), allocation(0) {
    if (cstr_ && *cstr_ != a_null_byte) {
        cstr = allocate_string(cstr_, 0, strlen(cstr_));
        sz = strlen(cstr);
        allocation = int(sz + 1);
        total_allocation += allocation;
    }
    ++number;
}

// The copy constructor initializes this String with the original's data,
// and gets minimum allocation.
String::String(const String& original)
    : cstr(allocate_string(original.cstr, 0, original.sz)), sz(original.sz), allocation(int(original.sz + 1)) {
    if (!original.sz) {
        allocation = 0;
    }
    total_allocation += allocation;
    ++number;
}

// Move constructor - take original's data, and set the original String
// member variables to the empty state (do not initialize "this" String and swap).
String::String(String&& original) noexcept
    : cstr(original.cstr), sz(original.sz), allocation(original.allocation) {
    original.cstr = &a_null_byte;
    original.sz = 0;
    original.allocation = 0;
    ++number;
}

// Destructor - deallocate C-string memory
String::~String() noexcept {
    if (allocation) {
        delete[] cstr;
        cstr = nullptr;
    }
    total_allocation -= allocation;
    sz = 0;
    allocation = 0;
    --number;
}

// Move assignment - simply swaps the contents of rhs without any copying
String& String::operator= (String&& rhs) noexcept {
    swap(rhs);
    return *this;
}

// Swap - swap the content of a String with another String
void String::swap(String& other) noexcept {
    std::swap(cstr, other.cstr);
    std::swap(sz, other.sz);
    std::swap(allocation, other.allocation);
}

// String Assignment Operator (operator=) for String Objects
// The left-hand side gets a copy of rhs data. The copy-swap method is used (as mentioned in lecture).
String& String::operator= (const String& rhs) {
    // Creates a temporary String object that stores the contents of rhs.
    String temp(rhs);
    // Swap the value of this temporary String with the String that is being assigned to (or the current String).
    swap(temp);
    // Return a reference to newly assigned string (the old value is swapped into temp, which goes out of scope).
    return *this;
}

// String Assignment Operator (operator=) for C-strings
// This operator creates a temporary String object from the rhs C-string and swaps the
// contents. The copy-swap method is used (as mentioned in lecture).
String& String::operator= (const char* rhs) {
    // The same process is used here - create a temp String with the new value, swap it with the old value,
    // and let the old value go out of scope after returning the new value.
    String temp(rhs);
    swap(temp);
    return *this;
}

// Subscript Operator (operator[]) for String Objects
// Given an index i, this operation returns a reference to character i in the string.
char& String::operator[] (size_t i) {
    // If the index is larger than the string's size, throw an out of range exception.
    if (i >= sz) throw String_exception("Subscript out of range");
    // Retrieve the character at index i of the cstr c-string.
    return cstr[i];
}

// Subscript Operator (operator[]) for const String Objects
// Given an index i of a const String, this operation returns a reference to character i in the string.
const char& String::operator[] (size_t i) const {
    // If the index is larger than the string's size, throw an out of range exception.
    if (i >= sz) throw String_exception("Subscript out of range");
    // Retrieve the character at index i of the cstr c-string.
    return cstr[i];
}

// c_str() for String Objects
// When c_str() is called on a String object, this operation returns a pointer to a C-string
// object that stores the current contents of the String object.
const char* String::c_str() const {
    return cstr;
}

// size() for String Objects
// When size() is called on a String object, it returns the length of the String object.
size_t String::size() const {
    return sz;
}

// front() for String Objects
// This function returns a reference to the first character of the String. You may assume that this
// function will NEVER be called on empty strings.
char& String::front() {
    return *cstr;
}

// back() for String Objects
// This function returns a reference to the last character of the String. You may assume that this
// function will NEVER be called on empty strings.
char& String::back() {
    return *(cstr + sz - 1);
}

// substr() for String Objects
// When substr() is called using two parameters, "pos" and "len", this function returns a newly
// constructed String object with its value initialized to a copy of a substring of the original
// String object, where this substring starts at the character position represented by "pos" and
// spans "len" characters, or until the end of the string, whichever comes first.
//
// This function uses the allocate_string(const char* str, int begin, int len) function
// which returns a char* object that spans a certain length starting from a given position.
// For example:
//     If char *myCstr represents a C-string with a value {'e', 'e', 'c', 's', '2', '8', '1', '\0'},
//     calling char *newCstr = allocate_string(myCstr, 2, 3) would set newCstr to {'c', 's', '2', '\0'}.
// Then a String object is created by using the constructor defined on line 203.
// allocate_string() uses dynamic memory (calling new), so delete must be called on the C-string
// You may assume that the starting position "pos" < sz, and "len" will be at least 0.
//
// The "len" parameter is optional - if not defined, the "len" is set to a value of String::npos, and the
// substring is built to the very end of the String.
String String::substr(size_t pos, size_t len) const {
    // If the position exceeds the string's size, throw an out of bounds exception.
    if (pos > sz) throw String_exception("Substring bounds invalid");
    // Allocate a string that starts at position pos and spans len characters.
    char* newCstr = allocate_string(cstr, pos, std::min(len, sz - pos));
    // Use the String constuctor to build a String object from the newCstr.
    String temp(newCstr);
    // Delete the newCstr (since allocate_string uses dynamic memory).
    delete[] newCstr;
    // Return the String object that was created.
    return temp;
}

// The clear() function has been provided for you - it clears the contents of a String object.
void String::clear() {
    String s;
    swap(s);
}

// ============================================== TODO #1 ============================================== //

// TODO #1: Implement erase() for String Objects
// When erase() is called using two parameters, "pos" and "len", this function erases the portion of the
// String object that begins at index "pos" that spans "len" characters (or until the end of the String,
// whichever comes first). If "len" is not defined, the String is erased from "pos" to the end of the String.
// A reference to the modified String object is returned.
//
// You may assume that the starting position "pos" will be valid, and "len" will be greater than 0.
//
// HINTS: Start with two pointers or indices, one that begins at the position to begin erasing, and one that
// begins at the character "len" distance away from "pos" (the first character after "pos" that won't be erased).
// Make sure to end the new string with the sentinel (null character), which can be assigned using the member
// variable "a_null_byte" (e.g. *ptr = a_null_byte). Don't forget to update the size of the string, "sz".
String& String::erase(size_t pos, size_t len) {
    // ERROR CHECKING: YOU DO NOT NEED TO WORRY ABOUT THIS FOR THIS LAB
    if (pos > sz) throw String_exception("Erase bounds invalid");
    // TODO: Implement erase() below.
    if ((len + pos >= sz) || (len > sz)) {
        *(cstr + pos) = a_null_byte;
        sz = pos;
        //std::cout << cstr << std::endl;
        return *this;
    }
    /*
    char *begin = cstr + pos;
    char *end = begin + len;
    while((*end != a_null_byte) && (*begin != a_null_byte)){
        *begin = *end;
        ++begin;
        ++end;
    }
    *begin = a_null_byte;
    *end = a_null_byte;
     */
    for(size_t i = pos; i <= sz - len; ++i){
        *(cstr + i) = *(cstr + i + len);
    }
    sz -= len;
    *(cstr + sz) = a_null_byte;
    return *this;
}

// ============================================ END TODO #1 ============================================ //

// ============================================== TODO #2 ============================================== //

// TODO #2: Implement insert() for String Objects
// When insert() is called using two parameters, "pos" and "str", this function inserts the contents of
// "str" BEFORE the character indicated by "pos".
//
// You may assume that the starting position "pos" will be valid.
//
// HINTS: recall how an array works when you try to insert an element - all other elements after the insertion
// point must be shifted. This is true here as well. First, you must shift all characters after the insertion
// point by a certain distance. Then, you would insert the contents of the new String into the slots you have
// freed up for insertion. Make sure you add '\0' to the end of the string after inserting, and "sz" is updated.
String& String::insert(size_t pos, const String& str) {
    // ERROR CHECKING: YOU DO NOT NEED TO WORRY ABOUT THIS FOR THIS LAB
    if (pos > sz) throw String_exception("Insertion point out of range");
    // Make sure there is enough space to store the new string - don't worry about this.
    check_allocation(int(sz + str.sz + 1));
    // TODO: Implement insert() below.
    //first shift the position to the right
    //char *end = cstr + sz + str.sz;
    //*end = a_null_byte;
    /* if the size is the insert position
    if(pos == sz){
        for (size_t i = 0; i < str.sz; ++i) {
            *(cstr + pos + i) = *(str.cstr + i);
        }
        sz += str.sz;
        *(cstr + sz) = a_null_byte;
        return *this;
    }
     */
    //*(cstr + + sz + str.sz) = a_null_byte;
        //std::cout << *(cstr + sz + str.sz - i) << std::endl;
    //copy the string to the right position
    
    //std::cout << "Last in insert string: " << *(str.cstr + str.sz - 1) <<  std::endl;
    //char last = *(str.cstr + str.sz - 1);
    //if the string to copy is the same, use deep copy
    if(str.cstr == cstr){
        String new_one = str;
        for (size_t i = 0; i <= sz - pos; ++i) {
            *(cstr + sz + str.sz - i) = *(cstr + sz - i);
        }
        for (size_t i = 0; i < new_one.sz; ++i) {
            //std::cout << "Insert string size: " << str.sz << std::endl;
            //std::cout << "Last in insert string: " << *(str.cstr + str.sz - 1) <<  std::endl;
            //std::cout << "First in insert string: " << *(str.cstr + 1) <<  std::endl;
            *(cstr + pos + i) = *(new_one.cstr + i);
            //std::cout << *(str.cstr + i) << std::endl;
            //std::cout << *(cstr + pos + i) << std::endl;
        }
        sz += str.sz;
        //*(cstr + sz - 1) = last;
        return *this;
    }
    
    for (size_t i = 0; i <= sz - pos; ++i) {
        *(cstr + sz + str.sz - i) = *(cstr + sz - i);
    }
    for (size_t i = 0; i < str.sz; ++i) {
        //std::cout << "Insert string size: " << str.sz << std::endl;
        //std::cout << "Last in insert string: " << *(str.cstr + str.sz - 1) <<  std::endl;
        //std::cout << "First in insert string: " << *(str.cstr + 1) <<  std::endl;
        *(cstr + pos + i) = *(str.cstr + i);
        //std::cout << *(str.cstr + i) << std::endl;
        //std::cout << *(cstr + pos + i) << std::endl;
    }
    sz += str.sz;
    //*(cstr + sz - 1) = last;
    return *this;
}

// ============================================ END TODO #2 ============================================ //

// ============================================== TODO #3 ============================================== //

// TODO #3: Implement replace() for String Objects
// When replace() is called using three parameters, "pos", "len", and "str", this function replaces the
// portion of the String that begins at character "pos" and spans "len" characters with the contents of
// another String object, "str".
//
// You may assume that the starting position "pos" will be valid, and "len" will be greater than 0.
// If the value of "len" exceeds the end of the String object, replace as many characters as possible.
// A value of String::npos indicates that all characters to the end of the String should be replaced.
//
// HINT: You may make use other functions in this library to write a short solution.
String& String::replace(size_t pos, size_t len, const String& str) {
    // ERROR CHECKING: YOU DO NOT NEED TO WORRY ABOUT THIS FOR THIS LAB
    if (pos > sz) throw String_exception("Replace bounds invalid");
    // Make sure there is enough space to store the new string - don't worry about this.
    if ((pos + len) > sz) len = sz - pos;
    if (len < str.sz) check_allocation(int(sz - len + str.sz + 1));
    // TODO: Implement replace() below.
    if (str.cstr == cstr) {
        String new_copy = str;
        erase(pos, len);
        insert(pos, new_copy);
        return *this;
    }
    erase(pos, len);
    insert(pos, str);
    return *this;
}

// ============================================ END TODO #3 ============================================ //

// find() for String Objects
// When find() is called using two parameters, "str" and "pos", this function searches for the first
// occurrence of "str" starting at position "pos" of the String. Characters before position "pos" are
// ignored. The entire sequence of characters of "str" must match for find() to be successful. If such
// a sequence is found, find() returns a size_t that represents the position of the first character of
// the first match. If "pos" is not specified, the search begins at position 0.
//
// If find() fails to find "str" in the String, the function returns npos. If "pos" exceeds the length
// of the string, the function will never find a match.
size_t String::find(const String& str, size_t pos) {
    if (pos + str.sz > sz) {
        return npos;
    }
    else {
        // loop through the string
        for (size_t i = pos; i <= sz - str.sz; ++i) {
            // if str matches a substring of cstr, return the index of the match
            if (strncmp(cstr + i, str.cstr, str.sz) == 0) {
                return i;
            }
        }
        // otherwise, str was not found, so return npos
        return npos;
    }
}

// ============================================== TODO #4 ============================================== //

// TODO #4: Implement find_first_of() for String Objects
// When find_first_of() is called using two parameters, "str" and "pos", this function searches the
// String for the first character that matches ANY of the characters in "str", starting at position
// "pos" of the String. Characters before position "pos" are ignored. It is enough for one single
// character of the sequence to match for the search to be successful. If a match is found, the
// function returns a size_t that represents the position of the first character that matches.
// Otherwise, the function returns npos. If "pos" exceeds the length of the string, the function
// will never find a match. If "pos" is not specified, the value of "pos" is assumed to be 0.
//
// HINTS: This is similar to the find() operation, but you will only need ONE character match for
// a search to succeed (and not the entire String "str") - a double for loop is okay here.
size_t String::find_first_of(const String& str, size_t pos) {
    // TODO: Implement find_first_of() below.
    if(pos > sz) return npos;
    for (char *start = cstr + pos; start < cstr + sz; ++start) {
        for (char *check_start = str.cstr; check_start < str.cstr + str.sz; ++check_start) {
            if (*check_start == *start) {
                return size_t(start - cstr);
            }
        }
    }
    return npos; // GET RID OF THIS LINE WHEN YOU BEGIN IMPLEMENTING FIND_FIRST_OF (this is for compile purposes only)
}

// ============================================ END TODO #4 ============================================ //

// ============================================== TODO #5 ============================================== //

// TODO #5: Implement find_last_of() for String Objects
// When find_last_of() is called using two parameters, "str" and "pos", this function searches the
// String for the last character that matches ANY of the characters in "str", starting at position
// "pos" of the String (and moving toward 0). Characters after position "pos" are ignored. It is
// enough for one single character of the sequence to match for the search to be successful. If a
// match is found, the function returns a size_t that represents the position of the last character
// that matches. Otherwise, the function returns npos. If "pos" exceeds the length of the string,
// the entire String is searched.
//
// HINTS: This is similar to the find_first_of function. Make sure you consider the case where "pos"
// is larger than the size ("sz") of the String.
size_t String::find_last_of(const String& str, size_t pos) {
    // TODO: Implement find_last_of() below.
    if (pos > sz) {
        pos = sz;
    }
    for(char *end = cstr + pos; end >= cstr; --end){
        for (char *check_end = str.cstr; check_end < str.cstr + str.sz; ++check_end) {
            if(*check_end == *end) return size_t(end - cstr);
        }
    }
    return npos;
}

// ============================================ END TODO #5 ============================================ //

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ YOU MAY IGNORE EVERYTHING BELOW THIS LINE ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// Addition Assignment Operator (operator+=) for Chars
// This function appends a character "rhs" to a String and returns a reference to the modified String.
String& String::operator += (char rhs) {
    // Make sure there is enough space to store the new string - don't worry about this.
    check_allocation(int(sz + 1 + 1));
    cstr[sz] = rhs;
    cstr[++sz] = a_null_byte;
    return *this;
}

// Operator+= for String Objects - used to append a C-string
String& String::operator += (const char* rhs) {
   if (rhs && *rhs != a_null_byte) {
      char* temp = allocate_string(rhs, 0, sz + 1);
      bool self_assignment = false;
      if (cstr == rhs) self_assignment = true;
      check_allocation(int(sz + 1 + strlen(rhs)));
      if (self_assignment) {
         auto old_size = sz;
         for (size_t i = 0; i < old_size; ++i) {
             operator+=(*(temp + i));
         }
      } else {
         while (*rhs) {
             operator+=(*rhs++);
         }
      }
      delete[] temp;
   }
   return *this;
}

// Operator+= for String Objects - used to append another String object
String& String::operator += (const String& rhs) {
    if (rhs.size() > 0) {
        operator+=(rhs.c_str());
    }
    return *this;
}

// Compare lhs and rhs strings; constructor will convert a C-string literal to a String.
// Comparison is based on std::strcmp result compared to 0
bool operator== (const String& lhs, const String& rhs) {
    return !strcmp(lhs.c_str(), rhs.c_str());
}

bool operator!= (const String& lhs, const String& rhs) {
    return strcmp(lhs.c_str(), rhs.c_str());
}

bool operator< (const String& lhs, const String& rhs) {
    return strcmp(lhs.c_str(), rhs.c_str()) < 0;
}

bool operator> (const String& lhs, const String& rhs) {
    return strcmp(lhs.c_str(), rhs.c_str()) > 0;
}

/* Concatenate a String with another String.
If one of the arguments is a C-string, the String constructor will automatically create
a temporary String for it to match this function (inefficient, but instructive).
This automatic behavior would be disabled if the String constructor was declared "explicit".
This function constructs a copy of the lhs in a local String variable,
then concatenates the rhs to it with operator +=, and returns it. */
String operator+ (const String& lhs, const String& rhs) {
    String temp(lhs);
    temp += rhs;
    return temp;
}

#endif /* STRING_H */

