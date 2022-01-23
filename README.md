## Overview

In this assignment we will implement our own memory allocator. More specifically, we will replace malloc/free with your own memory management scheme based on the Buddy system discussed in class. Note this is NOT a kernel project, and you should just develop your code on onyx, not in your virtual machine. Submissions fail to compile or run on onyx, will not be graded.

## Learning Objectives

- Understand how free memory space is managed
- Learn the buddy memory allocation algorithm

## Starter Code

You should see the project folder with all the starter code. It should look like the listing below:

```console
[user@localhost (master)]$ ls -R
.:
buddy-non-preload  buddy-preload Makefile

./buddy-non-preload:
buddy.c  buddy.h  buddy-test.c  buddy-unit-test.c  Makefile  malloc-test.c

./buddy-preload:
buddy.c  buddy.h  Makefile  malloc-test.c
```

The buddy-preload folder will NOT be used this semester, thus you can ignore it.

You will be completing the buddy.c file in the buddy-non-preload subfolder. Make sure to study the header file buddy.h for the javadocs of functions that you have to implement. Also study buddy.c for the header declaration and stubs of the functions. <!-- Then you will port the code over to the buddy-preload folder. The porting only involves changing some function prototypes.-->

## Specification

## Buddy System Memory Management

Implement your own memory manager using the Buddy Algorithm. You should use the sbrk() to initially allocate a large block of memory. A good initial amount is 512MB. From there on manage the chunk of memory returned by sbrk using your own memory management functions. You may assume that the maximum amount of memory that you will ever manage is limited to 32GB.

buddy\_init() does all the initialization, users are expected to call this function before use buddy\_malloc(). However, if the user doesn't call this buddy\_init(), then it should be transparently called whenever the user calls buddy\_malloc() for the first time. We will use the following prototypes for the buddy functions:

```c
int buddy_init(size_t);
void *buddy_malloc(size_t);
void buddy_free(void *);
```

Note that if a 0 is passed as an argument to buddy\_init, then it initializes the memory pool to be of the default size (512MB, as specified above). If the caller specifies an unreasonably small size, then the buddy system may not be able to satisfy any requests. 

If the memory cannot be allocated, then your buddy\_malloc function should set the errno to ENOMEM (which is defined in errno.h header file). 

Note that we have provided you with a buddy.h header file that contains all the declarations and prototypes. We have also provided a skeleton buddy.c that has the declaration for the pool and the table of lists for the buddy system.

## Testing

<!-- Build a test suite for your buddy system. -->
Sample test code that you can use as a starting point is in the buddy-non-preload folder. It contains two performance test files: buddy-test.c and malloc-test.c that run identical tests using the two different allocators - your allocator and the default malloc allocator. You should not modify these two files! In addition, there is a unit test file buddy-unit-test.c, to which you are recommended to add more tests.

<!-- ## Interposing malloc()

Interposing allows us to add our library in as a shim. Thus when malloc/free are called our versions are called instead of the C standard library versions. To use interposing, your buddy system allocator will need to implement the same interface as malloc (and with the same function names and signature).  We will make our buddy system into another shared library, which will be named libbuddy.so.

Use the following command to interpose for malloc using libbuddy.so:

```console
    LD_PRELOAD=./libbuddy.so ./mytests 1000000 1
```

Note that to time the interposed version, use the following command:

```console-->
<!-- time LD_PRELOAD=./libbuddy.so ./malloc-test <appropriate arguments>
```

### Integrating with your mergesort

Use the interposing version of your buddy system to integrate with your mergesort. -->

### Buddy System Performance <!--(Graduate Students only)-->

Test your buddy system implementation against malloc and make sure that it outperforms it. For the purposes of measuring performance, use the buddy-test.c and malloc-test.c code provided in the sample code for this project. Here is performance comparison for the reference solution (tested on onyx, compiled with -O2 optimizer flag)

```console
[user@onyx buddy-non-preload]$ time buddy-test 20000000 1234 s
real    0m1.348s
user    0m1.345s
sys     0m0.002s

[user@onyx buddy-non-preload]$ time malloc-test 20000000 1234 s      
real    0m2.090s
user    0m2.088s
sys     0m0.001s
```

<!-- ### Thread Safety (Graduate Students only)-->

<!-- Make your buddy system library be thread-safe. Compare its run time performance against malloc and report in your README.md file.-->

<!-- ### Integrating with your browser (Graduate Students only)-->

<!-- Now you can use preloading to test your buddy system with your browser (either chrome or firefox), keep in mind that browsers are multi-threaded programs. -->

## References

Operating Systems: Three Easy Pieces: [Chapter 14: Memory API](https://pages.cs.wisc.edu/~remzi/OSTEP/vm-api.pdf)<br/>
Operating Systems: Three Easy Pieces: [Chapter 17: Free Space Management](https://pages.cs.wisc.edu/~remzi/OSTEP/vm-freespace.pdf)<br/>
Donald Knuth. Fundamental Algorithms. The Art of Computer Programming 1 (Second ed.) pp. 435-455. Addison-Wesley.

## Submission

Due Date:  02/15/2022, 23:59pm. Late submission will not be accepted/graded.

## Project Layout

All files necessary for compilation need to be submitted, this includes source code files, header files, and Makefile. <!-- The Makefile in the top level of your submission directory for this project must build both the preloaded and non-preloaded versions and other related text programs. --> The structure of the submission folder should be the same as what was given to you. Make sure to not modify the two test programs buddy-test.c and malloc-test.c.

<!-- To test the buddy system library with the mergesort project, you can simply copy your buddy system library to your mergesort project and preload it to test it with your mergesort project. This is how we will test your project.-->

## Grading Rubric (for Undergraduate Students and Graduate Students)

Grade:  /100

- [10 pts] Compiling:
	- Each compiler warning will result in a 3 point deduction.
	- You are not allowed to suppress warnings.
- [80 pts] Functional Requirements:
	<!-- - buddy system (90 points): -->
	- Malloc and free 1 byte works (40):
	- Allocation beyond maximum fails gracefully (10):
	- Stability test - run buddy-test with at least 10M iterations without crashing (25):
	- Performance - your buddy system outperforms the default malloc/free (5):
	<!-- - mergesort integration via interposing (35 points):
		- serial mergesort works with buddy manager with interposing. -->
- [10 pts] Documentation:
	- README.md file (replace this current README.md with a new one using the README template, and do not check in this current README file.)
	- You are required to fill in every section of the README template, missing 1 section will result in a 2-point deduction.

<!-- ## Grading Rubric (for Graduate Students)

Grade:  /150

- [10 pts] Compiling:
	- Each compiler warning will result in a 3 point deduction.
	- You are not allowed to suppress warnings.
- [125 pts] Functional Requirements:
	- buddy system (70 points):
		- Malloc and free 1 byte works (40):
		- Allocation beyond maximum fails gracefully (10):
		- Stability test - run buddy-test with at least 10M iterations without crashing (10):
		- Other unit or functional tests (10):
	- mergesort integration via interposing (30 points):
		- serial mergesort works with buddy manager with interposing (10)
		- parallel mergesort works with buddy manager with interposing (20)
	- browser integration via interposing (10 points):
		- browser (either chrome or firefox) works with buddy manager with interposing (provide a screenshot please: on the left side of the screenshot, show your terminal and your command; on the right side, show your browser)
	- buddy system performance (15 points) - no partial points for this, you get the points only if you outperforms the default malloc:
- [15 pts] Documentation:
	- README file:
	- Testing plan: Please describe in detail how you tested your program. -->
