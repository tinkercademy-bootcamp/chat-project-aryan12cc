// src/server-main.cpp

#include "server/server-chat.h"
#include "utils.h"

// The port through which the server will listen to
// connection requests from the client
const int LISTENING_PORT = 8080;

int main() {
  chat::server::Server chat_server(LISTENING_PORT); 
}
