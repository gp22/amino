#ifndef _commands_h
#define _commands_h

#include <netdb.h>
#include <sys/_types/_socklen_t.h>
#include <sys/socket.h>

int Accept(int, struct sockaddr *, socklen_t *);
void Bind(int, const struct sockaddr *, socklen_t);
int Connect(int, struct sockaddr *, int);
int Getaddrinfo(char *, char *, struct addrinfo *, struct addrinfo **);
int Listen(int, int);
int Socket(int, int, int);

#endif
