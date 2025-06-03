// src/utils.h

// header guard for utils.h. Ensures that the header is included atmost
// once while compiling
#ifndef UTILS_H
#define UTILS_H

/* standard headers */
#include <concepts>
#include <cstring> // Functions: std::memset
#include <iostream> // Functions: std::cerr
#include <string>

/* user-defined headers */

namespace chat {

  // Constant buffer size to be used throughout the program to ensure that
  // there will only be a single buffer size globally and hence, the code
  // will be less error prone to buffer issues while transmitting messages
  // from one host to another
  constexpr int BUF_SIZE = 1024;

  // Template to check for errors. If the error message check passes, the
  // error message is printed and the program is terminated
  // The failure condition should either be an integer or a boolean
  //    and the result of the condition should be called here
  //    for example, if you don't want positive to be <= 0, you should call
  //    check_error(positive <= 0, "Positive cannot be non-positive")
  // The error message should be convertible to a string
  template <typename T, typename S> 
  requires (std::is_integral_v<T> || std::is_same_v<T, bool>) &&
         std::convertible_to<S, std::string>
  void check_error(
    T failure_condition, /* the failure condition */
    S error_message /* the error message to be printed */
  ) {
    if(failure_condition) {
      std::cerr << error_message << "\n";
      exit(EXIT_FAILURE);
    }
  }

  // Function to set the buffer size to 0. Takes in the start pointer as
  // the parameter and sets all 1024 bytes after the start pointer as '\0'
  inline void clear_buffer(char* buffer) {
    std::memset(buffer, 0, BUF_SIZE);
  }

} // namespace chat

#endif // UTILS_H
