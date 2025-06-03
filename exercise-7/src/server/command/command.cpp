// src/server/command/command.cpp

/* standard headers */

/* user-defined headers */
#include "command.h"

/* namespace for all commands */

namespace chat::server::command {
  
  /*
  A function to read input from the client and parse it
  for channels / server to act upon
  Returns: bool, signifying whether the parsing was
          successful or not
  */
  bool Command::get_input_from_client(
    std::string data, /* data sent by the client */
    int client_file_descriptor /* client id for now */
  ) {
    return true;
  }
} // chat::server::commands