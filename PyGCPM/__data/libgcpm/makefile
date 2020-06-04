all: obj lib

obj:
	cd iri && $(MAKE)
	cd xform && $(MAKE)
	cd gcpm && $(MAKE)
	
lib:
	gfortran -fPIC -fno-automatic -ffree-line-length-none -shared -lm -o libgcpm.so iri/*.o xform/*.o gcpm/*.o
	
clean:
	cd iri && $(MAKE) clean
	cd xform && $(MAKE) clean
	cd gcpm && $(MAKE) clean
	rm -v libgcpm.so
