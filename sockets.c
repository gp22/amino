#include "sockets.h"
#include "error.h"

void Bind(int fd, const struct sockaddr *sa, socklen_t salen) {
  if (bind(fd, sa, salen) < 0)
    err_sys("bind error");
}

int Connect(int sockfd, struct sockaddr *serv_addr, int addrlen) {
  int status;

  if ((status = connect(sockfd, serv_addr, addrlen)) != 0)
    err_sys("connect error");

  return status;
}

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
