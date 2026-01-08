# Final Project Proposal

## Group Members:

Emily Mai

# Intentions:

This project will be a simple chat program in which users will be able to communicate with others.

# Intended usage:

A server can be made by running a command like ./server. In order to communicate, users will have to connect to the server by running another command such as ./client. Users will be prompted to input text messages which will be received by the server and displayed on all user terminals. 

# Technical Details:

Sockets and networking will be used to facilitate connections between the server and the client, and allow for communication among them.
To have multiple clients, the select function wil be used to simultaneously check multiple sockets to see if they have data waiting to be received or if data can be sent to them without blocking.
Signals can be used to close clients and sockets.
Files can be used to keep track of the chat log.


# Intended pacing:

1/12 - basic program allowing users to communicate in place
1/13 - making chat log file
1/14 - debugging, error checking, can add features like usernames, etc. to make it feel more like a messaging app
1/15 - finishing touches, record and edit video presentation
1/16 - final review of project, readme done, project due
