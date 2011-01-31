include ../Makefile.inc

default: all

all: 404 aboutMe aboutSite index newPost resume

.c: ../include/page.o
	$(CC) $(CFLAGS) $@.c -lpq -lssl ../include/*.o -o ../bin/$@.bin

clean:
	rm -fr *.o

distclean: clean
	rm -fr ../bin/*.bin
