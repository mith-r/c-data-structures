/* 
 * settest.c - test program for CS50 set module
 *
 *
 * This program is a "unit test" for the set module.
 * It does a decent job of testing the module, but is
 * not a complete test; it should test more corner cases.
 *
 * CS50, April 2025
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <stdbool.h>
 #include "set.h"
 

int main(void) 
{
  set_t* set = NULL;

  printf("Making a new Set");
  set = set_new();

  if (set == NULL) {
    fprintf(stderr, "set_new failed for set\n");
    return 1;
  }

  char *key = "Dartmouth";
  int value = 1;

  bool nullTest = false;
  printf("\nTest with null set, good item, good key...\n");
  nullTest = set_insert(NULL, key, &value);
  printf("test with null key...\n");
  nullTest = set_insert(set, NULL, &value); 
  printf("test with null item...\n");
  nullTest = set_insert(set, key, NULL);

  printf("\nIf successful, boolean NullTest should equal 0!\n");
  printf("NullTest = %d\n", nullTest);
  
  
  printf("\nTesting normal adding and finding\n");
  set_insert(set, key, &value);

  if (set_find(set, key) == &value) {
    printf("Successfully found!\n");
  } else {
    printf("Test failed\n");
  }

  printf("\nTest duplicate addition\n");

  if (set_insert(set,key,&value) == true) {
    printf("Failed\n");
  } else {
    printf("Success!\n");
  }
}