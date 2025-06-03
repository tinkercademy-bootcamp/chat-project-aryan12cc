// src/server/command/command.cpp

/* standard headers */
#include <iostream> // std::cout, std::endl

/* user-defined headers */
#include "command.h"

/* namespace for all commands */

namespace chat::server::command {

  /*
  A function to read input from the client and parse it
  for channels / server to act upon
  Returns: bool, signifying whether the parsing was
          successful or not
           std::string, the data that needs to be displayed
  */
  std::pair<bool, std::string> parse_client_command(
    std::string data, /* data sent by the client */
    int client_file_descriptor /* client id for now */
  ) {
    // check if data is empty
    if(data.empty() || data[0] != '/') {
      return std::make_pair(false, "Error: Invalid command");
    }

    std::string command = get_command_input(data);

    return std::make_pair(true, command);
  }

  /*
    This function gets the command part of the input
    The command part is the text just after the starting `/`
  */
  std::string get_command_input(
    std::string data /* the data for which we need to get the command */
  ) {
    // position of the first space in data
    size_t space_pos = data.find(' ');

    std::string command = "";

    // space not present
    if(space_pos == std::string::npos) {
      command = data.substr(1, data.size()); // remove the `/`
    }
    else {
      command = data.substr(1, space_pos); // remove the `/`
    }
    return command;
  }

} // chat::server::commands