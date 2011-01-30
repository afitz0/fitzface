include ../Makefile.inc

default: all

all: 404 aboutMe aboutSite index newPost processPost resume

.c: ../include/page.o
	$(CC) $(CFLAGS) $@.c ../include/page.o -o $@.bin

clean:
	rm -fr *.o

distclean: clean
	rm -fr *.bin
