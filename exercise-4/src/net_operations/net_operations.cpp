#include "net_operations.h"

#include <arpa/inet.h>
#include <sys/socket.h>

int create_socket() {
  int mysock = socket(AF_INET, SOCK_STREAM, 0);
  check_error(mysock < 0, "Socket creation error\n");
  return mysock;
}

sockaddr_in create_address(std::optional<std::string> ip_address, int port) {
  sockaddr_in address;
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(port);

  if(ip_address.has_value()) {
    auto err_code = inet_pton(AF_INET, ip_address->c_str(), &address.sin_addr);
    check_error(err_code <= 0, "Invalid Address / Address not supported\n");
  }
  return address;
}