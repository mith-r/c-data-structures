/*
 * hashtable.c Mithun Rameshkumar April 2025
 *
 *  This file implements the CS50 hashtable module "hashtable.h"
 * A *hashtable* is a set of (key,item) pairs. It acts just like a 
 * set but is far more efficient for large collections.
 * 
 * See hashtable.h for more info
 */

 #include <stdio.h>
 #include <stdbool.h>
 #include "hashtable.h"
 #include "hash.h"
 #include "mem.h"
 #include "hashtable.h"
 #include "set.h"

 /**************** global types ****************/
 typedef struct hashtable {
    set_t **slots; //
    int num_slots;
 } hashtable_t;

 /**************** local functions ****************/
 /**************** hashtable_new() ****************/
/* see hashtable.h for description */
hashtable_t* hashtable_new(const int num_slots)
{   
    //Checking to make sure num_slots is valid number
    if (num_slots <= 0) {
        return NULL;
    }

    //initalize memory for hashtable
    hashtable_t *hashtable = mem_malloc(sizeof(hashtable_t));

    //Make sure no error
    if (hashtable == NULL) {
        return NULL;
    }

    //Scale size of hashtable according to num_slots
    hashtable->slots = calloc(num_slots, sizeof(set_t*));
    hashtable->num_slots = num_slots;

    for (int i = 0; i < num_slots; i++) {
        hashtable->slots[i] = set_new();
    }
    
    //If error free memory and return NULL
    if (hashtable->slots == NULL) {
        mem_free(hashtable);
        return NULL;
    }

    return hashtable;
}

/**************** hashtable_insert() ****************/
/* see hashtable.h for description */
bool hashtable_insert(hashtable_t* ht, const char* key, void* item)
{
    //Checking for Null values
    if (ht == NULL || key == NULL || item == NULL) {
        return false;
    }

    //Calculating hash number and inserting into set
    int slot = hash_jenkins(key, ht->num_slots);
    return set_insert(ht->slots[slot], key, item);
}


/**************** hashtable_find() ****************/
/* see hashtable.h for description */
void* hashtable_find(hashtable_t* ht, const char* key)
{
    //Null checks
    if (ht == NULL || key == NULL) {
        return NULL;
    }

    //Calculate proper hash number and return item
    int slot = hash_jenkins(key, ht->num_slots);
    return set_find(ht->slots[slot],key);
}

/**************** hashtable_print() ****************/
/* see hashtable.h for description */
void hashtable_print(hashtable_t* ht, FILE* fp, 
    void (*itemprint)(FILE* fp, const char* key, void* item))
{
    if (fp != NULL) {
        if (ht != NULL) {
            // iterate through sets
            for (int i = 0; i < ht->num_slots; i++) {
                fprintf(fp, "Slot %d:", i);
                //iterate through sets
                set_print(ht->slots[i], fp, (*itemprint));
                fprintf(fp, "\n");
            }
        } else {
            fputs("(null)", fp);
        }
    }
}

/**************** hashtable_iterate() ****************/
/* see hashtable.h for description */
void hashtable_iterate(hashtable_t* ht, void* arg,
    void (*itemfunc)(void* arg, const char* key, void* item))
{
    //Null checks
    if (ht == NULL || itemfunc == NULL){
        return; 
    }

    //Iterate through slots and call set_iterate
    for (int i = 0; i < ht->num_slots; i++) {
        set_iterate(ht->slots[i], arg, (*itemfunc));
    }
}

/**************** hashtable_delete() ****************/
/* see hashtable.h for description */
void hashtable_delete(hashtable_t* ht, void (*itemdelete)(void*item))
{
    if (ht != NULL) {
        //iterate through slots and call set_delete
        for (int i = 0; i <ht->num_slots; i++) {
            set_delete(ht->slots[i], (*itemdelete));
        }

        //free memory
        mem_free (ht->slots); 
        mem_free (ht);
    }
}
