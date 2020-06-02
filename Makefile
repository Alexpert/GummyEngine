CC=clang
CFLAGS=-Wall -Iinclude

build/bin/triangle: test/triangle/main.c build/lib/libgummy.so
	$(CC) $(CFLAGS) -Lbuild/lib -lgummy -lSDL2 -o $@ $<

build/lib/libgummy.so: $(wildcard src/libgummy/*.c)
	$(CC) $(CFLAGS) -lGL -fPIC -shared -o $@ $^

