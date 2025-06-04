// src/client-main.cpp

#include "client/client-chat.h"
#include "utils.h"

// The port through which the client will connect to the server
// This is the same port used by the server to listen to
// connection requests
const int CONNECTION_PORT = 8080;

int main() {
  chat::client::Client chat_client(CONNECTION_PORT); 
}
