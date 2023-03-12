This code creates a UDP server that listens on port 5501 and prints any data that it receives to the console. Here's a summary of what each line does:

    int port = 5501;: Defines an integer variable 'port' and assigns it the value 5501.
    int sockfd;: Declares an integer variable 'sockfd' that will later be used to store the file descriptor of the socket.
    struct sockaddr_in myaddr, remoteAddr;: Declares two struct variables, 'myaddr' and 'remoteAddr', of type sockaddr_in.
    char buffer[1024];: Declares a character array 'buffer' with a size of 1024, which will be used to store data received from the socket.
    socklen_t addr_size;: Declares a variable 'addr_size' of type socklen_t, which will be used to store the size of the remote address struct.
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);: Creates a UDP socket and assigns its file descriptor to 'sockfd'.
    memset(&myaddr, '\0', sizeof(myaddr));: Sets all bytes in 'myaddr' to '\0'.
    myaddr.sin_family = AF_INET;: Sets the address family of 'myaddr' to IPv4.
    myaddr.sin_port = htons(port);: Sets the port number of 'myaddr' to the value of 'port', converted to network byte order using htons().
    myaddr.sin_addr.s_addr = inet_addr("127.0.0.1");: Sets the IP address of 'myaddr' to

# cmd
- nc -u 127.0.0.1 5501