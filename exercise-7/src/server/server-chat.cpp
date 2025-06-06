// src/server/server-chat.cpp

/* standard headers */
#include <arpa/inet.h>
#include <array>
#include <fcntl.h>
#include <map>
#include <sys/epoll.h>
#include <unistd.h>

/* user-defined headers */
#include "../network/network.h"
#include "channels/channel-information.h"
#include "command/command.h"
#include "server-chat.h"

namespace chat::server {

  std::map<int, Channel> all_channels; // maps channel_id with the
                                       // corresponding channel object

  // --------------- PUBLIC FUNCTIONS START HERE ---------------

  Server::Server(int port) {

    // Create socket, bind and listen to it for incoming connections
    create_server_socket(port);

    // Initialize epoll manager for event monitoring of sockets
    epoll_fd_ = net::initialize_epoll();
    net::epoll_ctl_add(epoll_fd_, listen_socket_fd_, EPOLLIN);

    // Loop to communicate with the clients
    communication_loop();

    return;
  }

  // --------------- PUBLIC FUNCTIONS END HERE ---------------
  // --------------- PRIVATE FUNCTIONS START HERE ---------------

  int Server::accept_incoming_request() {
    struct sockaddr_in store_client_address; // store client address
                                          // when accept() is called
    socklen_t socket_length = sizeof(store_client_address);
                                        // size of sockaddr_in struct

    int connection_socket = accept(listen_socket_fd_, 
      (struct sockaddr*) &store_client_address, &socket_length);

    // convert client ip to a string
    clear_buffer(buffer);
    inet_ntop(AF_INET, (char*) &store_client_address.sin_addr, buffer,
      sizeof(store_client_address));
    
    spdlog::info("Connected with client at address {0}:{1}", buffer,
      ntohs(store_client_address.sin_port));

    // set the client socket to non blocking mode using O_NONBLOCK
    check_error(fcntl(connection_socket, F_SETFL, 
      fcntl(connection_socket, F_GETFL, 0) | O_NONBLOCK) == -1,
      "Non-blocking socket failed");

    // add the file descriptor to the list of epoll file descriptor 
    // list for monitoring
    net::epoll_ctl_add(epoll_fd_, connection_socket, EPOLLIN | 
        EPOLLHUP | EPOLLRDHUP); 
    return connection_socket;
  }

  void Server::close_client_connection(int file_descriptor) {
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
    
    spdlog::info("Connection closed with client {}", client_info);
    
    // Clean up resources
    close(file_descriptor);
    epoll_ctl(epoll_fd_, EPOLL_CTL_DEL, file_descriptor, nullptr);
  }

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
          int new_connection_socket = accept_incoming_request();
          std::string help_result = command::_execute_help(new_connection_socket);
            // result of executing /help command
          write_data_to_client(new_connection_socket, help_result);
            // writing back the result to the client
        }
        // someone sent an input
        else if(events[event_idx].events & EPOLLIN) {
          parse_input_from_client(events[event_idx].data.fd);
            // read and parse the input given by the client
        }

        // check if the connection is closing
        if(events[event_idx].events & (EPOLLHUP | EPOLLRDHUP)) {
          close_client_connection(events[event_idx].data.fd);
        }
      }
    }
  }

  void Server::create_server_socket(int port) {
    listen_socket_fd_ = net::create_socket(); 
    
    sockaddr_in server_address = net::create_address(port); 

    /*
    Configuring a listening server socket to allow incoming connections
    - SO_REUSEADDR to immediately bind the socket to a port
    */
    int opt = 1;
    setsockopt(listen_socket_fd_, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    // Bind socket to IP and port specified in server_address
    check_error(bind(listen_socket_fd_, (sockaddr *) &server_address, 
                sizeof(server_address)) < 0, "Bind failed");
    
    // Set socket to non-blocking mode
    check_error(fcntl(listen_socket_fd_, F_SETFL, 
      fcntl(listen_socket_fd_, F_GETFL, 0) | O_NONBLOCK) == -1,
      "Non-blocking socket failed");
    
    // Start listening on socket. Allow upto 10 backlogged connections
    check_error(listen(listen_socket_fd_, 10) < 0, "Listen failed");
    
    // Print a message to denote server has started listening

    spdlog::info("Server has started listening on port {}", port);
    std::cout << "Server has started listening on port " << port << std::endl;
    
    return;
  }

  void Server::parse_input_from_client(int file_descriptor) {
    std::string input_data{}; // to store the input data
    while(true) {
      // read the message
      int bytes_read = read(file_descriptor, buffer,
                              BUF_SIZE);
      // Check for end of data or error
      if(bytes_read == 0) {
        // Connection closed by client
        break;
      }
      else if(bytes_read < 0) {
        // Error occurred or would block (non-blocking socket)
        if(errno != EAGAIN && errno != EWOULDBLOCK) {
          spdlog::error("Error reading from client: {}", strerror(errno));
        }
        break;
      }
      input_data += std::string(buffer, bytes_read);
              // convert to std::string
    }
    // dont parse if there was an issue
    if(input_data == "") {
      return;
    }
    std::string parsed_data;
    bool close_file_descriptor = false;
    parsed_data = command::parse_client_command(input_data, file_descriptor,
                                                close_file_descriptor);

    // write the message back
    write_data_to_client(file_descriptor, parsed_data);

    if(close_file_descriptor) {
      close_client_connection(file_descriptor);
    }
  }

  void Server::write_data_to_client(int file_descriptor, std::string data) {
    check_error(write(file_descriptor, data.c_str(), data.size()) 
      <= 0, "Error while writing");
  }

  // --------------- PRIVATE FUNCTIONS END HERE ---------------
}
