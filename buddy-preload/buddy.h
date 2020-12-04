#ifndef BUDDY_H_
#define BUDDY_H_

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

/**
 * Allocate dynamic memory. Rounds up the requested size to next power of two.
 * Returns a pointer that should be type casted as needed.
 * @param size  The amount of memory requested
 * @return Pointer to new block of memory of the specified size.
 */
void *malloc(size_t size);


/**
 * Allocate and clear memory to all zeroes. Wrapper function that just calles buddy_malloc.
 *
 * @param nmemb  The number of members needed
 * @param size   Size of each member
 * @return Pointer to start of the array of members
 */
void *calloc(size_t nmemb, size_t size);


/**
 * Changes the size of the memory block pointed to by ptr to size bytes. 
 * The contents will be unchanged to the minimum of the old and new sizes; newly 
 * allocated memory will be uninitialized. If ptr is NULL, the call is equivalent 
 * to buddy_malloc(size); if size is equal to zero, the call is equivalent to buddy_free(ptr). 
 * Unless ptr is NULL, it must have been returned by an earlier call to buddy_malloc(), 
 * buddy_calloc() or buddy_realloc().
 *
 * @param  ptr Pointer to existing memory block
 * @param  size The new size of the memory block
 * @return The pointer to the resized block
 */
void *realloc(void *ptr, size_t size);


/**
 * Frees the memory space pointed to by ptr, which must have been returned 
 * by a previous call to buddy_malloc(), buddy_calloc() or buddy_realloc(). Otherwise, 
 * or if buddy_free(ptr) has already been called before, undefined behaviour occurs. If 
 * ptr is NULL, no operation is performed. 
 * @param ptr Pointer to memory block to be freed
 */
void free(void *ptr);


/**
 * Prints out all the lists of available blocks in the Buddy system.
 */
void printBuddyLists();

#endif /*BUDDY_H_*/
