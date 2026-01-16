#include "networking.h"


void subserver_logic(int client_socket, int listen_socket, fd_set * master){
    //listens for a string (use the buffer size)
    char buffer[BUFFER_SIZE];
    int bytes_read = read(client_socket, buffer, sizeof(buffer));
    if (bytes_read <= 0) {
      close(client_socket);
      FD_CLR(client_socket, master); //remove from master set
    }
    buffer[bytes_read] = '\0';
    printf("%s\n", buffer);

    //writing to chat log file
    int fd = open("log.txt", O_CREAT | O_WRONLY | O_APPEND, 0644);
    err(fd, "file open error");
    char log[BUFFER_SIZE];
    memset(log, 0, sizeof(log));
    strcat(log, buffer);
    strcat(log, "\n");
    int bytes_written = write(fd, log, strlen(log));
    err(bytes_written, "write error");
    close(fd);

    //server writes back message to all clients
    for (int i = 0; i < FD_SETSIZE; i++) {
      if (i != client_socket && i != listen_socket && FD_ISSET(i, master)) {
        int bytes_written = write(i, buffer, strlen(buffer));
        err(bytes_written, "write error");
      }
    }
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

  printf("Welcome! Server has succesfully connected!\n");
  printf("Server is waiting for users...\n");

  //make chat log file here
  int fd = open("log.txt", O_CREAT | O_WRONLY | O_APPEND, 0644);
  err(fd, "file open error");
  char text[BUFFER_SIZE] = "\n----------New server session----------\n";
  int bytes_written = write(fd, text, strlen(text));
  err(bytes_written, "write error");
  close(fd);

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
          char user[BUFFER_SIZE];
          memset(user, 0, sizeof(user));
          int bytes_read = read(client_socket, user, sizeof(user));
          err(bytes_read, "user name read error");
          user[bytes_read] = '\0';
          printf("%s has connected\n", user);
          //adding connection messages to chat log
          int fd = open("log.txt", O_CREAT | O_WRONLY | O_APPEND, 0644);
          err(fd, "file open error");
          char text[BUFFER_SIZE];
          snprintf(text, sizeof(text), "%s has connected\n", user);
          int bytes_written = write(fd, text, strlen(text));
          err(bytes_written, "write error");
          close(fd);
        }
        else {
          subserver_logic(i, listen_socket, &master);
        }
      }
    }
  }
}
