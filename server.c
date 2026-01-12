#include "networking.h"


void subserver_logic(int client_socket, int listen_socket, fd_set * master){
  //while (1) {
    //listens for a string (use the buffer size)
    char buffer[BUFFER_SIZE];
    int bytes_read = read(client_socket, buffer, sizeof(buffer));
    if (bytes_read <= 0) {
      printf("Socket closed\n");
      close(client_socket);
      FD_CLR(client_socket, master); //remove from master set
      //break;
    }
    printf("server received: %s\n", buffer);

    //server writes back message to all clients
    for (int i = 0; i < FD_SETSIZE; i++) {
      if (i != client_socket && i != listen_socket && FD_ISSET(i, master)) {
        int bytes_written = write(i, buffer, bytes_read);
        err(bytes_written, "write error");
      }
    }
    //printf("server sending back: %s\n", buffer);
  //}
}


int main(int argc, char *argv[] ) {
  fd_set master;    // master file descriptor list
  fd_set read_fds;  // temp file descriptor list for select()
  int fdmax;        // maximum file descriptor number

  FD_ZERO(&master);
  FD_ZERO(&read_fds);
  int listen_socket = server_setup();

  //add listen_socket to the master set
  FD_SET(listen_socket, &master);

  fdmax = listen_socket; //biggest file descriptor so far

  printf("bind complete\n");
  printf("server listening for connections.\n");
  while (1) {
    read_fds = master;
    if (select(fdmax+1, &read_fds, NULL, NULL, NULL) == -1) {
      perror("select error");
      exit(1);
    }

    for (int i = 0; i <= fdmax; i++) {
      if (FD_ISSET(i, &read_fds)) {
        if (i == listen_socket) {
          //connect new client
          int client_socket = server_tcp_handshake(listen_socket);
          FD_SET(client_socket, &master); //add to master
          if (client_socket > fdmax) {
            fdmax = client_socket;
          }
          //printf("new client connected: %d\n", client_socket);
          char user[BUFFER_SIZE];
          int bytes_read = read(client_socket, user, sizeof(user));
          err(bytes_read, "user name read error");
          printf("new client connected: %s\n", user);
        }
        else {
          subserver_logic(i, listen_socket, &master);
        }
      }
    }
  }
}
