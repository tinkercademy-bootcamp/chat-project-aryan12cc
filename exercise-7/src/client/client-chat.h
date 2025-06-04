// src/client/client-chat.h

#ifndef CLIENT_CHAT_H_
#define CLIENT_CHAT_H_

#include <netinet/in.h>

/* namespace for all client related operations */
namespace chat::client { 

  /* 
  Client() class containing all client related operations:
  - Username
  - List of channels currently present in
  (Others may be added later)
  */

  class Client {
    
    public:

      Client(
        int port /* the port through which client will connect to server */
      );

      ~Client() = default;
    
    private:
      
      /* Function to setup the socket of the client 
      to be able to connect to the server */
      void client_setup_socket(
        int port /* the port to which the client needs to connect */
      );

      /* Function to communicate with the server */
      void communication_loop();

      /* Function to connect the client to the server */
      void connect_to_server();

      /* Function to read message sent from server */
      void read_from_server();

      /* Function to read input from standard input */
      void read_from_stdin();

      int client_socket_fd_; // file descriptor of the client to connect to
                            // the server
      sockaddr_in server_address_; // sockaddr_in struct to store the details
                            // of the ip address and port of the server
  };
  
}

#endif
