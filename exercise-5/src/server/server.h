#ifndef __SERVER_H__
#define __SERVER_H__

#include <netinet/in.h>

class Server {
  public:
    // construtor for port
    Server(int port);
    // destructor to destroy socket
    ~Server();

    // public member functions
    void create_server();
    void connect_to_socket();

  private:
    // member variables
    int server_socket;
    int server_port;
    sockaddr_in server_address;

    // private member functions
    void set_socket_options(int options);
    void create_server_socket();
    void create_server_address();
    void bind_address_to_socket();
    void listen_on_socket();
    void handle_accept(int accepted_socket);
    void handle_connections();
};

#endif