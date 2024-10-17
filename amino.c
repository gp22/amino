#include "bstrlib.h"
#include "error.h"
#include "sockets.h"
#include "sys.h"

#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>

#define BACKLOG 10
#define BUFSIZE 65536

void web(int fd) {
  char buff[BUFSIZE + 1];
  int mr;
  ssize_t ret;
  ssize_t res;
  bstring get = bfromcstr("GET");
  bstring req_f, req_m, req;
  struct bstrList *req_body, *req_header;

  ret = Recv(fd, buff, BUFSIZE, 0);
  if (ret == 0) {
    return;
    // TODO: add a way to quit the process without quitting the whole program
    // err_quit("failed to read request");
  }

  req = bfromcstr(buff);
  if (!req) {
    //err_quit("error reading request");
    char msg[] = "HTTP/1.1 500 Internal Server Error\n";
    ssize_t len = sizeof(msg);
    res = Send(fd, msg, len, 0);
    Close(fd);
    return;
  }

  req_body = bsplit(req, '\n');
  if (req_body->qty < 1) {
    //err_quit("invalid request");
    char msg[] = "HTTP/1.1 400 Bad Request\n";
    ssize_t len = sizeof(msg);
    res = Send(fd, msg, len, 0);
    Close(fd);
    return;
  }

  req_header = bsplit(req_body->entry[0], ' ');
  if (req_header->qty != 3) {
    //err_quit("invalid request");
    char msg[] = "HTTP/1.1 400 Bad Request\n";
    ssize_t len = sizeof(msg);
    res = Send(fd, msg, len, 0);
    Close(fd);
    return;
  }

  req_m = req_header->entry[0];
  mr = biseqcaseless(req_m, get);
  if (mr != 1) {
    char msg[] = "HTTP/1.1 405 Method Not Allowed\n";
    ssize_t len = sizeof(msg);
    res = Send(fd, msg, len, 0);
    Close(fd);
    return;
  } else {
    char msg[] = "HTTP/1.1 200 OK\n";
    ssize_t len = sizeof(msg);
    res = Send(fd, msg, len, 0);
    Close(fd);
    return;
  }

  // req_f = req_header->entry[1];
  //  TODO: Make requested file is valid (correct ext, exists)

  //Close(fd);
  // bdestroy(req_f);
  //bdestroy(req_m);
  //bdestroy(req);
  //bstrListDestroy(req_body);
  //bstrListDestroy(req_header);
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
