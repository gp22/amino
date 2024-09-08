CC = cc
CFLAGS=-Wall -g -O0

default: sockets.c sockets.h amino.c
	$(CC) $(CFLAGS) sockets.c error.c amino.c -o amino

clean:
	rm amino
	find . -name "*.gc*" -exec rm {} \;
	rm -rf `find . -name "*.dSYM" -print`
