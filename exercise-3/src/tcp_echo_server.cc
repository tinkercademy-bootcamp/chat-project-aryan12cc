#include <iostream>
#include <netinet/in.h>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

const int kBufferSize = 1024;

void check_error(bool test, std::string error_message, bool exit_flag = true) {
  if(test) {
    std::cerr << error_message << "\n";
    if(exit_flag) {
      exit(EXIT_FAILURE);
    }
  }
  return;
}

int create_socket() {
  int my_sock = socket(AF_INET, SOCK_STREAM, 0);
  check_error(my_sock < 0, "Socket creation error");
  return my_sock;
}

bool set_socket_options(int sock, int opt) {
  int socket_option_return = setsockopt(sock, SOL_SOCKET, 
                    SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));
  check_error(socket_option_return < 0, "setsockopt() error");
  return true;
}

sockaddr_in create_address(int port) {
  sockaddr_in address;
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(port);
  return address;
}

void bind_address_to_socket(int sock, sockaddr_in &address) {
  check_error(bind(sock, (sockaddr*) &address, sizeof(address)) < 0, "bind failed");
}

void listen_on_socket(int sock) {
  check_error(listen(sock, 3) < 0, "listen failed");
}

void start_listening_on_socket(int my_socket, sockaddr_in &address) {
  const int kSocketOptions = 1;
  set_socket_options(my_socket, kSocketOptions);

  bind_address_to_socket(my_socket, address);
  listen_on_socket(my_socket);
}

void handle_accept(int client_socket) {
  char buffer[kBufferSize] = {0};
  ssize_t valread = read(client_socket, buffer, kBufferSize);
  std::string error_message = "Read error on client socket " + std::to_string(client_socket);
  check_error(valread < 0, error_message);
  if (valread > 0) {
    std::cout << "Received: " << buffer << "\n";
    sleep(10);
    send(client_socket, buffer, valread, 0);
    std::cout << "Echo message sent\n";
  } else if (valread == 0) {
    std::cout << "Client disconnected.\n";
  }
  close(client_socket);
}

void handle_connections(int sock, int port) {
  sockaddr_in address = create_address(port);
  socklen_t address_size = sizeof(address);

  // #Task - is it good to have an infinite loop?
  // Yes this is fine since servers should ideally be running infinitely
  while (true) {
    int accepted_socket = accept(sock, (sockaddr *)&address, &address_size);
    check_error(accepted_socket < 0, "accept error");
    handle_accept(accepted_socket);
  }
}

int main() {
  const int kPort = 8080;
  int my_socket = create_socket();
  sockaddr_in address = create_address(kPort);

  // #Task - is there a better name for this function?
  // init_socket() could be a better name
  start_listening_on_socket(my_socket, address);
  std::cout << "Server listening on port " << kPort << "\n";
  handle_connections(my_socket, kPort);
  close(my_socket);

  return 0;
}