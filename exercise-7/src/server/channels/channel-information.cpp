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
  This function returns the channel_name value stored in the object
  */
  std::string Channel::get_channel_name() {
    return channel_name_;
  }
  
  // --------------- PUBLIC FUNCTIONS END HERE ---------------
  // --------------- PRIVATE FUNCTIONS START HERE ---------------



  // --------------- PRIVATE FUNCTIONS END HERE ---------------
} // chat::server