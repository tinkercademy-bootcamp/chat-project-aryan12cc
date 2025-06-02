// ./utils.h

#ifndef UTILS_H
#define UTILS_H

#include <iostream>

namespace chat {

  // template to check error and if it occurs, print out the error message
  template <typename T, typename S> void check_error(
    T failure_condition, /* the failure condition */
    S error_message /* the error message to be printed */
  ) {
    if(failure_condition) {
      std::cerr << error_message << "\n";
      exit(EXIT_FAILURE);
    }
}

} // namespace chat

#endif // UTILS_H
