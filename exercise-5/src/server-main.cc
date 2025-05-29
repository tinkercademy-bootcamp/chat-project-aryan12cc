#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "net/chat-sockets.h"
#include "server/server.h"
#include "utils.h"

// namespace tt::chat::server {

// void set_socket_options(int sock, int opt) {
//   namespace ttc = tt::chat;
//   auto err_code = setsockopt(sock, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
//                              &opt, sizeof(opt));
//   ttc::check_error(err_code < 0, "setsockopt() error\n");
// }

// int create_server_socket() {
//   int sock = net::create_socket();
//   set_socket_options(sock, 1);
//   return sock;
// }

// void bind_address_to_socket(int sock, sockaddr_in &address) {
//   namespace ttc = tt::chat;
//   auto err_code = bind(sock, (sockaddr *)&address, sizeof(address));
//   ttc::check_error(err_code < 0, "bind failed\n");
// }

// void listen_on_socket(int sock) {
//   namespace ttc = tt::chat;
//   auto err_code = listen(sock, 3);
//   ttc::check_error(err_code < 0, "listen failed\n");
// }

// void handle_accept(int sock) {
//   namespace ttc = tt::chat;
//   const int kBufferSize = 1024;
//   char buffer[kBufferSize] = {0};
//   ssize_t read_size = read(sock, buffer, kBufferSize);

//   ttc::check_error(read_size < 0,
//                    "Read error on client socket " + std::to_string(sock));
//   if (read_size > 0) {
//     std::cout << "Received:" << buffer << "\n";
//     send(sock, buffer, read_size, 0);
//     std::cout << "Echo message sent\n";
//   } else if (read_size == 0) {
//     std::cout << "Client disconnected.\n";
//   } else {
//     std::cerr << "Read error on client socket " << sock << "\n";
//   }
//   close(sock);
// }

// sockaddr_in create_server_address(int port) {
//   namespace ttn = tt::chat::net;
//   sockaddr_in address = ttn::create_address(port);
//   address.sin_addr.s_addr = INADDR_ANY;
//   return address;
// }

// void handle_connections(int sock, sockaddr_in &address) {
//   socklen_t address_size = sizeof(address);

//   while (true) {
//     int accepted_socket = accept(sock, (sockaddr *)&address, &address_size);
//     check_error(accepted_socket < 0, "Accept error n ");
//     handle_accept(accepted_socket);
//   }
// }

// } // namespace tt::chat::server

int main() {
  namespace ttc = tt::chat;
  const int kPort = 8080;

  Server thisServer = Server(kPort);
  thisServer.create_server();
  thisServer.connect_to_socket();

  // int my_socket = ttc::server::create_server_socket();
  // sockaddr_in address = ttc::server::create_server_address(kPort);

  // // start listening on the socket
  // ttc::server::bind_address_to_socket(my_socket, address);
  // ttc::server::listen_on_socket(my_socket);

  // std::cout << "Server listening on port " << kPort << "\n";
  // ttc::server::handle_connections(my_socket, address);
  // close(my_socket);

  return 0;
}
