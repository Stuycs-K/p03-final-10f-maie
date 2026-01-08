#include "networking.h"


void subserver_logic(int client_socket){
 
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