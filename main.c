/**
 * Bootstrap file
 *
 * WARNING: Not production ready
 */

#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>

int main(void)
{
    int new_fd = 0;
    int fd = 0;
    struct sockaddr_in name;
    int addrlen = sizeof(name);
    char buffer[1024] = {0};
    int valread = 0;
    char *hello = "Hello from the server";
    int opt = 1;

    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd == 0) {
        printf("Error\n");
        return (84);
    }

    name.sin_family = AF_INET;
    name.sin_port = htons(3333);
    name.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(fd, (struct sockaddr *)&name, sizeof(name))<0) {
        perror ("bind");
        return (84);
    }
    if (listen(fd, 1) < 0) {
        perror("listen");
        return (84);
    }
    if ((new_fd = accept(fd, (struct sockaddr *)&name, (socklen_t*)&addrlen))<0) {
        perror("accept");
        return (84);
    }
    valread = read(new_fd, buffer, 1024);
    printf("%s\n",buffer );
    send(new_fd , hello , strlen(hello) , 0 );
    printf("Hello message sent\n");
    close(fd);
    close(new_fd);
    return (0);
}

