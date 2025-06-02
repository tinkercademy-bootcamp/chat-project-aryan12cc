// ./server/server-chat.cpp

/* standard headers */
#include <sys/epoll.h>
#include <unistd.h>

/* user-defined headers */
#include "../utils.h"
#include "../network/network.h"
#include "server-chat.h"

namespace chat::server {
  // --------------- PUBLIC FUNCTIONS START HERE ---------------

  /*
  Constructor for the class Server(). 
  Initializes member variables and member functions
  */
  Server::Server(
    int port /* the port through which server will listen */
  ) {

    create_server_socket(port);

    server_listen_for_connections();

    return;
  }

  /*
  Destructor for the class Server()
  Ensures resource cleanup of member functions and variables
  */
  Server::~Server() {

    close(epoll_fd);
    close(listen_socket_fd);
    return;
  }

  // --------------- PUBLIC FUNCTIONS END HERE ---------------
  // --------------- PRIVATE FUNCTIONS START HERE ---------------

  /*
  The function creates a server socket tied to the port as given
  in the parameter
  */
  void Server::create_server_socket(
    int port /* the port through which server will listen */
  ) {
    listen_socket_fd = net::create_socket(); 
      // src/network/network.h 
    
    sockaddr_in server_address = net::create_address(port); 
      // src/network/network.h

    /*
    Configuring a listening server socket to allow incoming connections
    - SO_REUSEADDR to immediately bind the socket to a port
    */
    int opt = 1;
    setsockopt(listen_socket_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    check_error(bind(listen_socket_fd, (sockaddr *) &server_address, 
                sizeof(server_address)) < 0, "Bind failed");
      // utils.h

    check_error(listen(listen_socket_fd, 10) < 0, "Listen failed");
      // utils.h

    return;
  }

  /*
  Function to set the epoll file descriptor to listen to connections from
  multiple sockets, and act upon them
  */
  void Server::server_listen_for_connections() {
    epoll_fd = epoll_create1(0);
  }

  // --------------- PRIVATE FUNCTIONS END HERE ---------------
}