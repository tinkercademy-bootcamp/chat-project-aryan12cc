// src/client-main.cpp

/* standard headers */

/* user defined headers */
#include "client/client-chat.h"

// The port through which the client will connect to the server
// This is the same port used by the server to listen to
// connection requests
const int PORT = 8080;

int main() {
  // Create a client object called chat_client that calls the
  // parameterized constructor with port = PORT, signifying to
  // connect to the server on that specific port
  chat::client::Client chat_client(PORT); 
    // src/client/client-chat.h
}