// src/server/command/command.cpp

/* standard headers */
#include <algorithm>
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
      "/create <channel_name>",
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
      result += "Channel id: " + 
                std::to_string(channel_pair.second.channel_id) + "\n";
      result += "Channel name: " + 
                channel_pair.second.get_channel_name() + "\n";
      result += "\n"; // Add blank line between channels for readability
    }
    
    // Return a helpful message if no channels exist
    if (result.empty()) {
      return "No channels available.";
    }
    
    return result;
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

  /*
  A function to get the parameters of the next word (integer)
  of the command given by the client
  Returns: The next word, ensuring its an integer (bool takes
  care of that)
  */
  std::pair<bool, long long> get_next_integer(
    std::string data /* data sent by the client after the command */
  ) {
    // timming whitespaces at the beginning and end
    data = trim(data);
    if(data.empty()) {
      return std::make_pair(false, -1);
    }
    constexpr long long maximum_parameter_value = 100'000'000'000'000'000LL;
    // find first position of space
    size_t space_pos = data.find(' ');
    if(space_pos == std::string::npos) {
      space_pos = data.size();
    }
    long long parameter_input = 0;
    for(size_t i = 0; i < space_pos; i++) {
      if(data[i] < '0' || data[i] > '9') { 
        // check if the character is a number
        return std::make_pair(false, -1);
      }
      // add the digit to the input
      parameter_input = (parameter_input * 10) + data[i] - '0';
      if(parameter_input >= maximum_parameter_value) { // parameter_input
        parameter_input = maximum_parameter_value;
      }
    }
    return std::make_pair(true, maximum_parameter_value);
  }

  /*
  A function to get the remaining text of the string
  Returns: The remaining text, ensuring its not empty (bool takes
  care of that)
  */
  std::pair<bool, std::string> get_remaining_string(
    std::string data /* data sent by the client after the command */
  ) {
    // timming whitespaces at the beginning and end
    data = trim(data);
    if(data.empty()) {
      return std::make_pair(false, "");
    }
    return std::make_pair(true, data);
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
    data.pop_back(); // remove '\0'
    data = trim(data); // remove whitespaces
    if(data.empty() || data[0] != '/') {
      return std::make_pair(false, "Error: Invalid command");
    }

    std::string command = get_command_input(data);

    // parameter associated with the command
    std::string parameters = data.substr(command.size() + 1);

    // calling the corresponding function as the command
    if(command == "create") {
      std::pair<bool, std::string> remaining_text = 
          get_remaining_string(parameters);
    }
    if(command == "help") {
      return std::make_pair(true, _execute_help());
    }
    if(command == "list") {
      return std::make_pair(true, _execute_list());
    }

    return std::make_pair(false, "Error: Invalid command");
  }

  /*
    Utility function to trim whitespace from beginning and end of a string
  */
  std::string trim(
    std::string data /* string to be trimmed */
  ) {
    // If string is empty, return it
    if(data.empty()) {
      return data;
    }
    
    auto front = std::find_if_not(data.begin(), 
                data.end(), ::isspace); // first character that
                                        // is not a space
    auto back = std::find_if_not(data.rbegin(), 
                data.rend(), ::isspace).base();
                                        // last character that
                                        // is not a space + 1
    if (front >= back) return "";
    return std::string(front, back);
  }

} // chat::server::command
