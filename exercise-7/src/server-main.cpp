// src/server-main.cpp

#include "server/server-chat.h"
#include "utils.h"

// The port through which the server will listen to
// connection requests from the client
const int LISTENING_PORT = 8080;

int main() {
  auto new_logger = spdlog::basic_logger_mt("new_default_logger", "logs/server-log.txt", true);
  spdlog::set_default_logger(new_logger);
  chat::server::Server chat_server(LISTENING_PORT); 
}
