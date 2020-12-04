
all:
	cd buddy-non-preload/; make
	cd buddy-preload/; make

clean:	
	cd buddy-non-preload/; make clean
	cd buddy-preload/; make clean
