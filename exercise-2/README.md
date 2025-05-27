# Exercise 2

**Update this README with your answers to the questions below.**

## Sources of Information for Questions from Before

### Socket 
- https://man7.org/linux/man-pages/man2/socket.2.html - System call reference
  for creating communication endpoints
- Or type `man socket` in terminal
- https://man7.org/linux/man-pages/man7/socket.7.html - Socket interface 
  overview and protocol families
- Or type `man 7 socket` in terminal
- When would you want to use a `SOCK_RAW` stream?
  - I would use `SOCK_RAW` stream if I wanted to implement a different IP protocol other than TCP / UDP. This gives me access to the low level details of communicating with another host (any device -- computer, mobile etc.), which may be used to optimize communication since it may be so that the protocol (TCP / UDP) being used is not the most effective way to communicate.

### TCP and IP Protocols
- [IPv4](https://www.rfc-editor.org/info/rfc791) - Internet Protocol 
  specification defining packet structure and routing
- [IPv6](https://www.rfc-editor.org/info/rfc8200) - Next-generation Internet 
  Protocol with expanded address space
- [TCP](https://datatracker.ietf.org/doc/html/rfc9293) - Transmission Control 
  Protocol providing reliable, ordered data delivery
    
### C++
- [C++23 ISO standard draft](https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2023/n4950.pdf) - 
  Working draft of the C++ language specification
- Is the above the official C++23 spec? 
  - No, it is a working draft.
- Where is the official C++23 spec?
  - [Official C++23 spec](https://www.iso.org/standard/83626.html)
- Why was this link chosen instead?
  - The official spec is pay to use. The link chosen is a draft and is freely available publicly.
- Is this a helpful reference for learning C++?
  - For beginner stage, no. This is because it is full of jargon that a newcomer won't understand.
  - For advanced developers, yes. This allows the developers to delve deeper into the meaning and syntax of C++ related coding practicies.
- Can the various implementations of C++ compilers be different from the C++ standard?
  - Yes. The way a compiler is implemented is upto the author / developer / maintainer of the compiler. That being said, the compiler should be according to the C++ standard.
- What are the most widely used and most significant C++ compilers?
  - GCC / G++
  - Clang
- Where is the equivalent spec for C++26?
  - The official spec hasn't been released since C++26 hasn't been released. The draft can be found [here](https://github.com/cplusplus/draft).

- Where do you find the spec for the HTTP protocol?
  - [IETF website](https://datatracker.ietf.org/doc/html/rfc2616)
- What about HTTPS? Is there a spec for that protocol?
  - HTTPS is essentially HTTP with Transport Layer Security (TLS) to secure connections. This can be found [here](https://datatracker.ietf.org/doc/html/rfc2818).

## Introduction to C++ and Sockets Programming

- Read the code in `src/`
- Are there any bugs in this code? 
  - If there were multiple arguments (say `./build/client.out I am`), only `I` was being sent. Although, I believe, the intent was to keep the message within quotation marks.
  - An empty message like `./build/client.out ""` would make the client send a message of length 0 and wait for a response. This is because the client is sending a `cstring` of length 1 consisting of `\0` while the server is sending a `std::string` of length `0` which never gets "sent".
  - 
- What can you do to identify if there are bugs in the code?
  - For this exercise, I tested it on various inputs
  - On bigger software development projects, one can have a testing system to test the critical flows of the system.

## Refactoring: Extract Function

- What is different in this code compared to exercise-1?
  - The code in `tcp_echo_client.cc` and `tcp_echo_server.cc` is more modular - it is broken down into functions which serve different purposes while communicating with the client.
- Is this code better or worse than exercise-1?
  - Better.
- What are the tradeoffs compared to exercise-1?
  - The modular code helps in testing, readability, coding in the future / for other developers etc.
  - A drawback of modular code is the code size. For example, there is a difference of 30 lines in the server codes between exercise 1 and 2.
- Are you able to spot any mistakes or inconsistencies in the changes?
  - I could not spot any mistake in the changes. The 
  - A mistake I needed to fix in Exercise 1 was that if I had a message "Hello" and then "Hi", since the buffer wasn't cleared, the second message would be printed as "Hillo". The modular code removes this error by giving each connection its own buffer.
  
## Thinking About Performance

- Does writing code this way have any impact on performance?
  - Human performance, yes, since it saves a lot of time for future developers.
  - Computer performance, not really. It has a negative effect since there may be a lot of jumping between functions which may induce an overhead.
- What do we mean when we say performance?
  - Here, I mean computer performance and human performance (how much time it takes a human to read, understand, and modify code)
- How do we measure performance in a program?
  - Human performance can be measured by the amount of time taken to maintain and refactor the code.
  - Computer performance can be measured by profiling tools like CProfile, `std::chrono`, `./time` etc.

## Play with Git

- There isn't necessarily a single correct answer for how to abstract the code from exercise-1 into functions
- Try different ways to refactor the code from exercise-1 to make it more readable.
- Make sure to commit each change as small and self-contained commit
- This will make it easier to revert your code if you need to
- What is `git tag`? How is `git tag` different from `git branch`?
  - `git tag` is used to "tag" specific commits in the repository. These may represrnt various milestones / working versions.
  - `git branch` is used to deviate from the main working branch and work on a separate line of development (like for a feature).
- How can you use `git tag` and `git branch` to make programming easier and more fun?
  - Suppose the project is scheduled for a release with some features. Each of the features ideally has a separate branch, after which they get merged into the same branch. When the release happens, the current commit gets tagged as the release version. Now, if I want to add another feature, I can branch it off from the main branch and work on it. On finishing it, it may require some testing, so a `test` tag may be added to that commit before merging it with the main branch.

## Learn Basics of Debugging in Your IDE

- How do you enable debug mode in your IDE?
  - Install `gdb`. Change the Makefile to add `-g` flag while compiling. Configure `launch.json` with the executables to be run.
- In debug mode, how do you add a watch?
  - In the run and debug panel, there is a watch section. Clicking on the `+` button allows us to type in an expression to watch.
- In debug mode, how do you add a breakpoint?
  - To the left of the code, the subsequent line numbers are shown. There is a small gap between the window and the line number. Hovering over the gap enables a red dot, clicking on which enables a breakpoint on that line.
- In debug mode, how do you step through code?
  - There is a small GUI with symbols. There are 6 symbols as follows:
    - Continue / Pause (F5 shortcut)
    - Step Over (F10)
    - Step Into (F11)
    - Step Out (Shift + F11)
    - Restart (Shift + Cmd + F5)
    - Stop (Shift + F5)

### Memory Management and Debug Mode in Your IDE

- How do you see the memory layout of a `std::string` from your IDE debug mode?
- How do you see the memory layout of a struct from your IDE debug mode?