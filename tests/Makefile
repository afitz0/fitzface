include ../Makefile.inc

default: all

all: posts testMap

posts: ../include/page.o posts.c ../include/db.o
	$(CC) $(CFLAGS) -lpq posts.c ../include/map.o ../include/db.o ../include/page.o -o posts.bin

testMap: ../include/map.o testMap.c
	$(CC) $(CFLAGS) -lssl testMap.c ../include/map.o -o testMap.bin

clean:
	rm -f *.o

distclean: clean
	rm -f *.bin
