// src/server/channels/channel-information.cpp

/* standard headers */
#include <string>

/* user-defined headers */
#include "channel-information.h"

namespace chat::server {
  // --------------- PUBLIC FUNCTIONS START HERE ---------------

  /*
    Parameterized constructor to store the name of the channel
  */
  Channel::Channel(
    int id, /* stores the channel id */
    std::string name /* name of the channel */
  ) {
    channel_id = id;
    channel_name_ = name;
    channel_members_ = {};
    channel_admins_ = {};
  }

  /*
  This function adds a member to the channel if the member is not present
  */
  bool Channel::add_member(
    int client_file_descriptor /* file descriptor fo the client who wants
                                  to join the channel */
  ) {
    if(channel_members_.find(client_file_descriptor)
        != channel_members_.end()) {
          return false;
    }
    channel_members_.insert(client_file_descriptor);
    return true;
  }

  /*
  This function returns the channel_name value stored in the object
  */
  std::string Channel::get_channel_name() {
    return channel_name_;
  }
  
  // --------------- PUBLIC FUNCTIONS END HERE ---------------
  // --------------- PRIVATE FUNCTIONS START HERE ---------------



  // --------------- PRIVATE FUNCTIONS END HERE ---------------
} // chat::server
