// src/server/command/command.cpp

/* standard headers */
#include <iostream> // std::cout, std::endl

/* user-defined headers */
#include "../channels/channel-information.h"
#include "../server-chat.h"
#include "command.h"

/* namespace for all commands */

namespace chat::server::command {

  /*
  A function to execute the /help command given by the client
  Returns: Data that is displayed to the client
  */
  std::string _execute_help() {
    std::string result = "Results of /help:\n";
    result += "Commands available:\n";
    std::vector<std::string> command_list = {
      "/help",
      "/join <channel_id>",
      "/leave <channel_id>",
      "/list",
      "/message <channel_id> <message>"
    };

    for(auto &command: command_list) {
      result += "\t" + command + "\n";
    }
    return result;
  }

  /*
  A function to execute the /list command given by the client
  Returns: Data that is displayed to the client
  */
  std::string _execute_list() {
    std::string result = ""; // stores the output to be printed to the client
    
    // Add namespace qualifier to all_channels
    for(auto channel_pair : chat::server::all_channels) {
      // Convert int to string with std::to_string
      result += "Channel id: " + std::to_string(channel_pair.second.channel_id) + "\n";
      result += "Channel name: " + channel_pair.second.get_channel_name() + "\n";
      result += "\n"; // Add blank line between channels for readability
    }
    
    // Return a helpful message if no channels exist
    if (result.empty()) {
      return "No channels available.";
    }
    
    return result;
  }

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
    data = data.substr(0, data.size() - 1); // remove the null character
    if(data.empty() || data[0] != '/') {
      return std::make_pair(false, "Error: Invalid command");
    }

    std::string command = get_command_input(data);

    // calling the corresponding function as the command
    if(command == "help") {
      return std::make_pair(true, _execute_help());
    }
    if(command == "list") {
      return std::make_pair(true, _execute_list());
    }

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
      command = data.substr(1); // remove the `/`
    }
    else {
      command = data.substr(1, space_pos - 1); // remove the `/`
    }
    return command;
  }

} // chat::server::command
