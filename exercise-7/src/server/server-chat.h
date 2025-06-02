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
      Server(); // constructor to initialize member variables
      ~Server(); // destructor to ensure cleanup of sockets
    
    // private functions and variables, only accessible by functions and 
    // variables of the same class
    private:
      int server_socket_fd; // file descriptor for the server's listening
                            // socket
  };
  
}

#endif