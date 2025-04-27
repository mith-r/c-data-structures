/*
 * counters.c  Mithun Rameshkumar April 2025
 *
 *  This file implements the CS50 counters module "counters.h" providing an
 *  unordered collection of unique keys and an associated count
 * 
 *  see counters.h for more info
 */

#include <stdio.h>
#include <stdlib.h>
#include "counters.h"
#include "mem.h"

/**************** local types ****************/
typedef struct counternode {
    int key; // pointer to key for this item
    int count; //pointer to counter for this item
    struct counternode *next; //link to next node
} counternode_t;

/**************** global types ****************/
typedef struct counters {
    struct counternode *head; //head of list of items in counters
} counters_t;

/**************** local functions ****************/
/* Allocate and initialize a setnode */
static counternode_t* counternode_new(int key)
{
    counternode_t* node = mem_malloc(sizeof(counternode_t));

    if (node == NULL) {
        // error allocating memory for node; return error
        return NULL;
    } else {
        node->key = key;
        node->count = 0;
        return node;
    }
}

/**************** counters_new() ****************/
/* see counters.h for description */
counters_t* counters_new(void) 
{
    counters_t* counter = mem_malloc(sizeof(counters_t));

    if (counter == NULL){
        return NULL; //error allocating set
    } else {
        // initialize contents of set structure
        counter->head = NULL;
        return counter;
    }
}

/**************** counters_add() ****************/
/* see counters.h for description */
int counters_add(counters_t* ctrs, const int key)
{
    //Checking for Null values
    if (ctrs == NULL || key < 0){
        return 0;
    }

    //Checking to see if it already exists
    counternode_t *node = ctrs->head;

    while (node) {
        //If found increment count and return
        if (node->key == key) {
            node->count++;
            return node->count;
        }
        node = node->next;
    }

    //Allocate new node to be added to lsit
    counternode_t *new = counternode_new(key);

    //Set count to one and add to head of the list
    new->count = 1;
    new->next = ctrs->head;
    ctrs->head = new;

    //Return the new count
    return new->count;
}

/**************** counters_get() ****************/
/* see counters.h for description */
int counters_get(counters_t* ctrs, const int key)
{   
    //Null/invalid key checks
    if (ctrs == NULL || key < 0){
        return 0;
    }

    counternode_t *node = ctrs->head;

    //If found return count, if not return 0
    while (node) {
        if (node->key == key) {
            return node->count;
        }
        node = node->next;
    }

    return 0;
}

/**************** counters_set() ****************/
/* see counters.h for description */
bool counters_set(counters_t* ctrs, const int key, const int count)
{
    // NULL check and invalid key/count check
    if (ctrs == NULL || key < 0 || count < 0) {
        return false;
    }

    counternode_t *node = ctrs->head;

    //If found set count to given
    while (node) {
        if (node->key == key) {
            node->count = count;
            return true;
        }
        node = node->next;
    }

    //Else call counters_add to add key and call counters_set again
    counters_add(ctrs,key);
    return counters_set(ctrs,key,count);
}

/**************** counters_print() ****************/
/* see counters.h for description */
void counters_print(counters_t* ctrs, FILE* fp)
{
    if (fp != NULL) {
        if (ctrs != NULL) {
            fputc('{', fp);
            //Iterate over counters
            for (counternode_t* node = ctrs->head; node != NULL; node = node->next) {
                //print current node
                fprintf(fp, "%d=%d, ", node->key, node->count); //print the node's key and count
            }
            fputc('}',fp);
        } else {
            fputs("(null)",fp);
        }
    } 
}

/**************** counters_iterate() ****************/
/* see counters.h for description */
void counters_iterate(counters_t* ctrs, void* arg, 
    void (*itemfunc)(void* arg, const int key, const int count))
{
    if (ctrs != NULL && itemfunc != NULL) {
        // call itemfunc with arg on each item
        for (counternode_t* node = ctrs->head; node != NULL; node = node->next) {
            (*itemfunc)(arg, node->key, node->count);
        }
    }
}

/**************** counters_delete() ****************/
/* see counters.h for description */
void counters_delete(counters_t* ctrs)
{
    if (ctrs != NULL) {
        for (counternode_t* node = ctrs->head; node != NULL;) {
            counternode_t *next = node->next; //remember what comes next
            mem_free(node); //free then node
            node = next; // and move on to next
        }
        mem_free(ctrs);
    }
}
