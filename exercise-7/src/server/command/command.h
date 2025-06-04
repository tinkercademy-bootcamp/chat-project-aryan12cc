// src/server/command/command.h

#ifndef __COMMAND_H__
#define __COMMAND_H__

/* standard headers */
#include <string> // std::string

/* user-defined headers */


/*
  Command namespace containing all the implementation related to the
    commands a client can enter. Currently the commands are:
  1. /help -- shows the entire list of commands
  2. /join <channel_id> -- client joins the channel with channel_id
  3. /leave <channel_id> -- client leaves the channel with channel_id
  4. /list -- lists all channels according to their id
  5. /message <channel_id> <message> -- client sends message 
                                        to channel with channel_id
*/

namespace chat::server::command {
  // all command executing functions start with _execute

  /*
  This function executes the help command given by the client
  Return: Data in a formatted order
  */
  std::string _execute_help();

  /*
  This function executes the list command given by the client
  Return: Data in a formatted order
  */
  std::string _execute_list();

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
    This function gets the command part of the input.
    For example, `/message yes` will make this command
    return message
  */
  std::string get_command_input(
    std::string data /* data for which the command needs 
                    to get extracted */
  );
      
} // chat::server::command

#endif
