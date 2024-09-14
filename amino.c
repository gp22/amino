#include "error.h"
#include "sockets.h"
#include <arpa/inet.h>

int main(int argc, char *argv[]) {
  int listenfd, connfd, status;
  struct addrinfo hints, *res;
  struct sockaddr_in servaddr;
  char buff[MAXLINE];

  memset(&hints, 0, sizeof hints); // make sure the struct is empty
  hints.ai_family = AF_UNSPEC;     // don't care IPv4 or IPv6
  hints.ai_socktype = SOCK_STREAM; // TCP stream sockets
  hints.ai_flags = AI_PASSIVE;     // fill in my IP for me

  status = Getaddrinfo(NULL, "3490", &hints, &res);
  listenfd = Socket(AF_INET, SOCK_STREAM, 0);

  freeaddrinfo(res);

  return EXIT_SUCCESS;
}
