// src/network/network.cpp

/* standard headers */
#include <sys/epoll.h> // struct epoll_event, epoll_ctl

/* user-defined headers */
#include "network.h"
#include "../utils.h"

namespace chat::net {
  
  int create_socket() {
    int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    check_error(sock_fd < 0, "Socket creation error\n"); // utils.h
    return sock_fd;
  }

  sockaddr_in create_address(int port) {
    sockaddr_in address;

    // allow connections from IPv4 family
    address.sin_family = AF_INET;

    // 
    address.sin_port = htons(port); // included as a part of network.h
    address.sin_addr.s_addr = INADDR_ANY;
    return address;
  }
  
  void epoll_ctl_add(int epoll_file_descriptor, int monitor_file_descriptor,
                      int events) {

    // populate the epoll_event struct with the data provided
    struct epoll_event event;
    event.events = events;
    event.data.fd = monitor_file_descriptor;

    check_error(epoll_ctl(epoll_file_descriptor, EPOLL_CTL_ADD, 
                        monitor_file_descriptor, &event) == -1,
                        "Epoll ctl() failed"); // utils.h
    
  }

  int initialize_epoll() {
      // Create an epoll instance. epoll_fd_ stores the file descriptor
      int epoll_fd = epoll_create1(0);
      return epoll_fd;
  }
}
