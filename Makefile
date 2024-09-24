CC = cc
CFLAGS=-Wall -g -O0

default: bstrlib.c bstrlib.h error.c error.h sockets.c sockets.h sys.c sys.h amino.c
	$(CC) $(CFLAGS) bstrlib.c sockets.c error.c sys.c amino.c -o amino

showip: error.c error.h sockets.c sockets.h showip.c
	$(CC) $(CFLAGS) error.c sockets.c showip.c -o showip

clean:
	rm amino showip
	find . -name "*.gc*" -exec rm {} \;
	rm -rf `find . -name "*.dSYM" -print`
