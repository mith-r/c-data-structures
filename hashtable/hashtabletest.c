/* 
 * hashtabletest.c - unit test for CS50 hashtable module
 *
 * Tests hashtable_new, hashtable_insert, hashtable_find, hashtable_print, hashtable_iterate, hashtable_delete
 *
 * Mithun Rameshkumar, CS50, April 2025
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <stdbool.h>
 #include "hashtable.h"
 
 /* Helper functions */
 static void itemprint(FILE* fp, const char* key, void* item);
 static void itemcount(void* arg, const char* key, void* item);
 static void itemdelete(void* item);
 
 int main(void)
 {  
     //Testing hashtable_new
     printf("Testing hashtable_new...\n");
     hashtable_t* ht = hashtable_new(10);  // 10 slots
     if (ht == NULL) {
         fprintf(stderr, "hashtable_new failed\n");
         return 1;
     }
 
     char* key1 = "Dartmouth";
     char* key2 = "Hanover";
     int* val1 = malloc(sizeof(int));
     int* val2 = malloc(sizeof(int));
     *val1 = 1;
     *val2 = 2;
     
     //Testing hashtable_insert with NULL parameters
     printf("\nTesting hashtable_insert with NULL parameters...\n");
     if (hashtable_insert(NULL, key1, val1) != false) printf("Error: should fail inserting into NULL hashtable\n");
     if (hashtable_insert(ht, NULL, val1) != false) printf("Error: should fail inserting NULL key\n");
     if (hashtable_insert(ht, key1, NULL) != false) printf("Error: should fail inserting NULL item\n");
     
     //Testing normal hashtable insert
     printf("\nTesting normal hashtable_insert...\n");
     if (hashtable_insert(ht, key1, val1) != true) printf("Error: should succeed inserting key1\n");
     if (hashtable_insert(ht, key2, val2) != true) printf("Error: should succeed inserting key2\n");
     
     //Testing hashtable_find
     printf("\nTesting hashtable_find...\n");
     if (hashtable_find(ht, key1) == val1) {
         printf("Found key1 correctly.\n");
     } else {
         printf("Failed to find key1.\n");
     }
 
     if (hashtable_find(ht, key2) == val2) {
         printf("Found key2 correctly.\n");
     } else {
         printf("Failed to find key2.\n");
     }
 
     if (hashtable_find(ht, "Nonexistent") == NULL) {
         printf("Correctly did not find nonexistent key.\n");
     } else {
         printf("Error: should not have found nonexistent key.\n");
     }
     
     //Testing duplicate key insertions
     printf("\nTesting duplicate key insertion...\n");
     if (hashtable_insert(ht, key1, val2) != false) {
         printf("Error: should not allow duplicate key insert\n");
     } else {
         printf("Correctly rejected duplicate key.\n");
     }
     
     //Testing hashtable_print
     printf("\nTesting hashtable_print...\n");
     hashtable_print(ht, stdout, itemprint);
     printf("\n");
     
     //Testing hashtable_iterate (counting items)
     printf("\nTesting hashtable_iterate (counting items)...\n");
     int count = 0;
     hashtable_iterate(ht, &count, itemcount);
     printf("Counted %d items. (Should be 2)\n", count);
     
     //Testing hashtable_delete
     printf("\nTesting hashtable_delete...\n");
     hashtable_delete(ht, itemdelete);
     printf("Hashtable deleted successfully.\n");
 
     return 0;
 }
 
 /* Helper function to print one key-item pair */
 static void itemprint(FILE* fp, const char* key, void* item)
 {
     if (fp != NULL && key != NULL && item != NULL) {
         fprintf(fp, "[%s: %d]", key, *(int*)item);
     }
 }
 
 /* Helper function to count items */
 static void itemcount(void* arg, const char* key, void* item)
 {
     int* counter = arg;
     if (counter != NULL && item != NULL) {
         (*counter)++;
     }
 }
 
 /* Helper function to delete an item */
 static void itemdelete(void* item)
 {
     if (item != NULL) {
         free(item);
     }
 }