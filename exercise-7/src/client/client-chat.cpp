// src/client/client-chat.cpp

#include <iostream>
#include <string>
#include <sys/epoll.h>
#include <unistd.h>

#include "../network/network.h"
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
    // create an epoll file descriptor to monitor stdin and
    // server inputs
    int epoll_fd = net::initialize_epoll();
    net::epoll_ctl_add(epoll_fd, client_socket_fd_, EPOLLIN);
    net::epoll_ctl_add(epoll_fd, STDIN_FILENO, EPOLLIN);

    constexpr int MAX_EVENTS = 10; // max events to process at one go
    struct epoll_event events[MAX_EVENTS]; // stores all events after the
                                  // last time it was checked
    while(true) {
      int num_events = epoll_wait(epoll_fd, events, MAX_EVENTS, -1);
      
      for(int event_idx = 0; event_idx < num_events; event_idx++) {
        if(events[event_idx].data.fd == client_socket_fd_) { // server
          read_from_server();
        }
        else { // client input
          read_from_stdin();
        }
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

  void Client::read_from_server() {
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
      return;
    }
    else {
      // Error reading from server
      std::cerr << "Error reading from server: " << strerror(errno) 
                  << std::endl;
    }
  }

  void Client::read_from_stdin() {
    std::string input;
    std::getline(std::cin, input);

    // write to server
    check_error(write(client_socket_fd_, input.c_str(), input.size() + 1) 
              <= 0, "Failed to write from client to server");
  }

  // --------------- PRIVATE FUNCTIONS END HERE ---------------
}
