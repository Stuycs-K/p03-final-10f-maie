#include "networking.h"

void clientLogic(int server_socket){
  while (1) {
    //prompts the user for a string
    printf("client, enter a message: ");
    char input[BUFFER_SIZE];
    if (fgets(input, BUFFER_SIZE, stdin) != NULL) {
      int len = strlen(input);
      if (len > 0 && input[len-1] == '\n') {
        input[len -1] = '\0'; //remove new line
      }
      //send the user input to the server
      int bytes_written = write(server_socket, input, sizeof(input));
      err(bytes_written, "write error");
    }
    else {
      printf("Client closed\n");
      break;
    }
    //read message from the server
    char buffer[BUFFER_SIZE];
    int bytes_read = read(server_socket, buffer, sizeof(buffer));
    if (bytes_read == 0) {
      printf("Socket closed\n");
      break;
    }
    err(bytes_read, "read error");

    //prints the modified string
    //printf("client received: '%s'\n", buffer);
  }
}

int main(int argc, char *argv[] ) {
  char* IP = "127.0.0.1";
  if(argc>1){
    IP=argv[1];
  }
  int server_socket = client_tcp_handshake(IP);
  printf("client connected.\n");
  clientLogic(server_socket);
}
