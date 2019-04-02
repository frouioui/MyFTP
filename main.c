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
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/time.h>

static struct sockaddr_in create_sockaddr_info(const int port)
{
    struct sockaddr_in info = {0};


    info.sin_family = AF_INET;
    info.sin_port = htons(port);
    info.sin_addr.s_addr = htonl(INADDR_ANY);
    return (info);
}

static int create_socket(struct sockaddr_in info, const int port)
{
    int sock = 0;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == 0) {
        // SOCKET_ERROR
        return (-1);
    }
    if (port > 0)
        info.sin_port = htons(port);
    if (bind(sock, (struct sockaddr *)&info, sizeof(info)) < 0) {
        // BIND_ERROR
        return (-2);
    }
    if (listen(sock, 1) < 0) {
        // LISTEN_ERROR
        return (-3);
    }
    return (sock);
}

static int accept_incoming_connection(struct sockaddr_in info, const int parent_socket)
{
    int addrlen = sizeof(info);

    return accept(parent_socket, (struct sockaddr *)&info, (socklen_t*)&addrlen);
}

static void run_single_connection(struct sockaddr_in info, int socket)
{
    static int ports_list[1000] = {0};
    char buffer[1024] = {0};
    int valread = 0;
    int opt = 1;

    valread = read(socket, buffer, 1024);

    // DEBUG: Receiving the PASV (passive) command
    if (strncmp(buffer, "PASV", 4) == 0) {
        int data_socket = 0;

        get_free_port(ports_list, info.sin_port);
        data_socket = create_socket(info, 3334);
        if (data_socket <= 0) {
            perror("create_socket");
            return;
        }
        printf("recieved PASV created data_socket on port 3334\n");
        close(data_socket);
    }

    printf("%s\n", buffer);
    // send(socket, hello, strlen(hello), 0);
    // printf("Hello message sent\n");
}

int main(void)
{
    int connected_socket = 0;
    int fd = 0;
    int ret = 0;
    struct sockaddr_in name = create_sockaddr_info(3333);
    int addrlen = sizeof(name);
    fd_set read_set, working_set;
    struct timeval timeout;

    fd = create_socket(name, 0);
    if (fd <= 0) {
        perror("create_socket");
        return (84);
    }

    FD_ZERO(&read_set);
    FD_SET(fd, &read_set);

    timeout.tv_sec = 3 * 60;
    timeout.tv_usec = 0;

    while (true) {

        working_set = read_set;
        ret = select(FD_SETSIZE, &working_set, NULL, NULL, NULL);

        for (unsigned int i = 0; i < FD_SETSIZE; i++) {
            if (FD_ISSET(i, &working_set)) {
                if (i == fd) {
                    // DEBUG: New client
                    if ((connected_socket = accept_incoming_connection(name, fd)) < 0) {
                        perror("accept");
                        return (84);
                    }
                    printf("connected\n");
                    FD_SET(connected_socket, &read_set);
                } else {
                    // DEBUG: Old client
                    run_single_connection(name, i);
                }
            }
        }

    }
    close(fd);
    return (0);
}

