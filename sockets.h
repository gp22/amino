#ifndef _commands_h
#define _commands_h

#include <netdb.h>
#include <sys/socket.h>

int Accept(int, struct sockaddr *, socklen_t *);
void Bind(int, const struct sockaddr *, socklen_t);
int Connect(int, struct sockaddr *, int);
int Getaddrinfo(char *, char *, struct addrinfo *, struct addrinfo **);
int Listen(int, int);
ssize_t Recv(int, void *, size_t, int);
int Socket(int, int, int);

#endif
