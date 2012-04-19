all: native-release

docs: $(shell find src -type f) docs/config
	doxygen docs/config >/dev/null

native-release: 
	cd build-native; cmake .; make;
	strip --strip-unneeded radiorandom-web-server


native-dev:
	cd build-native; cmake .; make;

clean:
	cd build-native; make clean; true
	cd build-native; rm -fr CMakeCache.txt CMakeFiles cmake_install.cmake Makefile

