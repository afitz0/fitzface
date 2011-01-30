include ../Makefile.inc

default: all

all: map page db 

page:
	$(CC) $(CFLAGS) -c page.c

db: map.o
	$(CC) $(CFLAGS) $(DB) -lpq -c db.c

map:
	$(CC) $(CFLAGS) -lssl -c map.c

clean:
	rm -f *.o

distclean: clean
	rm -f *.bin
