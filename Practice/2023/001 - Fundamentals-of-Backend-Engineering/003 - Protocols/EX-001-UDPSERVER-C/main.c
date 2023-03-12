#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>



int main(int argc, char **argv){

  int port = 5501; // define an integer variable 'port' and assign it a value of 5501
  int sockfd; // define an integer variable 'sockfd'
  struct sockaddr_in myaddr, remoteAddr; // define two struct variables 'myaddr' and 'remoteAddr'
  char buffer[1024]; // define a character array 'buffer' with size 1024
  socklen_t addr_size; // define a variable 'addr_size' of type socklen_t

  sockfd = socket(AF_INET, SOCK_DGRAM, 0); // create a UDP socket and assign its file descriptor to 'sockfd'

  memset(&myaddr, '\0', sizeof(myaddr)); // set all the bytes in 'myaddr' to '\0'
  myaddr.sin_family = AF_INET; // set the address family to IPv4
  myaddr.sin_port = htons(port); // set the port number to the value of 'port'
  myaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // set the IP address to "127.0.0.1" (localhost)

  bind(sockfd, (struct sockaddr *)&myaddr, sizeof(myaddr)); // bind the socket to the local address and port number

  addr_size = sizeof(remoteAddr); // set the size of 'remoteAddr' to the size of a sockaddr_in struct
  recvfrom(sockfd, buffer, 1024, 0, (struct sockaddr *)&remoteAddr, &addr_size); // receive data from the socket and store it in 'buffer'

  printf("got data from %s ", buffer); // print the data received from the socket

  return 0; // return 0 to indicate successful program termination
}
