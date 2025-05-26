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
  - Yes. The way a compiler is implemented is upto the author / developer / maintainer of the compiler. That being said, The compiler should be according to the C++ standard.
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
- What can you do to identify if there are bugs in the code?

## Refactoring: Extract Function

- What is different in this code compared to exercise-1?
- Is this code better or worse than exercise-1?
- What are the tradeoffs compared to exercise-1?
- Are you able to spot any mistakes or inconsistencies in the changes?
  
## Thinking About Performance

- Does writing code this way have any impact on performance?
- What do we mean when we say performance?
- How do we measure performance in a program?

## Play with Git

- There isn't necessarily a single correct answer for how to abstract the 
  code from exercise-1 into functions
- Try different ways to refactor the code from exercise-1 to make it more
  readable.
- Make sure to commit each change as small and self-contained commit
- This will make it easier to revert your code if you need to
- What is `git tag`? How is `git tag` different from `git branch`?
- How can you use `git tag` and `git branch` to make programming easier and
  more fun?

## Learn Basics of Debugging in Your IDE

- How do you enable debug mode in your IDE?
- In debug mode, how do you add a watch?
- In debug mode, how do you add a breakpoint?
- In debug mode, how do you step through code?

### Memory Management and Debug Mode in Your IDE

- How do you see the memory layout of a `std::string` from your IDE debug mode?
- How do you see the memory layout of a struct from your IDE debug mode?