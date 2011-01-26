CC      = gcc
CFLAGS  = -Wall -pedantic -ggdb --std=gnu99 -I/usr/include/postgresql
WEBROOT = /var/www

all: include tests src

install: all
	cp content/*.html src/*.bin css/*.css .htaccess $(WEBROOT)

src: force
	make -C src all

include: force
	make -C include all

tests: force
	make -C tests all

posts: page.o posts.c db.o
	$(CC) $(CFLAGS) $(DB) -c posts.c
	$(CC) $(CFLAGS) $(DB) -lpq map.o db.o posts.o page.o -o posts.bin

testMap: map.o testMap.c
	$(CC) $(CFLAGS) -c testMap.c
	$(CC) $(CFLAGS) -lssl map.o testMap.o -o testMap.bin

clean:
	make -C src clean
	make -C tests clean
	make -C include clean

distclean: clean
	make -C src distclean
	make -C tests distclean
	make -C include distclean

force:
	true
