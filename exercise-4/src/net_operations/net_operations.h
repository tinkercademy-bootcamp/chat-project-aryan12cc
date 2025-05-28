#ifndef __NET_OPERATIONS__
#define __NET_OPERATIONS__

#include <cstdlib>
#include <iostream>
#include <netinet/in.h>

template <typename T, typename S> void check_error(T test, S error_message) {
  if (test) {
    std::cerr << error_message << "\n";
    exit(EXIT_FAILURE);
  }
}

int create_socket();

#endif