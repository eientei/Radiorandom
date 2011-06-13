all: native-release

docs: $(shell find radiorandom -type f) docs/config
	doxygen docs/config 

native-release: 
	cd build-native; cmake .; make;
	strip --strip-unneeded radiorandom-server


native-dev:
	cd build-native; cmake .; make;

clean:
	cd build-native; make clean; true
	cd build-native; rm -fr CMakeCache.txt CMakeFiles cmake_install.cmake Makefile

