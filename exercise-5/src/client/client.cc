#include "client.h"
#include "../net/chat-sockets.h"
#include "../utils.h"

// constructor
Client::Client() {
  Client::client_socket = tt::chat::net::create_socket();
}

// destructor
Client::~Client() {
  close(Client::client_socket);
}

// public member functions
void Client::connect_server(const std::string &server_ip, int port) {
  Client::server_address = Client::create_server_address(server_ip, port);
  Client::connect_to_server(Client::client_socket, Client::server_address);
}

void Client::send_message(const std::string &message) {
  Client::send_and_receive_message(Client::client_socket, message);
}

// private member functions
sockaddr_in Client::create_server_address(const std::string &server_ip, int port) {
  sockaddr_in address = tt::chat::net::create_address(port);
  // Convert the server IP address to a binary format
  auto err_code = inet_pton(AF_INET, server_ip.c_str(), &address.sin_addr);
  tt::chat::check_error(err_code <= 0, "Invalid address/ Address not supported\n");
  return address;
}

void Client::connect_to_server(int sock, sockaddr_in &server_address) {
  auto err_code =
      connect(sock, (sockaddr *)&server_address, sizeof(server_address));
  tt::chat::check_error(err_code < 0, "Connection Failed.\n");
}

void Client::send_and_receive_message(int sock, const std::string &message) {
  const int kBufferSize = 1024;
  char recv_buffer[kBufferSize] = {0};

  // Send the message to the server
  send(sock, message.c_str(), message.size(), 0);
  std::cout << "Sent: " << message << "\n";

  // Receive response from the server
  ssize_t read_size = read(sock, recv_buffer, kBufferSize);
  tt::chat::check_error(read_size < 0, "Read error.\n");
  if (read_size > 0) {
    std::cout << "Received: " << recv_buffer << "\n";
  } else if (read_size == 0) {
    std::cout << "Server closed connection.\n";
  }
}
