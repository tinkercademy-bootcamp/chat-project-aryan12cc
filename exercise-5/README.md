# Exercise 5

**Update this README with your answers to the questions below.**

## Comparing File Changes

- What's an easy way to identify the changes in source code from one exercise to another?
  - The `diff` command in the terminal is an easy way of identifying changes.
    - `diff -w` gives all the lines of code that are different between two source codes, whilst ignoring whitespaces
    - `diff -c` shows the lines that were changed in a verbose manner
    - `diff -u` is similar to `diff -c` but more compact an easier to understand.
  - To run the `diff` command, we use `diff -<flag> <path_to_source_1> <path_to_source_2>`
    
## Using Classes

- Here is one way to separate out the code into multiple files
- Is this the best way to do it? 
  - I think classes could be used to separate the concerns (logic) in a better manner instead of namespace, since the member functions and variables in a class should usually be strongly related with one another, coming together as a whole to create objects. One may also use the fact that there can be multiple clients so it might be better just to create a client object everytime.
  - One way I like to think about it (didn't find it anywhere though), is that namespaces should define a broader group which has related functionality. Classes should define a small / medium sized group which is very cohesive in nature. As in, the data members and variables should ideally interact a lot between one another, and not that much when used outside.
  - Furthermore, the way namespace was used in the code is a bit weird
    - The separation of logic into namespaces is not the best in the code preovided
    - For example, clients and server are the two main separation of logic points apart from sockets / network. The way namespace is used in clients and server is very different -- clients don't even have a namespace for that matter.
- What are the advantages and disadvantages?
  - I think namespaces are mainly used to organize code into broad groups. Useful naming can also be used to give an idea about the namespace
  - Nested namespaces / badly named namespaces can be as hard to understand as its easy for namespaces to organise code. In general, readability decreases when someone uses something like `ns1::ns2::ns3::ns4::var1`.

## Introduction to Namespace

- There are different ways namespace is being used in this exercise
  - Unnamed namespaces are used, where a chunk of code is just being declared within a namespace and the namespace has not been given a name
  - `using` keyword has been used, in which if we type `using namespace xyz`, we don't need to add the prefix `xyz::` to any of the member variables of that namespace
  - `namespace x = y` has been used. Instead of appending the prefix `y::`, we can not append the prefix `x::`
- Which way is better? What are the advantages and disadvantages?
  - Unnamed namespaces just work for the current file (and any other file that is being referred as a header). Thus, it prevents symbol collissions. The design has a very limited scope and one needs to use it in a very efficient manner to get the most of it
  - `using` keyword makes it more convenient for the developer to write code as it saves typing the prefix `xyz::`. That being said, in bigger systems, it may lead to name clashes and may lead to ambiguity, especially if multiple namespaces are being used using the `using` keyword.
  - `namespace x = y` is aliasing `y` to `x`. This is so that long or nested namespaces conveniently gets converted to a smaller namespace. Although, this may lead to a new developer who is inexperienced with the codebase to get confused very easily.

## Abstracting Code into Classes

- Abstract the client and server logic into a `Client` and `Server` class
- **Note**: You don't have to use the code in this exercise as a starting point
- You can use the code you wrote from previous exercises instead
- How should you divide the code into files?
  - We should divide the code such that each file is a "class" or a "functional unit" by itself. It does most of the interactions internally, and very few interactions go to other external files. Similar classes operating under the same purpose in the code flow can be grouped together in the same directory, with the name of the directory being something similar to what the purpose is.
- What namespace and directory structure should you use? Why?
  - There should be separate `src/`, `build/` and `tests/` folders. Furthermore, a `Makefile` should be present in the root directory. This is for the ease of testing, executing and changing the codebase. It basically ensures that the executables don't interfere with the codebase or the testing, whilst also ensuring the same for testing and codebase.
    - `src/` should contain the codebase
    - `build/` should contain all the executables. `make all` should create this directory, while `make clean` should remove it.
    - `tests/` should contain all the tests used to ensure program / application correctness
  - The best I can think of for namespace structure is to follow the directory structure. This will prevent any clashes, and, if followed by the developer, will easily explain the purpose of the particular file in the codebase, just by looking at the namespace.


## Programming Sense of Taste

- How do you judge what makes a particular choice of namespace and directory structure? 
- How do you judge what makes a good naming convention or programming style?

## "Senses" in Programming

- Have you ever heard of programmers referring to "code smells"? How can code smell?
- What does it mean to have a sense of taste in programming? How can code taste?
- Is there an analogue for every sense?
- What other code senses can you think of?
- How many senses do humans have?
- When would you want to see something before you touch it?
- When would you want to touch something before you see it?