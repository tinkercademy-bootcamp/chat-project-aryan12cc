# Exercise 1

**Update this README with your answers to the questions below.**

## Learning How to Learn

- Answer the following questions in this file and commit and push your changes.
- Bonus sections are more difficult and optional.
- How can you find the information required to complete these tasks?
  - Google / Stack Overflow
  - Official C++ Documentation (man pages for example)
- How can you tell if the source of your information is good?
  - Good answers on Stack Overflow have a lot of positive votes. Furthermore, for Google, credible answers / web pages have a lot of references, hence, are one of the top links.
  - Official C++ documentation is written by the team that works on releasing new versions of C++ themselves.
- How would you define "good" in this situation?
  - Answers that have credibility from other users / people.

## Learn Basics of g++ CLI

- Compile the TCP client and server using `g++` from command line.
  - `g++ -std=c++23 tcp_echo_client.cc -o client.out`
  - `g++ -std=c++23 tcp_echo_server.cc -o server.out`
- What are the most important command line arguments to learn for `g++`?
  - `-std` allows you to select the version of C++
  - `-o <filename>` allows you to name the executable to something other than `a.out`, which may be helpful while compiling different programs together in the same directory
  - `-O2 / -O3 / -Ofast` allows you to direct the compiler to make optimizations, although it may take longer to compile. Furthermore, `Ofast` enables unsafe optimizations.
- What is the difference between debug vs release versions?
  - In the debug version, the developer ususally wants to go through what the code does in particular scenarios. Thus, a detailed debug report without any optimizations are used. Hence, the debug version can be significantly slower than the release version.
  - In the release version, the developer is putting out the code to the public, and hence, all optimizations are enabled for faster runtime.
- What are the tradeoffs between debug and release versions?
  - Debug versions have a more detailed Debug report generated so as to give more information to the developer. Furthermore, optimizations are turned off for easier debugging.
  - Release versions have a lesser detailed Debug report, while having optimizations enabled to ensure that the program runs faster.
- What arguments would you use in a debug build?
  - `-g` - Generates debug symbols for debuggers like GDB
  - `-O0` - For no optimizations
  - `-DDEBUG` - Defines the macro `DEBUG` which may be used to conditionally compile debug-only code.
- What about for release?
  - `-O2 (or -O3)` - Optimizes the code by eliminating redundant expressions and evaluating constant expressions at constant times.
  - `-DNDEBUG` - Defines `NDEBUG` which doesn't allow assertions.
- What other kinds of build types are useful?
  - Maybe Debugging while Releasing might seem as an option for developers to know what is happening during the release. So there can be a `Debug + Release` build type, especially for Alpha / Beta testing.

## Learn Basics of Make

- Create a Makefile that will speed up the process.
- [Quickstart tutorial to make](https://makefiletutorial.com/) - Learn make 
  fundamentals with practical examples and common patterns.
- How else can you learn about make?
  - Google and Stack overflow
  - [The official documentation of Make](https://www.gnu.org/software/make/manual/make.html)
- How can you tell if the resource you are using is correct?
  - Credible answers are often backed up by upvotes or more references!
- Create a makefile such that when you run `make` with no arguments, it will:
  - Create `build/` directory if it does not exist
  - Create executables **client** and **server** in `build/`, if needed
  - How does make know when it needs to rebuild the executables?
  - Change your Makefile such that `make clean` will remove `build/` and all
    its contents
- What are the most important command line arguments to learn for make?
  - `make` - Calls `make all` by default
  - `make <target name>` - Builds a specific target only
- What are the most important directives to learn about in Makefile?
  - `make target: prerequisites`: Makes the target with the condition that the pre-requisites already exist in the path
  - Variables: Allows us to define the build files, object files etc. in a better manner, maybe through wild cards.
  - Wild cards: Eliminates the need to write all the names of the files.
- What are the most important commands to implement in your Makefile?
  - `make all` - The build a developer needs to do to compile all the source files
  - `make clean` - To clean all the executables / object files.
- Which ones are essential, which ones are nice to haves?
  - `make all` is essential since it makes it easier for the person to compile everything at once, without giving a separate (possibly huge) command.
  - `make clean` is nice since it de-clutters the codebase after removing all the executables and `.o` files.

## Learn Basics of Git

- Read through the code in `src/`
- Answer any `#Questions` as a comment
- Commit and push your changes to git
- Each commit should be responding to a single task or question
- Why is it important to keep your commit to a single task or question?
  - Commits can be represented as a progress chart for the project. One should save every particular task achieved (as that adds to the projects), which is why commits should be made to a single task.
- Is it better to have a lot of very small commits, or one big commit when 
  everything is working?
  - A lot of small commits is better, since if something doesn't work in one of the commits, you still have some amount of progress. Furthermore, it's easier to debug as we know the commit to work on.
  - A big commit on the other hand, restarts the progress if something goes wrong, and it may be harder to debug where exactly the error was created, since may tasks were "completed" in that commit.
- What are the most important commands to know in git?
  - `git add` - Adds files to the staging area
  - `git commit` - Commits all staged files
  - `git push` - Pushes all commits to the repository on github
  - `git checkout -b <branch>` - Change the branch to some other branch (and create if it doesn't exist)
  - `git pull` - Pull commits from github to your local repository
  - `git clone <url>` - Clones the git repository (if it is accessible to the user).

## Introduction to Sockets

- Read the code in `src/tcp-echo-client.cc` and add a way to change the 
  message sent using command line arguments
- **Example**: `./client "hello message from the command prompt"` should send
  `"hello message from the command prompt"` to the server
- Commit your changes into git
- What do all these headers do?
  - `iostream` is for input and output from the terminal (`cin` and `cout`). It also includes output for error through `cerr`.
  - `string` is for `std::string` related operations
  - `cstring` is for C-string related operations (`memset` in this case)
  - `sys/socket.h` is for Internet-Protocol family operations ([as described here](https://pubs.opengroup.org/onlinepubs/7908799/xns/syssocket.h.html)), like `bind`, `accept`, `send`, `recv`
  - `netinet/in.h` defines IP address structures like `AF_INET`, IP address, port number etc.
  - `arpa/inet.h` is for definitions for internet operations. It has functions like `htonl()`, `htons()` etc. which converts values between host and network byte order.
  - `unistd.h` defines miscellaneous symbolic constants and types like `fork()`, `getpid()`, `getppid()`. This is also useful for file operations (`read`, `close` etc.). We may also execute shell commands (with `exec` family commands) via C / C++ program itself!
- How do you find out which part of the below code comes from which header?
  - `man <function name>` will show the header file the function belongs to. Furthermore, `Command + Right Click` on the function name in VS Code shows the header file.
- How do you change the code so that you are sending messages to servers other than localhost?
  - In the client, change the IP address to the address you want to send it to (the address of the server). Since the data is transferred to `IP:port`, it is essential to ensure that the `port` is also the same when communicating.
- How do you change the code to send to a IPv6 address instead of IPv4?
  - In the client code, we change the server address to its IPv6 address. Furthermore, for both client and server, we change all socket / IP operations to support IPv6 instead of IPv6 (for example, `AF_INET6`, `sockaddr_in6` etc).
- **Bonus**: How do you change the client code to connect by hostname instead of IP address?
  - First, I tried `gethostbyname()` method, which gives the IPv4 address of the host (considering we have the hostname of the server) using `h_addr_list[]` (list of all IP addresses). I knew there was a `gethostbyname()` method, thus, just looked up the man page and got the information.
  - Curiously, I wanted to find how to get IPv6 addresses. `gethostbyname()` is depracated, and redirects to `getaddrinfo()`, which provides the IPv6 addresses as well.
  
## Introduction to Memory Management

- What is happening in line 26 of `tcp-echo-client.cc`? 
  `if (inet_pton(AF_INET, kServerAddress.c_str(), &address.sin_addr) <= 0) {`
- What is happening in line 31 of `tcp-echo-client.cc`?
  `if (connect(my_sock, (sockaddr *)&address, sizeof(address)) < 0) {`
- What is the difference between a pointer and a reference?
- When is it better to use a pointer?
- When is it better to use a reference?
- What is the difference between `std::string` and a C-style string?
- What type is a C-style string?
- What happens when you iterate a pointer?
- What are the most important safety tips to know when using pointers?

## Learn Basics of Creating a C++ Project in Your IDE

- How do you compile and run your project in your IDE?

## Improving Interactions with LLMs

- What is the most authoritative source of information about `socket()`
  from `<sys/socket.h>`?
- What is the most authoritative source of information about the TCP and IP
  protocols?
- What is the most authoritative source of information about the C++
  programming language?
- What information can you find about using Markdown when structuring prompts 
  to LLMs?
- What is the difference between LLM and AI?
- Is it grammatically correct in English to say "a LLM" or "an LLM"? Why?