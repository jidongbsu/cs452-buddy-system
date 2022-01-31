#ifndef BUDDY_H_
#define BUDDY_H_

#include <stdio.h>	/* for printf() */
#include <unistd.h>	/* for sbrk() */

#define TRUE 1
#define FALSE 0

/* the header for an available block */
struct block_header {
    short tag;
    short kval;
    struct block_header *next;
    struct block_header *prev;
};

const int RESERVED = 0;
const int FREE = 1;
const int UNUSED = -1; /* useful for header nodes */

/* supports memory allocation of up to 2^(max_kval-1) in size */
const int max_kval = 29;

/* the table of pointers to the buddy system lists */
struct block_header avail[30];

/* default memory allocation is 512MB, in this program,
 * we ask 512MB from sbrk(), but we allow applications to allocate
 * at most 256MB, because we need extra space to store the header. */
const size_t DEFAULT_MAX_MEM_SIZE = 512*1024*1024;

void *base = NULL; // pointer to the start of the memory pool

/**
 * Initialize the buddy system to the default size 
 *
 * @return  TRUE if successful, FALSE otherwise.
 */
int buddy_init(void);

/**
 * Allocate dynamic memory. Rounds up the requested size to next power of two.
 * Returns a pointer that should be type casted as needed.
 * @param size  The amount of memory requested
 * @return Pointer to new block of memory of the specified size.
 */
void *buddy_malloc(size_t size);

/**
 * buddy_free() frees the memory space pointed to by ptr, which must have been returned 
 * by a previous call to buddy_malloc(), buddy_calloc() or buddy_realloc(). Otherwise, 
 * or if buddy_free(ptr) has already been called before, undefined behaviour occurs. If 
 * ptr is NULL, no operation is performed. 
 * @param ptr Pointer to memory block to be freed
 */
void buddy_free(void *ptr);

/**
 * Prints out all the lists of available blocks in the Buddy system.
 */
void printBuddyLists(void);

#endif /*BUDDY_H_*/
