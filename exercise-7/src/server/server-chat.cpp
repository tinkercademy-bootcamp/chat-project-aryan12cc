// ./server/server-chat.cpp

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

    // not implemented
    create_server_socket(port);

    return;
  }

  /*
  Destructor for the class Server()
  Ensures resource cleanup of member functions and variables
  */
  Server::~Server() {

    // not implemented
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
    // not implemented
    return;
  }
  // --------------- PRIVATE FUNCTIONS END HERE ---------------
}