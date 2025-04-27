# CS50 Lab 3
## CS50 Spring 2025

### set

A `set` is an unordered collection of unique key-item pairs
The `set` starts empty, grows as the caller adds one key-item_pair at a time, and allows lookup by key.
Keys must be unique within the set.
The `set` does not allow two different items to share the same key.

### Usage

The *set* module, defined in `set.h` and implemented in `set.c`, implements a set of `char* key` to 'void* item' pairs, and exports the following functions:

```c
set_t* set_new(void);
bool set_insert(set_t* set, const char* key, void* item);
void* set_find(set_t* set, const char* key);
void set_print(set_t* set, FILE* fp, void (*itemprint)(FILE* fp, const char* key, void* item));
void set_iterate(set_t* set, void* arg, void (*itemfunc)(void* arg, const char* key, void* item));
void set_delete(set_t* set, void (*itemdelete)(void* item));
```

### Implementation

We implement this set as a linked list.
The *set* itself is represented as a `struct set` containing a pointer to the head of the list; the head pointer is NULL when the set is empty.

Each node in the list is a `struct setnode`, a type defined internally to the module.
Each setnode includes a pointer to the `char* key`, a pointer to the `void* item` and a pointer to the next setnode on the list.

To insert a new key-item pair in the set we first verify that the key does not already exist (ensuring uniqueness).
If the key is unique, we create a new setnode to hold the key and item, and insert it at the head of the list.

The set_find function searches the list for the given key and returns the item, if found.

The set_print function prints a little syntax around the list, calls the itemprint function on each key-item pair, and separates entries with commas.

The set_iterate function calls the itemfunc function on each key-item pair.

The set_delete function calls the itemdelete function on each item, and frees all setnodes and the set structure itself.

### Assumptions

No assumptions beyond those that are clear from the spec.

### Files

* `Makefile` - compilation procedure
* `set.h` - the interface
* `set.c` - the implementation
* `settest.c` - unit test driver
* `testing.out` - result of `valgrind ./settest > testing.out 2>&1`


### Compilation

To compile, simply `make'

### Testing

Tested through valgrind and found no memory leaks. Also included testing.out which shows 
everything works as intended. I have included the valgrind results in testing.out
