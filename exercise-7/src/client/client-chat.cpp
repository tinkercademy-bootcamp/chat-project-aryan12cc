// ./client/client-chat.cpp

/* standard headers */

/* user-defined headers */
#include "../network/network.h"
#include "../utils.h"
#include "client-chat.h"

namespace chat::client {
  // --------------- PUBLIC FUNCTIONS START HERE ---------------

  /*
  Constructor for the class Client(). 
  Initializes member variables and member functions
  */
  Client::Client(int port) {

    client_setup_socket(port); // setup socket for communication

    connect_to_server(); // connect to the server to send and receive messages
  }

  /*
  Destructor for the class Client().
  Ensures resource cleanup of member functions and variables
  */
  Client::~Client() {

  }

  // --------------- PUBLIC FUNCTIONS END HERE ---------------
  // --------------- PRIVATE FUNCTIONS START HERE ---------------
  
  /*
  Function to effectively setup the socket needed to connect
  to the server
  */
  void Client::client_setup_socket(int port) {
    client_socket_fd = net::create_socket(); // network/network.h
    server_address = net::create_address(port);
  }

  /*
  Function to connect the client to the server
  */
  void Client::connect_to_server() {
    // Trying to connect client socket to the server.
    // On failure, prints "Connection Failed" and terminates
    // the program
    check_error(connect(client_socket_fd, (sockaddr *) &server_address, 
                  sizeof(server_address)), "Connection Failed");
    
    std::cout << "Input: " << std::endl;
  }

  // --------------- PRIVATE FUNCTIONS END HERE ---------------
}