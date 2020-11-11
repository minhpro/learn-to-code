#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>

#define SERVER_PORT 8080
#define MAX_PENDING 5
#define BUFFER_SIZE 256

int main() {
    int s;
    if ((s = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket failed");
        exit(1);
    }

    struct sockaddr_in sin;
    memset((char *)&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(SERVER_PORT);
  
    if ((bind(s, (struct sockaddr *)&sin, sizeof(sin))) < 0) {
        perror("bind failed");
        exit(1);
    }

    listen(s, MAX_PENDING);

    // wait for connection, then receive and print text
    socklen_t sock_len;
    char buf[BUFFER_SIZE];
    char *hello = "Hello from server"; 
    while(1) {
        int new_s;
        if ((new_s = accept(s, (struct sockaddr *)&sin, &sock_len)) < 0) {
            perror("Accept failed");
            exit(1);
        }
        int len;
        while ((len = recv(new_s, buf, sizeof(buf), 0))) {
            printf("%s\n", buf); 
            send(new_s , hello , strlen(hello) , 0 ); 
            printf("Hello message sent\n"); 
        }
        close(new_s);
    }

    return 0;
}
