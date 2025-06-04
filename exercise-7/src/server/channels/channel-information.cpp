// src/server/channels/channel-information.cpp

/* standard headers */
#include <string>

/* user-defined headers */
#include "channel-information.h"

namespace chat::server {
  // --------------- PUBLIC FUNCTIONS START HERE ---------------

  Channel::Channel(int id, std::string name) {
    channel_id = id;
    channel_name_ = name;
    channel_members_ = {};
    channel_admins_ = {};
  }

  bool Channel::add_member(int client_file_descriptor) {
    if(channel_members_.find(client_file_descriptor)
        != channel_members_.end()) {
          return false;
    }
    channel_members_.insert(client_file_descriptor);
    return true;
  }

  std::string Channel::get_channel_name() {
    return channel_name_;
  }
  
  // --------------- PUBLIC FUNCTIONS END HERE ---------------
  // --------------- PRIVATE FUNCTIONS START HERE ---------------



  // --------------- PRIVATE FUNCTIONS END HERE ---------------
} // chat::server
