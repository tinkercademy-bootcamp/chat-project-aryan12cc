// src/server/command/command.h

#ifndef __COMMAND_H__
#define __COMMAND_H__

/* standard headers */
#include <string> // std::string

/* user-defined headers */

/* namespace for all commands */

namespace chat::server::command {

  /*
  Command class containing all the implementation related to the
    commands a client can enter. Currently the commands are:
  1. /leave <channel_id> -- client leaves the channel with channel_id
  2. /join <channel_id> -- client joins the channel with channel_id
  3. /list -- lists all channels according to their id
  4. /message <channel_id> <message> -- client sends message 
                                        to channel with channel_id
  */
  class Command {

    // public functions and variables, accessible by everyone
    public:
      /*
      This function takes the input and the client from which it came from
      Returns: A boolean to check if the input was parsed successfully
              or there was some error
      */
      bool get_input_from_client(
        std::string data, /* data sent by the client */
        int client_file_desciptor /* the file descriptor form which it was 
                                    sent from */
      );
    
    // private functions -- accessible by same class members
    private:

  };
} // chat::server::commands

#endif