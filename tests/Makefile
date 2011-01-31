include ../Makefile.inc

default: all

all: testDB testMap

testDB: ../include/db.o ../include/map.o testDB.c
	$(CC) $(CFLAGS) -lpq testDB.c ../include/map.o ../include/db.o -o testDB.bin

testMap: ../include/map.o testMap.c
	$(CC) $(CFLAGS) -lssl testMap.c ../include/map.o -o testMap.bin

clean:
	rm -f *.o

distclean: clean
	rm -f *.bin
