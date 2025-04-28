# Makefile for 'hashtable' module
#
# Mithun Rameshkumar, CS50, April 2025
# Adapted from Makefile for 'bag' module

OBJS = hashtabletest.o hashtable.o ../set/set.o ../lib/file.o ../lib/mem.o hash.o
LIBS =

# uncomment the following to turn on verbose memory logging
#TESTING=-DMEMTEST

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(TESTING) -I../lib -I../set
CC = gcc
MAKE = make
# for memory-leak tests
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all

hashtabletest: $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

hashtabletest.o: hashtable.h ../set/set.h ../lib/file.h
hashtable.o: hashtable.h ../set/set.h hash.o
hash.o: hash.c
../set/set.o: ../set/set.h
../lib/file.o: ../lib/file.h

.PHONY: test valgrind clean

test: hashtabletest
	./hashtabletest

valgrind: hashtabletest
	$(VALGRIND) ./hashtabletest

clean:
	rm -rf *.dSYM  # MacOS debugger info
	rm -f *~ *.o
	rm -f hashtabletest
	rm -f core