#include "net_operations.h"

#include <arpa/inet.h>
#include <sys/socket.h>

int create_socket() {
  int mysock = socket(AF_INET, SOCK_STREAM, 0);
  check_error(mysock < 0, "Socket creation error\n");
  return mysock;
}