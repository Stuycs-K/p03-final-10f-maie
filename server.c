#include "networking.h"


void subserver_logic(int client_socket){
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
  int listen_socket = server_setup();
  printf("bind complete\n");
  printf("server listening for connections.\n");
  while (1) {
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
