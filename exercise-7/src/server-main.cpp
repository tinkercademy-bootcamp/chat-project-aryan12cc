// src/server-main.cpp

#include "server/server-chat.h"
#include "utils.h"

// The port through which the server will listen to
// connection requests from the client
const int LISTENING_PORT = 8080;

int main() {
  #ifdef LOG_FILE
    auto new_logger = spdlog::basic_logger_mt("server-logs", LOG_FILE, true);
  #else
    auto new_logger = spdlog::basic_logger_mt("server-logs", "logs/server-log.log", true);
  #endif
  spdlog::set_default_logger(new_logger);
  spdlog::set_level(spdlog::level::debug);
  spdlog::flush_on(spdlog::level::debug);
  chat::server::Server chat_server(LISTENING_PORT); 
}
