CC=gcc
CFLAGS=-g -O2 -std=gnu89 -Wall -Wpointer-arith -Wstrict-prototypes -MMD
LIBFLAGS=-I. -shared -fPIC
LIBS=-L. -lbuddy
LIBOBJS=buddy.o

all: libbuddy.so libbuddy.a buddy-test malloc-test buddy-unit-test

buddy.o: buddy.c
	$(CC) $(CFLAGS) -shared -fPIC -c -o $@ $?

libbuddy.so: $(LIBOBJS)
	$(LD) $(LIBFLAGS) -o $@ $?

libbuddy.a: $(LIBOBJS)
	$(AR)  rcv $@ $(LIBOBJS)
	ranlib $@

buddy-unit-test: buddy-unit-test.o buddy.o
	$(CC) $(CFLAGS) -o $@ $?

buddy-test: buddy-test.o buddy.o
	$(CC) $(CFLAGS) -o $@ $?

malloc-test: malloc-test.o 
	$(CC) $(CFLAGS) -o $@ $?

clean:	
	/bin/rm -f *.o *.d a.out buddy-test malloc-test libbuddy.* buddy-unit-test
