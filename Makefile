all: native

native: 
	cd build-native; cmake .; make;

clean:
	cd build-native; make clean; true
	cd build-native; rm -fr CMakeCache.txt CMakeFiles cmake_install.cmake Makefile

