// ./client/client-chat.cpp

/* standard headers */
#include <string>
#include <unistd.h>

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

    communication_loop();
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
  Function to communicate with the server endlessly on a loop
  */
  void Client::communication_loop() {

    char buffer[BUF_SIZE];
    while(true) {

      // get input from the client
      std::cout << "Give your input here:\n";

      std::string input = "";
      std::getline(std::cin, input);
      
      // write the input to the server
      check_error(write(client_socket_fd, input.c_str(), input.size() + 1) 
                  <= 0, "Failed to write from client to server");
      
      // read from server -- temporary -- echo
      int read_bytes = 0;
      set_buffer_to_zero(buffer);
      while((read_bytes = read(client_socket_fd, buffer, BUF_SIZE)) > 0) {
        std::cout << "Echo: " << buffer << std::endl;
        set_buffer_to_zero(buffer);
      }
      // check for errors
      check_error(read_bytes < 0, "Failed to read from the server");
      // if nothing is read, the buffer is clear, so go back to taking input
    }
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
  }

  // --------------- PRIVATE FUNCTIONS END HERE ---------------
}