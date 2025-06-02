// ./src/utils/network.cpp

/* standard headers */

/* user-defined headers */
#include "network.h"
#include "../utils.h"

namespace chat::net {
  /*
  A function to create a socket and return it
  Returns: Socket
  */
  int create_socket() {
    int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    check_error(sock_fd < 0, "Socket creation error\n");
    return sock_fd;
  }
}