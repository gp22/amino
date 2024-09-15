CC = cc
CFLAGS=-Wall -g -O0

default: error.c error.h sockets.c sockets.h sys.c sys.h amino.c
	$(CC) $(CFLAGS) sockets.c error.c amino.c -o amino

showip: error.c error.h sockets.c sockets.h showip.c
	$(CC) $(CFLAGS) error.c sockets.c showip.c -o showip

clean:
	rm amino showip
	find . -name "*.gc*" -exec rm {} \;
	rm -rf `find . -name "*.dSYM" -print`
