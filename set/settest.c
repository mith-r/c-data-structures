/* 
 * settest.c  Mithun Rameshkumar CS50, April 2025
 *
 * Tests set_new, set_insert, set_find, set_print, set_iterate, set_delete
 *
 * Mithun Rameshkumar, CS50, April 2025
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <stdbool.h>
 #include "set.h"
 
 /* Helper functions */
 static void itemprint(FILE* fp, const char* key, void* item);
 static void itemcount(void* arg, const char* key, void* item);
 static void itemdelete(void* item);
 
 int main(void) 
 {
   printf("Testing set_new...\n");
   set_t* set = set_new();
   if (set == NULL) {
     fprintf(stderr, "set_new failed\n");
     return 1;
   }
 
   char* key1 = "Dartmouth";
   char* key2 = "Hanover";
   int val1 = 1;
   int val2 = 2;
 
   printf("\nTesting set_insert with NULL parameters...\n");
   if (set_insert(NULL, key1, &val1) != false) printf("Error: should fail inserting into NULL set\n");
   if (set_insert(set, NULL, &val1) != false) printf("Error: should fail inserting NULL key\n");
   if (set_insert(set, key1, NULL) != false) printf("Error: should fail inserting NULL item\n");
 
   printf("\nTesting normal set_insert...\n");
   if (set_insert(set, key1, &val1) != true) printf("Error: should succeed inserting key1\n");
   if (set_insert(set, key2, &val2) != true) printf("Error: should succeed inserting key2\n");
 
   printf("\nTesting set_find...\n");
   if (set_find(set, key1) == &val1) {
     printf("Found key1 correctly.\n");
   } else {
     printf("Failed to find key1.\n");
   }
 
   if (set_find(set, key2) == &val2) {
     printf("Found key2 correctly.\n");
   } else {
     printf("Failed to find key2.\n");
   }
 
   if (set_find(set, "Nonexistent") == NULL) {
     printf("Correctly did not find nonexistent key.\n");
   } else {
     printf("Error: should not have found nonexistent key.\n");
   }
 
   printf("\nTesting duplicate key insertion...\n");
   if (set_insert(set, key1, &val2) != false) {
     printf("Error: should not allow duplicate key insert\n");
   } else {
     printf("Correctly rejected duplicate key.\n");
   }
 
   printf("\nTesting set_print...\n");
   set_print(set, stdout, itemprint);
   printf("\n");
 
   printf("\nTesting set_iterate (counting items)...\n");
   int count = 0;
   set_iterate(set, &count, itemcount);
   printf("Counted %d items. (Should be 2)\n", count);
 
   printf("\nTesting set_delete...\n");
   set_delete(set, itemdelete);
   printf("Set deleted successfully.\n");
 
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
   // Since we didn’t dynamically allocate the ints (val1, val2), nothing to free here
 }