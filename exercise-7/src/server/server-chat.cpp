// src/server/server-chat.cpp

/* standard headers */
#include <arpa/inet.h> // sockaddr_in struct, inet_ntop(), htons()
#include <fcntl.h> // fcntl, O_NONBLOCK
#include <string> // std::string
#include <sys/epoll.h> // epoll_create1, epoll_wait, epoll_event
#include <unistd.h> // close, read, write, accept

/* user-defined headers */
#include "../utils.h"
#include "../network/network.h"
#include "server-chat.h"

namespace chat::server {
  // --------------- PUBLIC FUNCTIONS START HERE ---------------

  /*
  Constructor for the class Server(). 
  Creates socket for the server and starts listening for incoming 
  connections from clients
  */
  Server::Server(
    int port /* the port through which server will listen */
  ) {

    // Create socket, bind and listen to it for incoming connections
    create_server_socket(port);

    // Initialize epoll manager for event monitoring of sockets
    initialize_epoll();

    // Loop to communicate with the clients
    communication_loop();

    return;
  }

  /*
  Destructor for the class Server()
  Ensures resource cleanup of member functions and variables
  */
  Server::~Server() {

    close(epoll_fd_);
    close(listen_socket_fd_);
    return;
  }

  // --------------- PUBLIC FUNCTIONS END HERE ---------------
  // --------------- PRIVATE FUNCTIONS START HERE ---------------

  // Function to accept an incoming connection request from the client
  void Server::accept_incoming_request() {
    struct sockaddr_in store_client_address; // store client address
                                          // when accept() is called
    socklen_t socket_length = sizeof(store_client_address);
                                        // size of sockaddr_in struct

    char ip_buffer[BUF_SIZE]; // can be used for anything
      // for example, storing client ip, client message etc.
    int connection_socket = accept(listen_socket_fd_, 
      (struct sockaddr*) &store_client_address, &socket_length);

    // convert client ip to a string
    clear_buffer(ip_buffer); // utils.h
    inet_ntop(AF_INET, (char*) &store_client_address.sin_addr, ip_buffer,
      sizeof(store_client_address));

    std::cout << "Connected with client at address " << ip_buffer << ":" 
      << ntohs(store_client_address.sin_port) << std::endl;

    // set the client socket to non blocking mode using O_NONBLOCK
    check_error(fcntl(connection_socket, F_SETFL, 
      fcntl(connection_socket, F_GETFL, 0) | O_NONBLOCK) == -1,
      "Non-blocking socket failed");
    // utils.h

    // add the file descriptor to the list of epoll file descriptor 
    // list for monitoring
    net::epoll_ctl_add(epoll_fd_, connection_socket, EPOLLIN | 
        EPOLLHUP | EPOLLRDHUP); 
    // src/network/network.h
  }

  // Function to gracefully close the connection between the server and
  // client after client disconnects
  void Server::close_client_connection(
    int file_descriptor /* the file descriptor to close connection from */
  ) {
    // Get client info from socket
    std::string client_info = "unknown";

    struct sockaddr_in store_client_address; // store client address
                                          // when accept() is called
    socklen_t socket_length = sizeof(store_client_address);
                                        // size of sockaddr_in struct
          
    if(getpeername(file_descriptor, 
        reinterpret_cast<struct sockaddr*>(&store_client_address), 
        &socket_length) == 0) {
      // Convert IP to string
      char ip_str[INET_ADDRSTRLEN];
      inet_ntop(AF_INET, &store_client_address.sin_addr, ip_str, INET_ADDRSTRLEN);
      
      // Format as IP:port
      client_info = std::string(ip_str) + ":" + 
                    std::to_string(ntohs(store_client_address.sin_port));
    }
    
    std::cout << "Connection closed with client " << client_info << std::endl;
    
    // Clean up resources
    close(file_descriptor);
    epoll_ctl(epoll_fd_, EPOLL_CTL_DEL, file_descriptor, nullptr);
  }

  // Loop that waits indefinitely for events on the file descriptors that
  // are registered on the epoll instance.
  void Server::communication_loop() {
    constexpr int MAX_EVENTS = 10; // max events to process at one go
    struct epoll_event events[MAX_EVENTS]; // stores all events after the
                                  // last time it was checked

    while(true) {
      // getting all events happened before last interaction
      int num_events = epoll_wait(epoll_fd_, events, MAX_EVENTS, -1);

      // looping through all the events
      for(int event_idx = 0; event_idx < num_events; event_idx++) {

        // incoming connection
        if(events[event_idx].data.fd == listen_socket_fd_) {
          // accept the incoming connection
          accept_incoming_request();
        }
        // someone sent an input
        else if(events[event_idx].events & EPOLLIN) {
          read_input_from_client(events[event_idx].data.fd);
        }

        // check if the connection is closing
        if(events[event_idx].events & (EPOLLHUP | EPOLLRDHUP)) {
          close_client_connection(events[event_idx].data.fd);
        }
      }
    }
  }

  /*
  The function creates a server socket tied to the port as given
  in the parameter
  */
  void Server::create_server_socket(
    int port /* the port through which server will listen */
  ) {
    listen_socket_fd_ = net::create_socket(); 
      // src/network/network.h 
    
    sockaddr_in server_address = net::create_address(port); 
      // src/network/network.h

    /*
    Configuring a listening server socket to allow incoming connections
    - SO_REUSEADDR to immediately bind the socket to a port
    */
    int opt = 1;
    setsockopt(listen_socket_fd_, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    // Bind socket to IP and port specified in server_address
    check_error(bind(listen_socket_fd_, (sockaddr *) &server_address, 
                sizeof(server_address)) < 0, "Bind failed");
      // utils.h
    
    // Set socket to non-blocking mode
    check_error(fcntl(listen_socket_fd_, F_SETFL, 
      fcntl(listen_socket_fd_, F_GETFL, 0) | O_NONBLOCK) == -1,
      "Non-blocking socket failed"); // utils.h
    
    // Start listening on socket. Allow upto 10 backlogged connections
    check_error(listen(listen_socket_fd_, 10) < 0, "Listen failed");
      // utils.h
    
    // Print a message to denote server has started listening
    std::cout << "Server has started listening on port " << port << std::endl;
    
    return;
  }

  /*
  Function to set the epoll file descriptor to listen to connections from
  multiple sockets
  */
  void Server::initialize_epoll() {
    // Create an epoll instance. epoll_fd_ stores the file descriptor
    epoll_fd_ = epoll_create1(0);

    // make the epoll instance monitor the file descriptor listening
    // for incoming connections for any input
    net::epoll_ctl_add(epoll_fd_, listen_socket_fd_, EPOLLIN);

    return;
  }

  /*
  Function to read the input data sent by the client to the server
  */
  void Server::read_input_from_client(
    int file_descriptor /* the file descriptor to read it from */
  ) {
    char read_buffer[BUF_SIZE];
    while(true) {
      clear_buffer(read_buffer); // utils.h

      // read the message
      int bytes_read = read(file_descriptor, read_buffer, 
                            sizeof(read_buffer));

      // all data read
      if(bytes_read <= 0) {
        break;
      }
      else {
        std::cout << "Received: " << read_buffer << std::endl;

        // write the message back
        write(file_descriptor, read_buffer, strlen(read_buffer));
      }
    }
  }

  // --------------- PRIVATE FUNCTIONS END HERE ---------------
}