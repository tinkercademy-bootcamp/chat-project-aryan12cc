// ./server/server-chat.h

#ifndef __SERVER_CHAT_H__
#define __SERVER_CHAT_H__

/* namespace for all server related operations */
namespace chat::server { 

  /* 
  Server() class containing all server related operations:
  - The data stored by Server() class
  - Setting up sockets
  - Handling new connections
  - Handling new data
  - Getting operations from the client and executing them
  */

  class Server {
    
    // public functions and variables, accessible by everyone
    public:

      /* Constructor to initialize member variables */
      Server(
        int port /* the port through which server will listen */
      );

      /* Destructor to ensure cleanup of sockets */
      ~Server();
    
    // private functions and variables, only accessible by functions and 
    // variables of the same class
    private:

      // member functions

      /*
      The function creates a server socket tied to the port as given
      in the parameter
      */
      void create_server_socket(
        int port /* the port through which server will listen */
      );

      // member variables
      
      int listen_socket_fd; // file descriptor for the server's listening
                            // socket
  };
  
}

#endif