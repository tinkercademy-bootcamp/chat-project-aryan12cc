// src/server-main.cpp

/* standard headers */

/* user defined headers */
#include "server/server-chat.h"

// The port through which the server will listen to
// connection requests from the client
const int LISTENING_PORT = 8080;

int main() {
  // calling the server to listen through a specified port
  // by creating a server object named chat_server
  chat::server::Server chat_server(LISTENING_PORT); 
    // src/server/server-chat.h
}