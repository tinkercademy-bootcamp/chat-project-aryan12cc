// src/server/command/command.cpp

#include <algorithm>
#include <iostream> 

#include "../../utils.h"
#include "../channels/channel-information.h"
#include "../server-chat.h"
#include "command.h"

/* namespace for all commands */

namespace chat::server::command {

  std::string _execute_create(
    std::string channel_name, int client_file_descriptor) {
    // get the new id of the channel (default = 1)
    int new_id = 1;
    if(!chat::server::all_channels.empty()) {
      int maximum_id = chat::server::all_channels.rbegin()->first;
          // get the last entry in the map (sorted by keys = id)
      new_id = maximum_id + 1;
    }

    // insert the new channel into the all_channels map
    chat::server::all_channels.insert({new_id, 
            chat::server::Channel(new_id, channel_name)});
    
    // return a confirmation message
    spdlog::info("/create by user{}: Channel `{}` created with id = {}", \
      client_file_descriptor, channel_name, new_id);

    std::string result = "Channel `" + channel_name + 
                        "` created with id = " + std::to_string(new_id);
    return result;
  }

  std::string _execute_help(int client_file_descriptor) {
    std::string result = "Commands available:\n";
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

    spdlog::info("/help by user{}: Executed successfully", \
      client_file_descriptor);
    return result;
  }

  std::string _execute_join(
    int client_file_descriptor, long long channel_id) {
    // check if the channel exists
    auto channel_itr = all_channels.find(channel_id);

    std::string result{};

    if(channel_itr == all_channels.end()) {
      spdlog::warn("/join by user{}: Channel {} doesn't exist", \
        client_file_descriptor, channel_id);
      result = "Error: Channel with " + 
              std::to_string(channel_id) + " doesn't exist";
      return result;
    }
    
    // channel object
    Channel &channel_object = channel_itr->second;

    // success
    if(channel_object.add_member(client_file_descriptor)) {
      spdlog::info("/join by user{}: Channel {} successfully joined", \
        client_file_descriptor, channel_id);
      result = "Joined the channel";
      return result;
    }
    // failure (already in the channel)
    spdlog::warn("/join by user{}: User already present in channel {}", \
      client_file_descriptor, channel_id);
    result = "You are already in the channel";
    return result;
  }

  std::string _execute_leave(
    int client_file_descriptor, long long channel_id) {
    // check if the channel exists
    auto channel_itr = all_channels.find(channel_id);
    std::string result{};
    if(channel_itr == all_channels.end()) {
      spdlog::warn("/leave by user{}: Channel {} doesn't exist", \
        client_file_descriptor, channel_id);
      result = "Error: Channel with " + std::to_string(channel_id) + 
              " doesn't exist";
      return result;
    }
    
    // channel object
    Channel &channel_object = channel_itr->second;

    // success
    if(channel_object.remove_member(client_file_descriptor)) {
      spdlog::info("/leave by user{}: Channel {} successfully left", \
        client_file_descriptor, channel_id);
      result = "Exited the channel";
      return result;
    }
    // failure (not present in the channel)
    spdlog::warn("/leave by user{}: User not present in channel {}", \
      client_file_descriptor, channel_id);
    result = "You are not there in the channel";
    return result;
  }

  std::string _execute_list(int client_file_descriptor) {
    std::string result{}; // stores the output to be printed to the client
    
    // Add namespace qualifier to all_channels
    for(auto channel_pair : chat::server::all_channels) {
      // Convert int to string with std::to_string
      result += "Channel id: " + 
                std::to_string(channel_pair.second.channel_id) + "\n";
      result += "Channel name: " + 
                channel_pair.second.get_channel_name() + "\n";
      result += "\n"; // Add blank line between channels
    }
    
    spdlog::info("/list by user{} successfully executed", \
                  client_file_descriptor);
    // Return a message if no channels exist
    if (result.empty()) {
      return "No channels available.";
    }
    
    return result;
  }

  std::string get_command_input(std::string data) {
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

  std::pair<bool, long long> get_next_integer(std::string data) {
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
    return std::make_pair(true, parameter_input);
  }

  std::pair<bool, std::string> get_remaining_string(std::string data) {
    // timming whitespaces at the beginning and end
    data = trim(data);
    if(data.empty()) {
      return std::make_pair(false, "");
    }
    return std::make_pair(true, data);
  }

  std::string parse_client_command(
    std::string data, int client_file_descriptor) {
    // check if data is empty
    data.pop_back(); // remove '\0'
    data = trim(data); // remove whitespaces

    std::string result{};
    if(data.empty() || data[0] != '/') {
      spdlog::warn("Invalid command given by user{}", client_file_descriptor);
      result = "Error: Invalid command";
      return result;
    }

    std::string command = get_command_input(data);

    // parameter associated with the command
    std::string parameters = data.substr(command.size() + 1);

    // calling the corresponding function as the command
    if(command == "create") {
      std::pair<bool, std::string> remaining_text = 
          get_remaining_string(parameters);
      if(remaining_text.first == false) {
        spdlog::warn("/create by user{}: Channel name is empty", \
                    client_file_descriptor);
        result = "Error: Channel name cannot be empty";
        return result;
      }
      return _execute_create(remaining_text.second, 
              client_file_descriptor);
    }
    if(command == "join") {
      // the id of the channel client wants to join
      std::pair<bool, long long> next_parameter = get_next_integer(parameters);
      if(next_parameter.first == false) {
        spdlog::warn("/join by user{}: Channel id is not an integer", \
          client_file_descriptor);
        result = "Error: Channel id should be an integer";
        return result;
      }
      return _execute_join(client_file_descriptor, 
            next_parameter.second);
    }
    if(command == "leave") {
      // the id of the channel client wants to join
      std::pair<bool, long long> next_parameter = get_next_integer(parameters);
      if(next_parameter.first == false) {
        spdlog::warn("/leave by user{}: Channel id is not an integer", \
          client_file_descriptor);
        result = "Error: Channel id should be an integer";
        return result;
      }
      return _execute_leave(client_file_descriptor, 
          next_parameter.second);
    }
    if(command == "help") {
      return _execute_help(client_file_descriptor);
    }
    if(command == "list") {
      return _execute_list(client_file_descriptor);
    }
    
    spdlog::warn("Invalid command given by user{}", client_file_descriptor);
    result = "Error Invalid command";
    return result;
  }

  std::string trim(std::string data) {
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
