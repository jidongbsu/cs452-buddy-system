
/**
 * Implementation of a memory allocator based on the Buddy System.
 * See Knuth Art of Computer Programming, vol. 1, page 442. 
 * Each available block starts with a header that consists
 * of a tag (free/reserved), kval (size of block 2^kval), next
 * and previous pointers. Each reserved block has the tag and kval 
 * field only. All allocations are done in powers of two. All requests
 * are rounded up to the next power of two.
 * 
 * @author  TBD
 * 
 */
 
#include "buddy.h"
int initialized = FALSE;

/* the header for an available block */
struct block_header {
	short tag;
	short kval;
	struct block_header *next;
	struct block_header *prev;
};
const int RESERVED = 0;
const int FREE = 1;
const int UNUSED = -1;


/* supports memory upto 2^(MAX_KVAL-1) (or 32 GB) in size */
#define  MAX_KVAL  35

/* default memory allocation is 512MB */
const size_t DEFAULT_MAX_MEM_SIZE = 512*1024*1024;


/* A static structure stores the table of pointers to the lists in the buddy system.  */
struct pool {
	void *start; // pointer to the start of the memory pool
	int lgsize;  // log2 of size
	size_t size; // size of the pool, same as 2 ^ lgsize
	/* the table of pointers to the buddy system lists */
	struct block_header avail[MAX_KVAL];
} pool;



int buddy_init(size_t size) { 
    return TRUE;
}


void *malloc(size_t size)
{
	return NULL;
}


void *calloc(size_t nmemb, size_t size) 
{
	return NULL;
}

void *realloc(void *ptr, size_t size) 
{
	return NULL;
}


void free(void *ptr) 
{
}


void printBuddyLists()
{
}

