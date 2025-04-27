/* 
 * set.c Mithun Rameshkumar April 24, 2025
 *
 * This file implements the CS50 set module "set.h" providing an 
 * unordered collection of unique key, item pairs
 * 
 * see set.h
 * 
 */

#include "set.h" 
#include "mem.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


/**************** local types ****************/
typedef struct setnode {
    char* key; //pointer to key for this item
    void* item; //pointer to data for this item
    struct setnode *next; //link to next node
} setnode_t;

/**************** global types ****************/
typedef struct set {
    setnode_t *head; //head of list of items in set
} set_t;

/**************** local functions ****************/

/**************** setnode_new ****************/
/* Allocate and initialize a setnode */
static setnode_t* setnode_new(char *key, void* item) 
{
    setnode_t* node = mem_malloc(sizeof(setnode_t));

    if (node == NULL) {
        // error allocating memory for node; return error
        return NULL;
    } else {
        node-> key = key;
        node-> item = item;
        node->next = NULL;
        return node;
    }
}

/**************** set_new() ****************/
/* see set.h for description */
set_t* set_new(void)
{
    set_t* set = mem_malloc(sizeof(set_t));

    if (set == NULL) {
        return NULL; //error allocating set
    } else {
        // initalize contents of set structure
        set->head = NULL;
        return set;
    }
}

/**************** set_insert() ****************/
/* see set.h for description */
bool set_insert(set_t* set, const char* key, void* item)
{
    //Checking for Null values
    if (set == NULL || key == NULL || item == NULL) {
        return false;
    } 

    //copying key cause of const qualifier
    char *keyCopy = malloc(strlen(key) + 1);
    strcpy(keyCopy, key);

    //checking for duplicates
    setnode_t *node = set->head;

    while (node) {
        if (strcmp(node->key, keyCopy) == 0) {
            mem_free(keyCopy);
            return false;
        
        }
        node = node->next;
    }

    //allocate a new node to be added to list
    setnode_t* new = setnode_new(keyCopy, item);

    //add it to the head of the list
    new->next = set->head;
    set->head = new;
    return true;
}

/**************** set_find() ****************/
/* see set.h for description */
void* set_find(set_t* set, const char* key)
{
    if (set == NULL || key == NULL) {
        return NULL;
    }

    setnode_t *node = set-> head;

    while (node) {
        if (strcmp(node->key, key) == 0) {
            return node->item;
        }
        node = node->next;
    }
    return NULL;
}

/**************** set_print() ****************/
/* see set.h for description */
void set_print(set_t* set, FILE* fp, 
    void (*itemprint)(FILE* fp, const char* key, void* item) )
{
    if (fp != NULL) {
        if (set != NULL) {
            fputc('{', fp);
            //Iterate over set
            for (setnode_t *node = set->head; node != NULL; node = node->next) {
                //print current node
                if (itemprint != NULL) { //print the node's key and item
                    (*itemprint)(fp, node->key, node->item);
                    fputc(',', fp);
                }
            }
            fputc('}', fp);
        } else {
            fputs("(null)", fp);
        }
    }
}

/**************** set_iterate() ****************/
/* see set.h for description */
void set_iterate(set_t* set, void* arg,
    void (*itemfunc)(void* arg, const char* key, void* item))
{
    if (set != NULL && itemfunc != NULL) {
        // call itemfunc with arg on each item
        for (setnode_t *node = set->head; node != NULL; node = node->next) {
            (*itemfunc)(arg, node->key, node-> item);
        }
    }
}

/**************** set_delete() ****************/
/* see set.h for description */
void set_delete(set_t* set, void (*itemdelete)(void* item) )
{
    if (set != NULL) {
        for (setnode_t* node = set->head; node != NULL;) {
            if (itemdelete != NULL) {      // if possible...
                (*itemdelete)(node->item); // delete node's item
            }
            setnode_t* next = node->next;  // remember what comes nedxt
            mem_free(node->key);           // free node's key
            mem_free(node);                // free the node
            node = next;                   // and move on to next
        }

        mem_free(set);
    }
}



