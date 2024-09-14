#ifndef _commands_h
#define _commands_h

#include <netdb.h>

int Getaddrinfo(char *, char *, struct addrinfo *, struct addrinfo **);
int Socket(int, int, int);

#endif
