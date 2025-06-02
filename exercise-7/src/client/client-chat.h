// ./client/client-chat.h

#ifndef __CLIENT_CHAT_H__
#define __CLIENT_CHAT_H__

/* namespace for all client related operations */
namespace chat::client { 

  /* 
  Client() class containing all client related operations:
  - Username
  - List of channels currently present in
  (Others may be added later)
  */

  class Client {
    
    // public functions and variables, accessible by everyone
    public:

      /* Constructor to initialize member variables */
      Client();

      /* Destructor to ensure cleanup of variables */
      ~Client();
    
    // private functions and variables, only accessible by functions and 
    // variables of the same class
    private:

      // member functions

      // member variables

  };
  
}

#endif