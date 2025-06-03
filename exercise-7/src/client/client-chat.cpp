// src/client/client-chat.cpp

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
    fd_set active_file_descriptors; // file descriptor set for
                                // monitoring readable file descriptors

    int max_file_descriptor = std::max(client_socket_fd, STDIN_FILENO);

    // get input from the client
    std::cout << "Give your input here:\n";

    while(true) {
      // clear file descriptor set and only add the two file descriptors
      FD_ZERO(&active_file_descriptors);
      FD_SET(client_socket_fd, &active_file_descriptors);
      FD_SET(STDIN_FILENO, &active_file_descriptors);

      // wait for activity on any of the file descriptors
      int activity_result = select(max_file_descriptor + 1, 
                            &active_file_descriptors, NULL, NULL, NULL);
      
      check_error(activity_result < 0, "Error in select() call");
      
      // check for activity from server
      if(FD_ISSET(client_socket_fd, &active_file_descriptors)) {
        clear_buffer(buffer);
        
        // read message from server
        int bytes_read = read(client_socket_fd, buffer, BUF_SIZE - 1);
        
        if(bytes_read > 0) {
          buffer[bytes_read] = '\0';
          std::cout << "From server: " << buffer << std::endl;

          // print for the next input
          std::cout << "Give your input here:\n";
        }
        else if(bytes_read == 0) {
          // Server has closed the connection
          std::cout << "Server disconnected" << std::endl;
          break;
        }
        else {
          // Error reading from server
          std::cerr << "Error reading from server: " << strerror(errno) << std::endl;
          break;
        }
      }
      
      // check for activity from user
      if(FD_ISSET(STDIN_FILENO, &active_file_descriptors)) {
        // read input
        std::string input;
        std::getline(std::cin, input); // reading entire line

        // write to server
        check_error(write(client_socket_fd, input.c_str(), input.size() + 1) 
                  <= 0, "Failed to write from client to server");
      }
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