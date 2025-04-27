/*
 * counterstest.c   Mithun Rameshkumar  CS50, April 2025
 *
 * Tests counters_new, counters_add, counters_get, counters_set,
 * counters_print, counters_iterate, counters_delete
 *
 * Mithun Rameshkumar, CS50, April 2025
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <stdbool.h>
 #include "counters.h"
 
 /* Helper functions */
 static void itemcount(void* arg, const int key, const int count);
 
 int main(void)
 {
     printf("Testing counters_new...\n");
     counters_t* ctrs = counters_new();
     if (ctrs == NULL) {
         fprintf(stderr, "counters_new failed\n");
         return 1;
     }
 
     printf("\nTesting counters_add with NULL parameters...\n");
     if (counters_add(NULL, 5) != 0) printf("Error: should fail adding to NULL counters\n");
     if (counters_add(ctrs, -1) != 0) printf("Error: should fail adding negative key\n");
 
     printf("\nTesting normal counters_add...\n");
     if (counters_add(ctrs, 1) != 1) printf("Error: should insert key 1 with count 1\n");
     if (counters_add(ctrs, 2) != 1) printf("Error: should insert key 2 with count 1\n");
     if (counters_add(ctrs, 1) != 2) printf("Error: key 1 should increment to 2\n");
 
     printf("\nTesting counters_get...\n");
     if (counters_get(ctrs, 1) == 2) {
         printf("Found correct count for key 1.\n");
     } else {
         printf("Failed finding correct count for key 1.\n");
     }
 
     if (counters_get(ctrs, 2) == 1) {
         printf("Found correct count for key 2.\n");
     } else {
         printf("Failed finding correct count for key 2.\n");
     }
 
     if (counters_get(ctrs, 999) == 0) {
         printf("Correctly returned 0 for nonexistent key.\n");
     } else {
         printf("Error: nonexistent key should return 0.\n");
     }
 
     printf("\nTesting counters_set...\n");
     if (!counters_set(ctrs, 1, 10)) {
         printf("Error: should set key 1 to 10\n");
     } else if (counters_get(ctrs, 1) != 10) {
         printf("Error: key 1 should now be 10\n");
     } else {
         printf("Key 1 successfully set to 10.\n");
     }
 
     if (!counters_set(ctrs, 5, 7)) {
         printf("Error: should set new key 5 to 7\n");
     } else if (counters_get(ctrs, 5) != 7) {
         printf("Error: key 5 should now be 7\n");
     } else {
         printf("Key 5 successfully set to 7.\n");
     }
 
     printf("\nTesting counters_print...\n");
     counters_print(ctrs, stdout);
     printf("\n");
 
     printf("\nTesting counters_iterate (counting items)...\n");
     int total = 0;
     counters_iterate(ctrs, &total, itemcount);
     printf("Counted %d keys.\n", total);
 
     printf("\nTesting counters_delete...\n");
     counters_delete(ctrs);
     printf("Counters deleted successfully.\n");
 
     return 0;
 }
 
 /* Helper function to count items */
 static void itemcount(void* arg, const int key, const int count)
 {
     int* counter = arg;
     if (counter != NULL) {
         (*counter)++;
     }
 }