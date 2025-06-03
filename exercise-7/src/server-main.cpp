// src/server-main.cpp

/* standard headers */
#include <iostream>

/* user defined headers */
#include "server/server-chat.h"

const int PORT = 8080;

int main() {
  // calling the server to listen through port = PORT
  chat::server::Server chat_server(PORT); 
    // src/server/server-chat.h
}