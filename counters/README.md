# CS50 Lab 3
## CS50 Spring 2025

### counters

A `counters` module is a collection of counters, each distinguished by an integer key.
Each key must be unique within the set.
The counter starts empty, grows as the caller adds keys, and allows lookup and update of counts by key.

### Usage

The *counters* module, defined in `counters.h` and implemented in `counters.c`, manages a set of integer keys and integer counts, and exports the following functions:

```c
counters_t* counters_new(void);
int counters_add(counters_t* ctrs, const int key);
int counters_get(counters_t* ctrs, const int key);
bool counters_set(counters_t* ctrs, const int key, const int count);
void counters_print(counters_t* ctrs, FILE* fp);
void counters_iterate(counters_t* ctrs, void* arg, void (*itemfunc)(void* arg, const int key, const int count));
void counters_delete(counters_t* ctrs);
```

### Implementation

We implement counters as a linked list.
The *counters* itself is represented as a `struct counters` containing a pointer to the head of the list; the head pointer is NULL when the counters is empty.

Each node in the list is a `struct countersnode`, a type defined internally to the module.
Each counternode includes an integer key, an integer count, and a pointer to the next node in the list.

The counters_add function searches the list for the given key.
If found, it increments the corresponding counter; otherwise, it creates a new node with a counter initialized to 1.

The counters_get function searches the list for a key and returns the current counter value.

The counters_set function searches the list for a key and sets its counter to a specific value. If the key does not exist, it adds a new node and sets the counter.

The counters_print function prints a comma-separated list of key-counter pairs within curly braces.

The counters_iterate function calls the itemfunc on each key-count pair in the list.

The counters_delete function frees all memory associated with the counter list and the counters structure itself.

### Assumptions

No assumptions beyond those that are clear from the spec.

### Files

* `Makefile` - compilation procedure
* `counters.h` - the interface
* `counters.c` - the implementation
* `counters.c` - unit test driver
* `testing.out` - result of `make test > testing.out`


### Compilation

To compile, simply `make'

### Testing

Tested through valgrind and found no memory leaks. Also included testing.out which shows 
everything works as intended. 
