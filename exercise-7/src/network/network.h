// ./src/network/network.h

#ifndef __NETWORK_H__
#define __NETWORK_H__

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
}

#endif