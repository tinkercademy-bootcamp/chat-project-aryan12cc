// src/client/client-chat.cpp

#include <iostream>
#include <string>
#include <unistd.h>

#include "../network/network.h"
#include "../utils.h"
#include "client-chat.h"

namespace chat::client {
  // --------------- PUBLIC FUNCTIONS START HERE ---------------

  Client::Client(int port) {

    client_setup_socket(port);

    connect_to_server();

    communication_loop();
  }

  // --------------- PUBLIC FUNCTIONS END HERE ---------------
  // --------------- PRIVATE FUNCTIONS START HERE ---------------
  
  void Client::client_setup_socket(int port) {
    client_socket_fd_ = net::create_socket();
    server_address_ = net::create_address(port);
  }

  void Client::communication_loop() {

    char buffer[BUF_SIZE];
    fd_set active_file_descriptors; // file descriptor set for
                                // monitoring readable file descriptors

    int max_file_descriptor = std::max(client_socket_fd_, STDIN_FILENO);

    while(true) {
      // clear file descriptor set and only add the two file descriptors
      FD_ZERO(&active_file_descriptors);
      FD_SET(client_socket_fd_, &active_file_descriptors);
      FD_SET(STDIN_FILENO, &active_file_descriptors);

      // wait for activity on any of the file descriptors
      int activity_result = select(max_file_descriptor + 1, 
                            &active_file_descriptors, NULL, NULL, NULL);
      
      check_error(activity_result < 0, "Error in select() call");
      
      // check for activity from server
      if(FD_ISSET(client_socket_fd_, &active_file_descriptors)) {
        clear_buffer(buffer);
        
        // read message from server
        int bytes_read = read(client_socket_fd_, buffer, BUF_SIZE - 1);
        
        // there is some message that has come from the server
        if(bytes_read > 0) {
          buffer[bytes_read] = '\0';
          std::cout << buffer << std::endl;

          // print for the next input
          std::cout << "Give your input here: " << std::endl;
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
        std::getline(std::cin, input);

        // write to server
        check_error(write(client_socket_fd_, input.c_str(), input.size() + 1) 
                  <= 0, "Failed to write from client to server");
      }
    }
  }

  void Client::connect_to_server() {
    // Trying to connect client socket to the server.
    // On failure, prints "Connection Failed" and terminates
    // the program
    check_error(connect(client_socket_fd_, (sockaddr *) &server_address_, 
                  sizeof(server_address_)) < 0, "Connection Failed");
  }

  // --------------- PRIVATE FUNCTIONS END HERE ---------------
}
