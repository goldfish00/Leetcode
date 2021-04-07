# Class

## Struct

```go
// Declare
type user struct {
	name 		string
	email 		string
	ext 		int
	privileged 	bool
}

// declare a user type variable; the member variables will be initialized to zero value of the corresponding type
var bill user
// specify the value of member variables at construction; 
// with the name of member variable, no need to follow the sequence in declaration
lisa := user{
  name: "Lisa",
  email: "lisa@email.com",
  ext: 123,
  privileged: true,
}
// or, follow the sequence
lisa := user{"Lisa", "lisa@email.com", 123, true}

// More complicated Struct
type admin struct{
  person 	user
  level		string	
}
// declare
fred := admin{
  person: user{
    name: "Lisa",
    email: "lisa@email.com",
    ext: 123,
    privileged: true,
  },
  level: "super",
}

// Define a new type based on primitive type
type Duration int64
var dur Duration
// the following statement would incur an error since the complier would take Duration as a different type from int64
dur = int64(1000)

// ways of struct
// if pointer is not used her, the value in the user will not be changed since we will be operating on its copy
func(u *user) changeEmail(email string){
  u.email = email
}
```

