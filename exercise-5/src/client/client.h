#ifndef __CLIENT_H__
#define __CLIENT_H__

#include <netinet/in.h>
#include <string>

class Client {

  public:
    // constructors / destructors
    Client(); // constructor to create socket
    ~Client(); // destructor to destroy socket

    // public member functions
    void connect_server(const std::string &server_ip, int port);
    void send_message(const std::string &message);

  private:
    // member variables
    int client_socket;
    sockaddr_in server_address;

    // member functions
    sockaddr_in create_server_address(const std::string &server_ip, int port);
    void connect_to_server(int client_socket, sockaddr_in &server_address);
    void send_and_receive_message(int socket, const std::string &message);
};

#endif