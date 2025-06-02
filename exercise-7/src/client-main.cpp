// ./client-main.cpp

/* standard headers */
#include <iostream>

/* user defined headers */
#include "client/client-chat.h"

const int PORT = 8080;

int main() {
  // calling the client to listen through port = PORT
  chat::client::Client chat_client(PORT); // src/client/client-chat.h
}