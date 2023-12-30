major_version = 0
minor_version = 1
patch_version = 0

lib_version = $(major_version).$(minor_version).$(patch_version)

all:
	make clean
	mkdir -p ./build
	gcc -Wall -Wextra -fpic -c basichashmap.c -o build/libbasichashmap.$(lib_version).o
	gcc -Wall -Wextra -shared -o build/libbasichashmap.$(lib_version).so build/libbasichashmap.$(lib_version).o
	cp basichashmap.h build/basichashmap.h

test:
	make clean
	mkdir -p ./build
	gcc -Wall -Wextra tests/main.c tests/helpers.c basichashmap.c -o build/test -lbasicvector
	./build/test

install:
	rm -rf /usr/lib/libbasichashmap.$(lib_version).so /usr/lib/libbasichashmap.$(major_version).so /usr/lib/libbasichashmap.so
	rm -rf /usr/include/basichashmap.h
	cp build/libbasichashmap.$(lib_version).so /usr/lib/libbasichashmap.$(lib_version).so
	ln -s /usr/lib/libbasichashmap.$(lib_version).so /usr/lib/libbasichashmap.$(major_version).so
	ln -s /usr/lib/libbasichashmap.$(lib_version).so /usr/lib/libbasichashmap.so
	cp build/basichashmap.h /usr/include/basichashmap.h

uninstall:
	rm -rf /usr/lib/libbasichashmap.*
	rm -rf /usr/include/basichashmap.h

clean:
	rm -rf ./build

