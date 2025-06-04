// src/server/channels/channel-information.h

#ifndef __CHANNEL_INFORMATION_H__
#define __CHANNEL_INFORMATION_H__

/* standard headers */
#include <string> // std::string
#include <vector> // std::vector

/* user-defined headers */
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
        int id, /* stores the channel id*/
        std::string name /* stores the channel name */
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
      std::vector<client::Client> channel_members_; // list of all clients
        // that are the members of the channel
      std::vector<client::Client> channel_admins_; // list of all clients
        // that are the admins of the channel
  };
      
} // chat::server

#endif
