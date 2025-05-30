#include "../net/chat-sockets.h"
#include "../utils.h"
#include "server.h"

Server::Server(int port) {
  server_port = port;
}

Server::~Server() {
  close(server_socket);
}

// public member functions
void Server::create_server() {
  create_server_socket();
  create_server_address();
}

void Server::connect_to_socket() {
  bind_address_to_socket();
  listen_on_socket();

  std::cout << "Server is listening on port: " << server_port << std::endl;
  handle_connections();
}

// private member functions
void Server::set_socket_options(int options) {
  auto err_code = setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                             &options, sizeof(options));
  tt::chat::check_error(err_code < 0, "setsockopt() error\n");
}

void Server::create_server_socket() {
  server_socket = tt::chat::net::create_socket();
  set_socket_options(1);
}

void Server::create_server_address() {
  server_address = tt::chat::net::create_address(server_port);
  server_address.sin_addr.s_addr = INADDR_ANY;
}

void Server::bind_address_to_socket() {
  auto err_code = bind(server_socket, (sockaddr *)&server_address, sizeof(server_address));
  tt::chat::check_error(err_code < 0, "bind failed\n");
}

void Server::listen_on_socket() {
  auto err_code = listen(server_socket, 3);
  tt::chat::check_error(err_code < 0, "listen failed\n");
}

void Server::handle_accept(int accepted_socket) {
  const int kBufferSize = 1024;
  char buffer[kBufferSize] = {0};
  ssize_t read_size = read(accepted_socket, buffer, kBufferSize);

  tt::chat::check_error(read_size < 0,
                   "Read error on client socket " + std::to_string(accepted_socket));
  if (read_size > 0) {
    std::cout << "Received:" << buffer << "\n";
    send(accepted_socket, buffer, read_size, 0);
    std::cout << "Echo message sent\n";
  } else if (read_size == 0) {
    std::cout << "Client disconnected.\n";
  } else {
    std::cerr << "Read error on client socket " << accepted_socket << "\n";
  }
  close(accepted_socket);
}

void Server::handle_connections() {
  socklen_t address_size = sizeof(server_address);

  while (true) {
    int accepted_socket = accept(server_socket, (sockaddr *)&server_address, &address_size);
    tt::chat::check_error(accepted_socket < 0, "Accept error n ");
    handle_accept(accepted_socket);
  }
}