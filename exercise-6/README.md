# Exercise 6

**Update this README with your answers to the questions below.**

## Adding Third Party Libraries or Source Code to Your Project

- There is a new file `src/spdlog-hello-world-main.cc`
- It uses the spdlog and fmt libraries. 
  [More info here](https://github.com/gabime/spdlog) - Fast C++ logging 
  library with various sink types and formatting options
- How do you compile this file using the `g++` CLI?
  - Installed only the header files from the link given above and added them to the `src/` folder.
  - Tried running a dummy code `try.cc`, and had to compile with the following line: `g++ src/try.cc -I src` when in `exercise-6/` folder.
  - In general, we need to add `-I <path to header>` in our compilation command.
- What do you need to change in your makefile to use this library?
  - The current makefile doesn't need any changes to use the library since it recursively finds all directories and adds the `-I` flag before the directory.
  - In case the makefile didn't have the command, we can have a variable containing all the paths to third-party directories, and add `-I` flag before the paths.
- How many different ways can this library be added into your project?
  - Install directly on the machine (ssh server in this case). Haven't tried, but as per the README of the Github repository: `sudo apt install libspdlog-dev`
  - Install the header-only version (copying the `include` folder) to the repository (`./exercise-6` in this case). Then add `-I` flag while manually compiling or compile using Make.
  - Install the compiled version by cloning the repository and using `cmake` on it. Then we can link the library via Make or g++ CLI.
  - **Note:** These only contain the ways mentioned in the above Github repository. May not be all the ways to add the library to the project.
- What are the tradeoffs in the different ways?
  - Installing directly on the machine is the easiest to setup but it is upto the developers of the third party libraries to ensure that the libraries are upto date with the package managers. Thus, the versions may be outdated which may lead to errors bsaed on some functionality being missing. Furthermore, it will be computer specific, depening on the package manager of the computer. For example, if there is a computer with `brew`, while another with `apt`, and the developer of the third-party library has different versions for `brew` and `apt`, then it will be an issue.
  - Header only version ensures that the setup still remains easy while also portable. Although, there will be a huge increase in the compile time as it is recompiled each time.
  - Installing compiled versions will give a huge boost to the compilation time but it is very delicate, in the sense that the Make files need to be correct and if they aren't then it may be a hassle to compile the project. That being said, bigger projects already have this figured usually, so this should be recommended for bigger projects.
- Why are there so many different ways to do it?
  - C++ historically never has had a package manager. Furthermore, based on the tradeoffs, it depends on the developer to select which way is the best for compiling and running the application in the bigger world, and hence, there are many different ways to do it, each with their own set of pros and cons.
  
## Static Linking vs Dynamic Linking

- What are the differences between static linking and dynamic linking?
  - **Static Linking:** The libraries linked are embedded directly into the executable of the program at linking time.
  - **Dynamic Linking:** The executable contains references to the shared code, but not the actual code. The shared libraries are linked at runtime instead of linking time.
- What are the tradeoffs?
  - In static linking, only the executable needs to be run, without having access to the other library files. Static linking will have a larger executable because of the linking of libraries. Furthermore, if different executables use the same library, it's a waste of memory.
  - Dynamic linking has a much smaller executable file compared to static linking because of the linked libraries. Furthermore, if a single library gets an update, the entire system doesn't need to be updated -- the library can get updated and it will have effects over the entire system. However, uses also need to install that they have the correct dependencies (library versions) to efficiently compile / run the code.
- How do you enable static linking or dynamic linking in your makefile?
  - For dynamic linking, we may change the variable `LDFLAGS` to include all the libraries. By default, this does dynamic linking.
  - For static linking, we need to add the `-static` flag.

## Git Clone and Building from Source

- Where is `g++` looking for the include files and library files?
  - `#include <header.h>` searches in the system include paths
  - `#include "header.h"` searches in the local directory first, and then the system include paths
  - List of include files:
    - `/usr/lib/gcc/aarch64-linux-gnu/14/include`
    - `/usr/local/include`
    - `/usr/include/aarch64-linux-gnu`
    - `/usr/include`
    - Directories specified with `-I` flag
  - List of library files:
    - `libraries: =/usr/lib/gcc/aarch64-linux-gnu/14/:/usr/lib/gcc/aarch64-linux-gnu/14/../../../../aarch64-linux-gnu/lib/aarch64-linux-gnu/14/:/usr/lib/gcc/aarch64-linux-gnu/14/../../../../aarch64-linux-gnu/lib/aarch64-linux-gnu/:/usr/lib/gcc/aarch64-linux-gnu/14/../../../../aarch64-linux-gnu/lib/../lib/:/usr/lib/gcc/aarch64-linux-gnu/14/../../../aarch64-linux-gnu/14/:/usr/lib/gcc/aarch64-linux-gnu/14/../../../aarch64-linux-gnu/:/usr/lib/gcc/aarch64-linux-gnu/14/../../../../lib/:/lib/aarch64-linux-gnu/14/:/lib/aarch64-linux-gnu/:/lib/../lib/:/usr/lib/aarch64-linux-gnu/14/:/usr/lib/aarch64-linux-gnu/:/usr/lib/../lib/:/usr/lib/gcc/aarch64-linux-gnu/14/../../../../aarch64-linux-gnu/lib/:/usr/lib/gcc/aarch64-linux-gnu/14/../../../:/lib/:/usr/lib/`
    - Directories specified with `-L` flag

- How do you find out?
  - Include paths: `g++ -v -x c -E /dev/null`
  - Library paths: `g++ -print-search-dirs`

## C++ Package Managers

- Why are there so many C++ package managers?
  - There are many C++ package managers because there is no "official" package manager. Furthermore, C++ is used for several different purposes (low latency, embedded systems etc.) and every project needs to be compiled for their own set of requirements of computer architecture.
- Which one is the best one?
  - There are different package managers for different target projects, depending on the project requirements. No package manager is the "best one".  
- Which are the most notable ways to manage the compilation of C++ projects?
  - Make
  - CMake