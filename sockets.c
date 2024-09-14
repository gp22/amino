#include "sockets.h"
#include "error.h"

int Getaddrinfo(char *node, char *service, struct addrinfo *hints,
                struct addrinfo **res) {
  int status;

  if ((status = getaddrinfo(node, service, hints, res)) != 0)
    err_sys("getaddrinfo error");

  return status;
}

int Socket(int family, int type, int proto) {
  int sockfd;

  if ((sockfd = socket(family, type, proto)) < 0)
    err_sys("socket error");

  return sockfd;
}
