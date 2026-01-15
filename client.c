#include "networking.h"

void clientLogic(int server_socket){
  fd_set read_fds;
  char input[BUFFER_SIZE];
  char s[BUFFER_SIZE];

  //ask client for username
  char user[BUFFER_SIZE];
  printf("client, enter a username: ");
  if (fgets(user, BUFFER_SIZE, stdin) != NULL) {
    int len = strlen(user);
    if (len > 0 && user[len-1] == '\n') {
      user[len -1] = '\0'; //remove new line
    }
    int bytes_written = write(server_socket, user, strlen(user));
    err(bytes_written, "write user name error");
  }

  printf("%s, enter a message: ", user);
  fflush(stdout);

  while (1) {
    FD_ZERO(&read_fds);
    FD_SET(STDIN_FILENO, &read_fds);
    FD_SET(server_socket, &read_fds);

    if (select(server_socket + 1, &read_fds, NULL, NULL, NULL) == -1) {
      perror("select");
      exit(1);
    }

    if(FD_ISSET(STDIN_FILENO, &read_fds)) {
      //prompts the user for a string
      //printf("%s, enter a message: ", user);
      //fflush(stdout);
      if (fgets(input, BUFFER_SIZE, stdin) != NULL) {
        int len = strlen(input);
        if (len > 0 && input[len-1] == '\n') {
          input[len -1] = '\0'; //remove new line
        }
        //send the user input to the server
        //char s[BUFFER_SIZE];
        strcat(s, user);
        strcat(s, ": ");
        strcat(s, input);
        //printf("%s", s);
        //int bytes_written = write(server_socket, user, strlen(input));
        //err(bytes_written, "write error");
        int bytes_written = write(server_socket, s, strlen(s));
        err(bytes_written, "write error");
        strcpy(s, "");
        printf("%s, enter a message: ", user);
        fflush(stdout);
      }
      else {
        printf("Client closed\n");
        break;
      }
    }
    if (FD_ISSET(server_socket, &read_fds)) {
      //read message from the server
      char buffer[BUFFER_SIZE];
      int bytes_read = read(server_socket, buffer, sizeof(buffer));
      if (bytes_read == 0) {
        printf("Socket closed\n");
        break;
      }
      err(bytes_read, "read error");
      buffer[bytes_read] = '\0';
      printf("\n%s\n", buffer);
      printf("%s, enter a message: ", user);
      fflush(stdout);
    }
  }
}

int main(int argc, char *argv[] ) {
  char* IP = "127.0.0.1";
  if(argc>1){
    IP=argv[1];
  }
  int server_socket = client_tcp_handshake(IP);
  printf("client connected.\n");
  //printf("client, enter a message:");
  clientLogic(server_socket);
}
