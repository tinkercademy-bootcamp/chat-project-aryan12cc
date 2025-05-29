#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "net/chat-sockets.h"
#include "server/server.h"
#include "utils.h"

int main() {
  namespace ttc = tt::chat;
  const int kPort = 8080;

  Server thisServer = Server(kPort);
  thisServer.create_server();
  thisServer.connect_to_socket();

  return 0;
}
