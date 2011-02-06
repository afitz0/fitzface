include Makefile.inc

all: include tests src

install:
	cp -r content/*.html bin/* css .htaccess js $(WEBROOT)

src: force
	make -C src all
include: force
	make -C include all
tests: force
	make -C tests all

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
