all: obj lib

obj:
	cd iri && $(MAKE)
	cd xform && $(MAKE)
	cd gcpm && $(MAKE)
	gcc -c -fPIC libgcpm.c -o libgcpm.o
	
lib:
	gfortran -fPIC -fno-automatic -ffree-line-length-none --std=legacy -shared -lm -o libgcpm.so libgcpm.o iri/*.o xform/*.o gcpm/*.o
	
clean:
	cd iri && $(MAKE) clean
	cd xform && $(MAKE) clean
	cd gcpm && $(MAKE) clean
	rm -v libgcpm.so
