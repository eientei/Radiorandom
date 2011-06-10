all: native docs

docs: $(shell find src -type f) docs/config
	doxygen docs/config 

native: 
	cd build-native; cmake .; make;

clean:
	cd build-native; make clean; true
	cd build-native; rm -fr CMakeCache.txt CMakeFiles cmake_install.cmake Makefile

