#include "sys.h"
#include "error.h"

int Close(int fildes) {
  int status;

  if ((status = close(fildes)) != 0)
    err_sys("error closing file descriptor: %d\n", fildes);

  return status;
}
