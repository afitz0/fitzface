CC      = gcc
CFLAGS  = -Wall -pedantic -ggdb --std=gnu99 -I/usr/include/postgresql

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
