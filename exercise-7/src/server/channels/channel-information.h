// src/server/channels/channel-information.h

#ifndef CHANNEL_INFORMATION_H_
#define CHANNEL_INFORMATION_H_

#include <map>
#include <set>
#include <string>
#include <vector>

#include "../../client/client-chat.h"

namespace chat::server {

  /*
  Channel class containing all the implementation 
    related to a particular channel
  These include:
  - channel id
  - channel name
  - members of the channel
  - admins of he channel
  */
  class Channel {

    // public functions and variables, accessible by everyone
    public:

      // member functions
      
      /*
        Paramterized constructor getting the values of the variables
      */
      Channel(
        int id, /* stores the channel id */
        std::string name /* stores the channel name */
      );

      /*
        Function to add a member (client) to the channel
      */
      bool add_member(
        int client_file_descriptor /* the member that wants to join */
      );

      /*
        Function to return the channel name in the object
      */
      std::string get_channel_name();

      // member variables

      int channel_id; // stores the id of the channel
        // The id is assigned when the and is unique

    // private functions and variables, only accessible by functions and 
    // variables of the same class
    private:

      // member functions

      // member variables

      std::string channel_name_; // stores the name of
        // the channel as given by the user on creation
      std::set<int> channel_members_; // list of all clients
        // that are the members of the channel
      std::set<int> channel_admins_; // list of all clients
        // that are the admins of the channel
  };
      
} // chat::server

#endif
