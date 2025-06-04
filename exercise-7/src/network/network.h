// src/network/network.h

#ifndef NETWORK_H_
#define NETWORK_H_

#include <netinet/in.h>

namespace chat::net {

  /* 
  Function to create a TCP socket using IPv4.
  Returns: Socket file descriptor
  */
  int create_socket();

  /*
  Function to create an IPv4 address (sockaddr_in)
  Returns: the IPv4 address struct containing the details of the address
  */
  sockaddr_in create_address(
    int port /* port with which the address is binded */
  );

  /*
  Function to register a file descriptor with an epoll instance to monitor
  */
  void epoll_ctl_add(
    int epoll_file_descriptor, /* File descriptor of the epoll instance */
    int monitor_file_descriptor, /* File descriptor to be monitored */
    int events /* Events for which the file descriptor is monitored */
  );
}

#endif
