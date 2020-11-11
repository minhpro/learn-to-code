#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h> 
#include <unistd.h>
#include <string.h>

#define SERVER_HOST "127.0.0.1"
#define SERVER_PORT 8080
#define MAX_LINE 256

int main() 
{
    struct sockaddr_in serv_addr;
    memset((char *)&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(SERVER_PORT);
    // Convert IPv4 and IPv6 addresses from text to binary form 
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)  
    { 
        printf("\nInvalid address/ Address not supported \n"); 
        return -1; 
    }

    int s;
    if ((s = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n"); 
        return -1;     
    }

    if (connect(s, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    { 
        printf("\nConnection Failed \n"); 
        return -1; 
    }

    char *hello = "Hello from client"; 
    char buffer[1024] = {0};
    int readlen;
    send(s , hello , strlen(hello) , 0 ); 
    printf("Hello message sent\n"); 
    readlen = read( s , buffer, 1024); 
    printf("%s\n",buffer );
    close(s);
    return 0;
}
