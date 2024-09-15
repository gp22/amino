#include "sockets.h"
#include "error.h"

int Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen) {
  int accept_fd;

  if ((accept_fd = accept(sockfd, addr, addrlen)) < 0)
    err_sys("accept error");

  return accept_fd;
}

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

int Listen(int sockfd, int backlog) {
  int status;

  if ((status = listen(sockfd, backlog)) != 0)
    err_sys("listen error");

  return status;
}

int Socket(int family, int type, int proto) {
  int sockfd;

  if ((sockfd = socket(family, type, proto)) < 0)
    err_sys("socket error");

  return sockfd;
}
