#include "networking.h"


void subserver_logic(int client_socket){
  fd_set read_fds;
  FD_ZERO(&read_fds);

  while (1) {
    //listens for a string (use the buffer size)
    char buffer[BUFFER_SIZE];
    int bytes_read = read(client_socket, buffer, sizeof(buffer));
    if (bytes_read == 0) {
      printf("Socket closed\n");
      break;
    }
    err(bytes_read, "read error");
    printf("server received: %s\n", buffer);

    //server writes back message to client
    int bytes_written = write(client_socket, buffer, bytes_read);
    err(bytes_written, "write error");
    //printf("server sending back: %s\n", buffer);
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

  printf("bind complete\n");
  printf("server listening for connections.\n");
  while (1) {
    read_fds = master;
    if (select(fdmax+1, &read_fds, NULL, NULL, NULL) == -1) {
      perror("select error");
      exit(1);
    }

    int client_socket = server_tcp_handshake(listen_socket);
    pid_t pid = fork();
    if (pid == 0) {
      subserver_logic(client_socket);
    }
    else {
      close(client_socket);
    }
  }
}
