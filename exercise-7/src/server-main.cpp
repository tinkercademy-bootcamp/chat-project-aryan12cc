// ./server-main.cpp

/* standard headers */
#include <iostream>

/* user defined headers */
#include "server/server-chat.h"

const int PORT = 8080;

int main() {
  chat::server::Server chat_server(PORT); // calling the server to listen through port = PORT
}