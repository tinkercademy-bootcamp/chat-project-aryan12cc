#include <arpa/inet.h>
#include <iostream>
#include <netinet/in.h>
#include <netdb.h> // for hostname
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
  // #Question - are these the same type?
  // No -- message is a std::string, while "Hello from client" is a char* (array of characters, also known as a cstring)
  std::string message = "";
  if(argc >= 2) {
    for(int i = 1; i < argc; i++) {
      message += argv[i]; // add argument (word)
      if(i != argc - 1) {
        message += " "; // add space if it is not the last word
      }
    }
  }
  else {
    message = "Hello from client!";
  }
  const int kPort = 35000;
  // Change the server address below to another server address (eg. 13.204.12.159 to access Arya's server)
  // Ensure client and server port is the same, as data is transferred to a combination of IP and port (<IP>:<port>)
  
  // IPv4 server address
  // const std::string kServerAddress = "15.207.74.244";

  // IPv6 server address
  // const std::string kServerAddress = "0000:0000:0000:0000:0000:ffff:0fcf:4af4";

  // Get host by name (connect by hostname)
  std::string hostName = "ip-172-31-21-18";
  // Using addrinfo for ip by hostname
  addrinfo hints{};
  addrinfo* res{};
  hints.ai_socktype = SOCK_STREAM; // TCP connections basically
  hints.ai_family = AF_INET; // or AF_INET6

  int s = getaddrinfo(hostName.c_str(), std::to_string(kPort).c_str(), &hints, &res);
  if(s != 0) {
    std::cout << "Error:" << gai_strerror(s) << std::endl;
    return -1;
  }
  
  sockaddr_in address; // IPv4
  // sockaddr_in6 address; // IPv6
  const int kBufferSize = 1024;
  char buffer[kBufferSize] = {0};
  // Creating socket file descriptor
  int my_sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
  // int my_sock = socket(AF_INET, SOCK_STREAM, 0); // IPv4
  // int my_sock = socket(AF_INET6, SOCK_STREAM, 0); // IPv6
  if (my_sock < 0) {
    std::cerr << "Socket creation error\n";
    return -1;
  }
  address.sin_family = AF_INET; // IPv4
  // address.sin6_family = AF_INET6; // IPv6
  address.sin_port = htons(kPort); // IPv4
  // address.sin6_port = htons(kPort); // IPv6
  // Convert IPv4 and IPv6 addresses from text to binary form
  // if (inet_pton(AF_INET, IPBuffer.c_str(), &address.sin_addr) <= 0) { // IPv4 -- by host
  // if (inet_pton(AF_INET, kServerAddress.c_str(), &address.sin_addr) <= 0) { // IPv4
  // if (inet_pton(AF_INET6, kServerAddress.c_str(), &address.sin6_addr) <= 0) { // IPv6
  //   std::cerr << "Invalid address/ Address not supported\n";
  //   return -1;
  // }
  // Connect to the server
  // if (connect(my_sock, (sockaddr *)&address, sizeof(address)) < 0) { // for IP connections
  if(connect(my_sock, res->ai_addr, res->ai_addrlen) < 0) {
    std::cerr << "Connection Failed\n";
    return -1;
  }
  // Send message
  send(my_sock, message.c_str(), message.size(), 0);
  std::cout << "Sent: " << message << "\n";
  // Wait for reply
  ssize_t read_size = read(my_sock, buffer, kBufferSize);
  std::cout << "Received: " << buffer << "\n";
  // Close the socket
  close(my_sock);
  return 0;
}