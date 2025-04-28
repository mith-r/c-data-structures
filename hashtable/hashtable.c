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

 typedef struct hashtable {
    set_t **slots;
    int num_slots;
 } hashtable_t;

hashtable_t* hashtable_new(const int num_slots)
{
    if (num_slots <= 0) {
        return NULL;
    }

    hashtable_t *hashtable = mem_malloc(sizeof(hashtable_t));

    if (hashtable == NULL) {
        return NULL;
    }

    hashtable->slots = calloc(num_slots, sizeof(set_t*));
    hashtable->num_slots = num_slots;

    for (int i = 0; i < num_slots; i++) {
        hashtable->slots[i] = set_new();
    }

    if (hashtable->slots == NULL) {
        mem_free(hashtable);
        return NULL;
    }

    return hashtable;
}

bool hashtable_insert(hashtable_t* ht, const char* key, void* item)
{
    if (ht == NULL || key == NULL || item == NULL) {
        return false;
    }

    int slot = hash_jenkins(key, ht->num_slots);
    return set_insert(ht->slots[slot], key, item);
}

void* hashtable_find(hashtable_t* ht, const char* key)
{
    if (ht == NULL || key == NULL) {
        return NULL;
    }

    int slot = hash_jenkins(key, ht->num_slots);
    return set_find(ht->slots[slot],key);
}

void hashtable_print(hashtable_t* ht, FILE* fp, 
    void (*itemprint)(FILE* fp, const char* key, void* item))
{
    if (fp != NULL) {
        if (ht != NULL) {
            for (int i = 0; i < ht->num_slots; i++) {
                fprintf(fp, "Slot %d:", i);
                set_print(ht->slots[i], fp, (*itemprint));
                fprintf(fp, "\n");
            }
        } else {
            fputs("(null)", fp);
        }
    }
}

void hashtable_iterate(hashtable_t* ht, void* arg,
    void (*itemfunc)(void* arg, const char* key, void* item))
{
    if (ht == NULL || itemfunc == NULL){
        return; 
    }

    for (int i = 0; i < ht->num_slots; i++) {
        set_iterate(ht->slots[i], arg, (*itemfunc));
    }
}

void hashtable_delete(hashtable_t* ht, void (*itemdelete)(void*item))
{
    if (ht != NULL) {
        for (int i = 0; i <ht->num_slots; i++) {
            set_delete(ht->slots[i], (*itemdelete));
        }

        mem_free (ht->slots);
        mem_free (ht);
    }
}
