#include "error.h"
#include "sockets.h"
#include <arpa/inet.h>

int main(int argc, char *argv[]) {

  int listenfd, connfd;
  struct sockaddr_in servaddr;
  char buff[MAXLINE];

  listenfd = Socket(AF_INET, SOCK_STREAM, 0);

  return EXIT_SUCCESS;
}
