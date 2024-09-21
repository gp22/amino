#include "bstrlib.h"
#include "error.h"
#include "sockets.h"
#include "sys.h"

#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

#define BACKLOG 10
#define BUFSIZE 65536

void web(int fd) {
  char buff[BUFSIZE + 1];
  int i;
  ssize_t ret;
  bstring req;
  struct bstrList *req_body, *req_header;

  ret = Recv(fd, buff, BUFSIZE, 0);
  if (ret == 0) {
    return;
    // TODO: add a way to quit the process without quitting the whole program
    // err_quit("failed to read request");
  }

  req = bfromcstr(buff);
  if (!req) {
    err_quit("error reading request");
  }

  req_body = bsplit(req, '\n');
  if (req_body->qty < 1) {
    err_quit("error reading request");
  }

  req_header = bsplit(req_body->entry[0], ' ');
  if (req_header->qty < 1) {
    err_quit("error reading request");
  }

  for (i = 0; i < req_header->qty; i++) {
    printf("req_header[%i]: %s\n", i, (char *)req_header->entry[i]->data);
  }

  Close(fd);
  bdestroy(req);
  bstrListDestroy(req_body);
}

int main(int argc, char *argv[]) {
  int accept_fd, listen_fd;
  struct addrinfo hints, *res;
  struct sockaddr_storage accept_addr;
  socklen_t addr_size;

  memset(&hints, 0, sizeof hints); // make sure the struct is empty
  hints.ai_family = AF_UNSPEC;     // don't care IPv4 or IPv6
  hints.ai_socktype = SOCK_STREAM; // TCP stream sockets
  hints.ai_flags = AI_PASSIVE;     // fill in my IP for me

  Getaddrinfo(NULL, "http", &hints, &res);

  // TODO: remove Getaddrinfo and code the server details

  listen_fd = Socket(res->ai_family, res->ai_socktype, res->ai_protocol);
  Bind(listen_fd, res->ai_addr, res->ai_addrlen);
  Listen(listen_fd, BACKLOG);

  for (;;) {
    addr_size = sizeof accept_addr;
    accept_fd = Accept(listen_fd, (struct sockaddr *)&accept_addr, &addr_size);

    web(accept_fd);
  }

  Close(listen_fd);
  freeaddrinfo(res);

  return EXIT_SUCCESS;
}
