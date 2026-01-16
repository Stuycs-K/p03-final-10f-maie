[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/QfAIDTGi)
# Chat Away

### GROUP NAME HERE (CHANGE THIS!!!!!)

Emily Mai

### Project Description:

A simple terminal-based chat program allowing communication among various users. This project utilizes sockets and networking to connect clients to a server, and select to handle sending and receiving to multiple sockets simultaneously. Users are able to enter usernames, communicate with other users, and view chat logs.

### Video Link
https://drive.google.com/file/d/1YsS5eLtH0E3iMnw_LqoV636xMKw4s6xK/view?usp=drive_link

### Instructions:
1. Open a terminal window and clone this repo through ssh by running:  
`git clone git@github.com:Stuycs-K/p03-final-10f-maie.git`

2. Once this repo is cloned, change to the repo directory:  
`cd p03-final-10f-maie`

3. Run this in the terminal:  
`make compile`

4. To run the server:  
`./server`

5. To connect a user, run the code below on a separate terminal. Multiple clients can connect to a server.  
`./client`

6. On the client terminal, you will be prompted to enter a username. Please enter any username you would like.

7. Once a username is entered, clients will be able to send messages to the server to other clients. Clients will be able to receive messages from other clients. Feel free to start typing.

8. To disconnect a client from the server, press Ctrl and C.

9. To view the chat log, run this on a separate terminal:  
`cat log.txt`

10. To reset chat logs:  
`make clean`


### Resources/ References:

https://konstantinnovation.github.io/systems.html  
https://beej.us/guide/bgnet/html/  

