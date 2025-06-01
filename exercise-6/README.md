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
- How do you enable static linking or dynamic linking in your makefile?

## Git Clone and Building from Source

- Where is `g++` looking for the include files and library files?
- How do you find out?

## C++ Package Managers

- Why are there so many C++ package managers?
- Which one is the best one?
- Which are the most notable ways to manage the compilation of C++ projects?