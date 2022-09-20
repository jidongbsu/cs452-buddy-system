## Overview

In this assignment we will implement our own memory allocator. More specifically, we will replace malloc/free with your own memory management scheme based on the buddy system discussed in class. Note this is NOT a kernel project, and you should just develop your code on onyx, not in your virtual machine. Submissions fail to compile or run on onyx, will not be graded.

## Learning Objectives

- Understand how free memory space is managed.
- Learn the buddy memory allocation algorithm.

## Note

This README is all about implementation. The theory of how buddy system works is beyond the scope of this README. You are highly recommended to read the book chapter and watch some youtube videos demonstrating how buddy system works.

## References

Operating Systems: Three Easy Pieces: [Chapter 17: Free Space Management](https://pages.cs.wisc.edu/~remzi/OSTEP/vm-freespace.pdf)<br/>

## Starter Code

The starter code looks like this:

```console
(base) [@onyx cs452-buddy-system]$ ls
buddy.c  buddy.h  buddy-test.c  buddy-unit-test.c  Makefile  malloc-test.c  README.md  README.template
```

You will be completing the buddy.c file. You should not modify the buddy.h file.<!-- Then you will port the code over to the buddy-preload folder. The porting only involves changing some function prototypes.-->

## Specification

You are required to implement the following 4 functions.

 - int buddy\_init(void): buddy\_init() does all the initialization. buddy\_init() does not take any parameters. It returns TRUE on success, and FALSE if it is a failure. Users are expected to call this function before use buddy\_malloc(). If they do not call buddy\_init() before calling buddy\_malloc(), your buddy\_malloc() can just return NULL.
 - void\* buddy\_malloc(size\_t size): just like malloc(), your buddy\_malloc() function allocates **size** bytes and returns a pointer to the allocated memory. If the memory cannot be allocated, then your buddy\_malloc function should return NULL.
 - void buddy\_free(void \*ptr); just like free(), your buddy\_free() function frees the memory space pointed to by **ptr**, which must have been returned by a previous call to buddy\_malloc(). Your buddy\_free() should not return anything. However, if ptr is NULL, then just return.
 - void printBuddyLists(void): this function is mainly for debugging purpose. Implementing this function will save your time in developing other functions. Example output of this printBuddyLists() is displayed below:

```console
List 0: head = 0x6020c0 --> head = 0x6020c0
List 1: head = 0x6020d8 --> head = 0x6020d8
List 2: head = 0x6020f0 --> head = 0x6020f0
List 3: head = 0x602108 --> head = 0x602108
List 4: head = 0x602120 --> head = 0x602120
List 5: head = 0x602138 --> [tag=1,kval=5,addr=0x199e020] --> head = 0x602138
List 6: head = 0x602150 --> [tag=1,kval=6,addr=0x199e040] --> head = 0x602150
List 7: head = 0x602168 --> [tag=1,kval=7,addr=0x199e080] --> head = 0x602168
List 8: head = 0x602180 --> [tag=1,kval=8,addr=0x199e100] --> head = 0x602180
List 9: head = 0x602198 --> [tag=1,kval=9,addr=0x199e200] --> head = 0x602198
List 10: head = 0x6021b0 --> [tag=1,kval=10,addr=0x199e400] --> head = 0x6021b0
List 11: head = 0x6021c8 --> [tag=1,kval=11,addr=0x199e800] --> head = 0x6021c8
List 12: head = 0x6021e0 --> [tag=1,kval=12,addr=0x199f000] --> head = 0x6021e0
List 13: head = 0x6021f8 --> [tag=1,kval=13,addr=0x19a0000] --> head = 0x6021f8
List 14: head = 0x602210 --> [tag=1,kval=14,addr=0x19a2000] --> head = 0x602210
List 15: head = 0x602228 --> [tag=1,kval=15,addr=0x19a6000] --> head = 0x602228
List 16: head = 0x602240 --> [tag=1,kval=16,addr=0x19ae000] --> head = 0x602240
List 17: head = 0x602258 --> [tag=1,kval=17,addr=0x19be000] --> head = 0x602258
List 18: head = 0x602270 --> [tag=1,kval=18,addr=0x19de000] --> head = 0x602270
List 19: head = 0x602288 --> [tag=1,kval=19,addr=0x1a1e000] --> head = 0x602288
List 20: head = 0x6022a0 --> [tag=1,kval=20,addr=0x1a9e000] --> head = 0x6022a0
List 21: head = 0x6022b8 --> [tag=1,kval=21,addr=0x1b9e000] --> head = 0x6022b8
List 22: head = 0x6022d0 --> [tag=1,kval=22,addr=0x1d9e000] --> head = 0x6022d0
List 23: head = 0x6022e8 --> [tag=1,kval=23,addr=0x219e000] --> head = 0x6022e8
List 24: head = 0x602300 --> [tag=1,kval=24,addr=0x299e000] --> head = 0x602300
List 25: head = 0x602318 --> [tag=1,kval=25,addr=0x399e000] --> head = 0x602318
List 26: head = 0x602330 --> [tag=1,kval=26,addr=0x599e000] --> head = 0x602330
List 27: head = 0x602348 --> [tag=1,kval=27,addr=0x999e000] --> head = 0x602348
List 28: head = 0x602360 --> [tag=1,kval=28,addr=0x1199e000] --> head = 0x602360
List 29: head = 0x602378 --> head = 0x602378

 Number of available blocks = 24

```

The meaning of these lists will be explained shortly in this next section.

## Global Data Structures and Variables

The starter code defines the following global data structures and variables, in buddy.h. Once again, do not modify buddy.h.

- *struct block_header avail[30]*; this is a global array which has 30 elements: avail[0] to avail[29]. Each element represents the head of a list. In theory you can implement this list in many different ways, in this assignment you are highly recommended to implement it as a circular doubly linked list. In total, you will have 30 such lists: List 0 to List 29 - the above printBuddyLists() prints these lists. All 30 lists should be initialized in your buddy\_init() function.

- *struct block_header*. This is the basic data structure which represents the header of one memory block.

```c
/* the header for an available block */
struct block_header {
    short tag;
    short kval;
    struct block_header *next;
    struct block_header *prev;
};
```

The above 30 lists do not connect memory blocks, rather, they connect headers - headers representing the head of memory blocks. Reading the book chapter will help you understand the meaning of headers and why we need headers, but the textbook chapter does not describe how exactly we can implement the buddy system. In our implementation, we define 30 circular doubly linked lists: list 0 connects block headers, and each header represents a memory block whose size is 2^0=1 byte, and we say its **kval** is 0; list 1 connects block headers, and each header represents a memory block whose size is 2^1=2 byte, and we say its **kval** is 1; list 2 connects block headers, and each header represents a memory block whose size is 2^2=4 bytes, and we say its **kval** is 2; ...; list 29 connects block headers, and each header represents a memory block whose size is 2^29=512MB, and we say its **kval** is 29.

In your printBuddyLists(), you should try to print out all your 30 lists. The *addr* in the example output of the above printBuddyLists(), means the address of each node.

- In *struct block_header*, there is a field called *tag*. We use this tag to represent the status of memory block. 3 tags are defined:

```c
const int RESERVED = 0;
const int FREE = 1;
const int UNUSED = -1; /* useful for header nodes */
```

The head of each of the 30 lists, is a dummy node, which does not represent any memory block, but is only used to represent the beginning of this list. Thus we use the tag UNUSED to represent such nodes. For all the other nodes on each of the 30 lists, we use the FREE tag: we use the lists to manage free space, that is why this book chapter is called "Free Space Management". We do not keep a node on any of the 30 lists, if the memory block it represents is allocated - and for those nodes, we use the tag RESERVED.

- *const int max_kval*; *max_kval* represents the largest index of the above array, which is initialized as 29, and should not be changed.

- *const size_t DEFAULT_MAX_MEM_SIZE*; this macro denotes the largest memory chunk you will get from sbrk() and will be the memory chunk you are going to manage. *DEFAULT_MAX_MEM_SIZE* is 512MB. In your buddy\_init(), you should use sbrk() as following:

```c
base=sbrk(DEFAULT_MAX_MEM_SIZE);
```

- *void* \**base*; *base* is a void type pointer which points to the starting address of the above memory chunk. In buddy.h, we initialized *base* as NULL, but once you use the above sbrk() line, *base* will be pointing to the starting address of the allocated 512MB memory chunk.

## APIs, Helper Code, and Formula

The only API function you will need to call in this programming assignment, is sbrk(), which is a library function which calls a system call function named brk()/sys\_brk() to allocate memory from the kernel. Once sbrk() returns the memory you need, you just manage the memory, and do not need to call sbrk() again.

In addition, at some point, you will need to calculate the ceiling log base 2 of an integer, for that, you are recommended to use the following code:

```c
    size=size-1;
    while(size>0){
        size=size>>1;
        lgsize++;
    }
```

Given an integer *size*, the above code stores the ceiling log base 2 of *size* in *lgsize* - make sure your *lgsize* is initialized to be 0.

As the chapter says: **The reason buddy allocation works so well is that it is simple to determine the buddy of a particular block. How, you ask? Think about the addresses of the blocks in the free space above. If you think carefully enough, you’ll see that the address of each buddy pair only differs by a single bit; which bit is determined by the level in the buddy tree.** It's true, there is only one single bit of difference between a memory block's **relative** address and its buddy's **relative** address. Thus in your code, you can use the following formula to compute your buddy's (**relative**) memory address.

```c
your_buddy_address = your_address^(1ULL<<lgsize));
```

This formula basically uses the bit-wise XOR operation to flip one single bit of your address, so as to get your buddy's address. Note, we are talking about relative addresses only; not absolute addresses. If your buddy calculation is correct, you should see that the distance between your address and your buddy's address is a power of 2, and you can use the following 4 lines to show the distance between two pointers *p* and *p2* - assuming *p* is larger than *p2*:

```c
#include <stddef.h> /* for ptrdiff_t */
ptrdiff_t distance_bytes;
distance_bytes=(char *)p-(char *)p2;				
printf("when splitting, the distance between p2 and its buddy (buddy on the right) is %td\n", distance_bytes);
```

Some sample output is like this:

```console
when splitting, the distance between p2 and its buddy (buddy on the right) is 268435456
when splitting, the distance between p2 and its buddy (buddy on the right) is 134217728
when splitting, the distance between p2 and its buddy (buddy on the right) is 67108864
when splitting, the distance between p2 and its buddy (buddy on the right) is 33554432
when splitting, the distance between p2 and its buddy (buddy on the right) is 16777216
when splitting, the distance between p2 and its buddy (buddy on the right) is 8388608
when splitting, the distance between p2 and its buddy (buddy on the right) is 4194304
when splitting, the distance between p2 and its buddy (buddy on the right) is 2097152
when splitting, the distance between p2 and its buddy (buddy on the right) is 1048576
when splitting, the distance between p2 and its buddy (buddy on the right) is 524288
when splitting, the distance between p2 and its buddy (buddy on the right) is 262144
when splitting, the distance between p2 and its buddy (buddy on the right) is 131072
when splitting, the distance between p2 and its buddy (buddy on the right) is 65536
when splitting, the distance between p2 and its buddy (buddy on the right) is 32768
when splitting, the distance between p2 and its buddy (buddy on the right) is 16384
when splitting, the distance between p2 and its buddy (buddy on the right) is 8192
when splitting, the distance between p2 and its buddy (buddy on the right) is 4096
when splitting, the distance between p2 and its buddy (buddy on the right) is 2048
when splitting, the distance between p2 and its buddy (buddy on the right) is 1024
when splitting, the distance between p2 and its buddy (buddy on the right) is 512
when splitting, the distance between p2 and its buddy (buddy on the right) is 256
when splitting, the distance between p2 and its buddy (buddy on the right) is 128
when splitting, the distance between p2 and its buddy (buddy on the right) is 64
when splitting, the distance between p2 and its buddy (buddy on the right) is 32
```

## Testing

Two performance test files are provided: buddy-test.c and malloc-test.c. They run identical tests using the two different allocators - your allocator and the default malloc allocator. You should not modify these two files! In addition, there is a unit test file buddy-unit-test.c, to which you are recommended to add more tests.

This is how you should run the buddy-unit-test program:

```console
(base) [@onyx ]$ ./buddy-unit-test s
(base) [@onyx ]$ ./buddy-unit-test v
```

*s* stands for silent, *v* stands for verbose. Thus *v* shows you more debugging information.

This is how you should run the buddy-test or malloc-test program:

```console
(base) [@onyx ]$ ./buddy-test 100 1234 s
(base) [@onyx ]$ ./buddy-test 100 1234 v
(base) [@onyx ]$ ./malloc-test 100 1234 s
(base) [@onyx ]$ ./malloc-test 100 1234 v
```

Once again, *s* stands for silent, *v* stands for verbose. *1234* is a random seed, you can use any number for the random seed. 100 means you want to run 100 iterations, each iteration will try to allocate or free some random memory blocks from your buddy memory allocator. Thus, a large number of iterations will test your buddy system more thoroughly. That is why the grading rubric says, we expect to run buddy-test against your buddy system with at least 10M iterations without crashing.

### Buddy System Performance

Test your buddy system implementation against malloc and make sure that it outperforms it. For the purposes of measuring performance, use the buddy-test.c and malloc-test.c code provided in the sample code for this project. Here is performance comparison for the reference solution (tested on onyx, compiled with -O2 optimizer flag)

```console
[user@onyx ]$ time buddy-test 20000000 1234 s
real    0m1.348s
user    0m1.345s
sys     0m0.002s

[user@onyx ]$ time malloc-test 20000000 1234 s      
real    0m2.090s
user    0m2.088s
sys     0m0.001s
```

## Submission

Due Date:  09/22/2022, 23:59pm. Late submission will not be accepted/graded.

## Project Layout

All files necessary for compilation need to be submitted, this includes source code files, header files, and Makefile. The structure of the submission folder should be the same as what was given to you. Make sure to not modify the two test programs buddy-test.c and malloc-test.c, and not to modify buddy.h.

## Grading Rubric (for Undergraduate Students and Graduate Students)

Grade:  /100

- [10 pts] Compiling:
	- Each compiler warning will result in a 3 point deduction.
	- You are not allowed to suppress warnings.
- [80 pts] Functional Requirements:
	- Malloc and free 1 byte works (this will be reported by buddy-unit-test) (40):
	- Allocation beyond maximum fails gracefully (this will be reported by buddy-unit-test) (10):
	- Stability test - run buddy-test with at least 10M iterations without crashing (this will be reported by buddy-test) (25):
	- Performance - your buddy system outperforms the default malloc/free (this will be reported by buddy-test and malloc-test) (5):
- [10 pts] Documentation:
	- README.md file (rename this current README file to README.orig and rename the README.template to README.md)
	- You are required to fill in every section of the README template, missing 1 section will result in a 2-point deduction.
