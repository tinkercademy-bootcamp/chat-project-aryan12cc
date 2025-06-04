// src/server/command/command.h

#ifndef __COMMAND_H__
#define __COMMAND_H__

/* standard headers */
#include <string> // std::string

/* user-defined headers */


/*
  Command namespace containing all the implementation related to the
    commands a client can enter. Currently the commands are:
  1. /create <channel_name> -- creates a channel with name <channel_name>
  2. /help -- shows the entire list of commands
  3. /join <channel_id> -- client joins the channel with channel_id
  4. /leave <channel_id> -- client leaves the channel with channel_id
  5. /list -- lists all channels according to their id
  6. /message <channel_id> <message> -- client sends message 
                                        to channel with channel_id
*/

namespace chat::server::command {
  // all command executing functions start with _execute

  /*
  This function executes the create command given by the client
  Return: boolean to check whether the channel has been created.
          std::string for data in a formatted order
  */
  std::pair<bool, std::string> _execute_create(
    std::string channel_name /* name of the channel */
  );
  /*
  This function executes the help command given by the client
  Return: Data in a formatted order
  */
  std::string _execute_help();

  /*
  This function executes the join command given by the client
  Returns: pair of bool and data to be displayed to the client
    bool signifies whether the client could join the channel
  */
  std::pair<bool, std::string> _execute_join(
    int client_file_descriptor, /* client that wants to join */
    long long channel_id /* id of the channel client is requesting to join */
  );

  /*
  This function executes the list command given by the client
  Return: Data in a formatted order
  */
  std::string _execute_list();

  /*
    This function gets the command part of the input.
    For example, `/message yes` will make this command
    return message
  */
  std::string get_command_input(
    std::string data /* data for which the command needs 
                    to get extracted */
  );

  /*
    This function gets ensures that the next "word" in the string
    is an integer and returns that
    Returns: std::pair<bool, long long>
      - bool to check whether the next "word" is an integer
      - long long contains the integer
  */
  std::pair<bool, long long> get_next_integer(
    std::string data /* data upon which the checking happens */
  );

  /*
    This function gets the remaining text of the string
    Returns: std::pair<bool, std::string>
      - bool to check whether the remaining text actually exists
      - std::string contains the remaining text
  */
  std::pair<bool, std::string> get_remaining_string(
    std::string data /* data upon which the checking happens */
  );

  /*
  This function takes the input and the client from which it came from
  Returns: A pair of boolean and std::string
    A boolean to check if the input was parsed successfully
      or there was some error
    std::string contains the formatted data to be shown to the client 
  */
  std::pair<bool, std::string> parse_client_command(
    std::string data, /* data sent by the client */
    int client_file_descriptor /* the file descriptor from which it was 
                                sent */
  );

  /*
    Utility function to trim whitespace from beginning and end of a string
  */
  std::string trim(
    std::string data /* string to be trimmed */
  );
      
} // chat::server::command

#endif
