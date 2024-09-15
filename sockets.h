#ifndef _commands_h
#define _commands_h

#include <netdb.h>
#include <sys/socket.h>

void Bind(int, const struct sockaddr *, socklen_t);
int Connect(int, struct sockaddr *, int);
int Getaddrinfo(char *, char *, struct addrinfo *, struct addrinfo **);
int Socket(int, int, int);

#endif
