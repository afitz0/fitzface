CC      = gcc
CFLAGS  = -Wall -pedantic -ggdb --std=gnu99
WEBROOT = /var/www
DB      = -I/usr/include/postgresql

default: all

install:
	cp *.html *.bin *.css .htaccess $(WEBROOT)

all: 404 aboutMe aboutSite index map newPost page processPost resume db posts

page:
	$(CC) $(CFLAGS) -c page.c

db: map.o
	$(CC) $(CFLAGS) $(DB) -lpq -c db.c

map:
	$(CC) $(CFLAGS) -lssl -c map.c

404: page.o 404.c
	$(CC) $(CFLAGS) -c 404.c
	$(CC) $(CFLAGS) 404.o page.o -o 404.bin

posts: page.o posts.c db.o
	$(CC) $(CFLAGS) $(DB) -c posts.c
	$(CC) $(CFLAGS) $(DB) -lpq map.o db.o posts.o page.o -o posts.bin

aboutMe: page.o aboutMe.c
	$(CC) $(CFLAGS) -c aboutMe.c
	$(CC) $(CFLAGS) aboutMe.o page.o -o aboutMe.bin

aboutSite: page.o aboutSite.c
	$(CC) $(CFLAGS) -c aboutSite.c
	$(CC) $(CFLAGS) aboutSite.o page.o -o aboutSite.bin

index: page.o index.c
	$(CC) $(CFLAGS) -c index.c
	$(CC) $(CFLAGS) index.o page.o -o index.bin

newPost: page.o newPost.c
	$(CC) $(CFLAGS) -c newPost.c
	$(CC) $(CFLAGS) newPost.o page.o -o newPost.bin

processPost: page.o processPost.c
	$(CC) $(CFLAGS) -c processPost.c
	$(CC) $(CFLAGS) processPost.o page.o -o processPost.bin

resume: page.o resume.c
	$(CC) $(CFLAGS) -c resume.c
	$(CC) $(CFLAGS) resume.o page.o -o resume.bin

testMap: map.o testMap.c
	$(CC) $(CFLAGS) -c testMap.c
	$(CC) $(CFLAGS) -lssl map.o testMap.o -o testMap.bin

clean:
	rm -fr *.o

distclean: clean
	rm -fr *.bin
