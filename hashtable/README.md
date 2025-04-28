# CS50 Lab 3
## CS50 Spring 2025

### hashtable

A `hashtable` is an unordered collection of unique key-item pairs, organized for efficient lookup based on key.
The `hashtable` starts empty, grows as the caller adds one key-item pair at a time, and allows fast lookup by key.
Keys must be unique within the table.
The `hashtable` does not allow two different items to share the same key.

### Usage

The *hashtable* module, defined in `hashtable.h` and implemented in `hashtable.c`, implements a mapping from `char* key` to `void* item`, and exports the following functions:

```c
hashtable_t* hashtable_new(const int num_slots);
bool hashtable_insert(hashtable_t* ht, const char* key, void* item);
void* hashtable_find(hashtable_t* ht, const char* key);
void hashtable_print(hashtable_t* ht, FILE* fp, void (*itemprint)(FILE* fp, const char* key, void* item));
void hashtable_iterate(hashtable_t* ht, void* arg, void (*itemfunc)(void* arg, const char* key, void* item));
void hashtable_delete(hashtable_t* ht, void (*itemdelete)(void* item));
```

### Implementation

We implement the hashtable as an array of pointers to sets (linked lists).
The hashtable itself is represented as a struct hashtable containing:
	•	an array of set_t* pointers (slots),
	•	and an integer number of slots.

Each slot in the array is a set, implemented internally by the set module.
Keys within each set must be unique.

When inserting, we compute the hash of the key to determine the appropriate slot.
If the slot is empty, a new set is created there.
The key-item pair is then inserted into the appropriate set.

The hashtable_find function searches the appropriate set for a given key.

The hashtable_print function prints the contents of each slot and each key-item pair using the provided itemprint function.

The hashtable_iterate function calls the given itemfunc on each key-item pair across all slots.

The hashtable_delete function deletes all sets, all nodes within each set, and finally the hashtable itself.

### Assumptions

No assumptions beyond those that are clear from the spec.

### Files

*	'Makefile' - compilation procedure
*   'hash.c' - hash function
*   'hash.h' - interface for hash function
*	'hashtable.h' - the interface
*	'hashtable.c' - the implementation
*	'hashtabletest.c' - unit test driver
*	'testing.out' - result of  `make test > testing.out`

### Compilation

To compile, simply `make'

### Testing

Tested through valgrind and found no memory leaks. Also included testing.out which shows 
everything works as intended. 