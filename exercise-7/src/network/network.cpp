// ./src/network/network.cpp

/* standard headers */

/* user-defined headers */
#include "network.h"
#include "../utils.h"

namespace chat::net {
  /*
  Creates a TCP socket using IPv4. If an error occurs, it reports
  an error and terminates the program
  Returns: File descriptor of the created socket
  */
  int create_socket() {
    int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    check_error(sock_fd < 0, "Socket creation error\n");
    return sock_fd;
  }
}