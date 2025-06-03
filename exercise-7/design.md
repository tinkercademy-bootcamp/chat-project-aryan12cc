# Design Document

## Requirements

### Minimal Requirements

- One server multiple clients connection scheme
- Clients should be assigned a **username** while communicating with the server
- Commands:
  - List channels
  - Goto a specific channel
  - Create a channel
- Whenever a client types in a message in a particular channel, everyone in that channel should receive the message

### Further Suggestions

**Note: Many will probably not be implemented due to time constraints. These are just some ideas I have**

- Display how many people are currently present in a channel
- Have a time to live for each channel, and when there are 0 members, remove that channel permanently
- A method to depict the username of the client while interacting with the server
- Login system for clients to re-use their original usernames
- A client can go to multiple channels instead of one
  - A client can select the channel to which a particular message should go to
- A client can be an **admin** of a channel
  - Admins can request or remove other **usernames** from that specific channel
  - Admins can make other people admins / remove them from admins
  - First person to join will be an admin by default
  - If the only admin leaves, the channel will choose another admin by:
    - Randomization
    - Longest current stay in the channel
- Request-only channels
  - Either admins can send an invite
  - Or clients can request for access
- Clients can have a look at the requests sent to them while they were offline
- Have a look at `ncurses` and `libsdl2`

### Feedback to Incorporate

- Handle graceful closing of socket in all cases
- Ctrl + C exception handlers
- Follow Law of Three
- No large chunks of code commented out
- Add comments, especially in header files
- Private member functions to end with a `_`
- Use `std::concepts` in `check_error()`
- Ensure no redundant branching
- Return a boolean with check_error if there is an error and you will not terminate, so that it gets logged

## Working

`*` indicates a requirement from **Further Suggestions**

### Server

- Server should have a list of clients, preferably a class alongside member functions like:
  - Usernames
  - List of channels currently present
- Server should have a list of channels, preferably a class alongside member functions like:
  - List of clients currently present
  - Channel id
  - Channel name
  - *List of admins
  - *Last time with >= 1 client present

### Client
- *Login (very rough idea as of now)
  - Phone number mapped with username
  - Username may change, although unique username
  - Phone numbers may not change
- Essentially **goto channel** is add to current channel and remove from previous channel
- Commands
  - `/create <channel_name>` Creates a channel with the channel_name and displays the corresponding id.
  - *`/get-history <channel_id> <number>` List the previous `number` messages in the channel. Ensure that the user was a member of the channel and didn't leave after that
  - `/join <channel_id>` Join a channel with corresponding channel_id
    - *May work differently for request-only channels (maybe `/request-join <channel_id>`)
  - `/leave <channel_id>` Leave channel with corresponding channel_id
  - `/list-all` List channels (will show ID mapping with names)
    - *`list <channel_id>` Detailed info about a channel prints the members of the channel
  - `/message <channel_id> <message>` Broadcasts the message to channel_id
  - *`/login <phone_number> <username>`
  - *`/register <phone_number> <username>`
  - *`/request-add <channel_id>` Request another client to be added to the `channel_id`. Needs to be an `admin` of `channel_id` channel.

## Directory Structure

**This is just a proposed directory structure.**

```
|-build/
|-src/
|    |-network/
|    |   |-- network.h
|    |   |-- network.cpp
|    |-server/
|    |   |--channels/
|    |   |     |-- channel-information.h
|    |   |     |-- channel-information.cpp
|    |   |--command/
|    |   |     |-- command.h
|    |   |     |-- command.cpp
|    |   |-- server-chat.h
|    |   |-- server-chat.cpp
|    |-client/
|    |   |-- client-chat.h
|    |   |-- client-chat.cpp
|    |- client-main.cpp
|    |- server-main.cpp
|-tests/
Makefile
```