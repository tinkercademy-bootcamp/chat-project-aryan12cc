# Exercise 4

**Update this README with your answers to the questions below.**

## Learning Multi-File C++ Projects

- Move code that can be shared between `tcp_echo_server.cc` and 
  `tcp_echo_client.cc` to separate `.h` and `.cc` files
  - Updated `src/` folder.
- How would you compile from the command line?
  - From `./exercise-4` run the following two commands:
    - `g++ -std=c++23 src/tcp_echo_server.cpp src/net_operations/net_operations.cpp -o build/server.out`
    - `g++ -std=c++23 src/tcp_echo_client.cpp src/net_operations/net_operations.cpp -o build/client.out`
  - The executables will be in the `build` directory
    - The server executable will be `build/server.out`
    - The client executable will be `build/client.out`
- How would you compile using make?
  - Updated Makefile. Notably, declared another variable called `COMMON_FILES` which contains `src/net_operations/net_operations.cpp`.
- How would you compile using VS Code?
  - Add a task in the `.vscode` folder at the root directory of the project. This can be done by creating a `tasks.json` file within the `.vscode` folder.
  - The tasks will contain arguments to compile the programs of client and server.
  - Command + Shift + B will execute the tasks, thus compiling the programs.

### Compiling vs Linking

- What is the difference between compiling and linking in C++?
  - Compiler compiles the individual source files to their corresponding object files
  - Linker takes all the object files and combines them into one final executable
- What is the difference between creating an executable and creating a library?
  - An executable is a single binary file that can be run.
  - A library is a collection of precompiled code which cannot be run individually. It is meant for re-use in other programs.
- How do you compile a library, and then use that library to compile an executable?
  - Compile the `.cpp` files to object files using `-c` flag. We can use the `ar` command to create a static library from the `.o` files, and use the `-L.` to check the current directory and `-l<libname>` flag to check for the respective library (for example, `-lfft` for `libfft.a`).

### Reminder 
[Quickstart tutorial to make](https://makefiletutorial.com/) - Learn make 
fundamentals with practical examples and common patterns.

## Experiments in Performance

- Is it better to have many small files spread across many directories, or
  a few large files across fewer directories?
- Is there a difference in compilation time between the two?
- How can you assess performance other than compilation speed?