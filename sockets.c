#include "sockets.h"
#include "error.h"
#include <sys/socket.h>

int Socket(int family, int type, int proto) {
  int sockfd;

  if ((sockfd = socket(family, type, proto)) < 0)
    err_sys("socket error");

  return sockfd;
}
