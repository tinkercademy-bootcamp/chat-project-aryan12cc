// src/server/server-chat.h

#ifndef SERVER_CHAT_H_
#define SERVER_CHAT_H_

#include <string>
#include <map>

#include "channels/channel-information.h"

/* namespace for all server related operations */
namespace chat::server { 

  /*
  Maintaining an unordered map with key = channel_id
  and value = the channel object with the corresponding channel_id
  */
  extern std::map<int, Channel> all_channels;

  /* 
  Server() class containing all server related operations:
  - The data stored by Server() class
  - Setting up sockets
  - Handling new connections
  - Handling new data
  - Getting operations from the client and executing them
  */

  class Server {
    
    public:

      Server(
        int port /* the port through which server will listen */
      );

      ~Server() = default;

    private:

      /*
      This function accepts an incoming request from the client side to
      connect to the server
      Returns the new connection socket
      */
      int accept_incoming_request();

      /*
      Close the connection between client and server gracefully after the
      client has gone offline
      */
      void close_client_connection(
        int file_descriptor /* the file descriptor from which the connection 
                            needs to be closed */
      );

      /*
      This function handles the interaction loop with the clients
      and gives / executes necessary instructions to the corresponding
      channel
      */
     void communication_loop();

      /*
      The function creates a server socket tied to the port as given
      in the parameter
      */
      void create_server_socket(
        int port /* the port through which server will listen */
      );

      /*
      The function is used when the server is ready to accept connections
      from clients. It initializes the epoll file descriptors to hear
      from other file descriptors.
      */
      void initialize_epoll();

      /*
      Function to read and parse the input data sent 
        from the client to the server
      */
      void parse_input_from_client(
        int file_descriptor /* The file descriptor to read the input from */
      );

      /*
      Function to write output data from the server to a specific client
      */
      void write_data_to_client(
        int file_descriptor, /* The file descriptor to write the output to */
        std::string output /* The output the be written */
      );

      int epoll_fd_; // file descriptor for epoll used to monitor multiple
                    // sockets

      int listen_socket_fd_; // file descriptor for the server's listening
                            // socket
  };
  
}

#endif
