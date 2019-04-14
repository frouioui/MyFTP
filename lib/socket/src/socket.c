/*
** EPITECH PROJECT, 2019
** MyFTP
** File description:
** Main socket functions
*/

#include <stdbool.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <netdb.h>

int create_socket(void)
{
    struct protoent *proto = getprotobyname("TCP");
    int fd = 0;
    int p = 1;

    if (proto == NULL)
        return (-1);
    fd = socket(AF_INET, SOCK_STREAM, proto->p_proto);
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &p, sizeof(int));
    return (fd);
}

int bind_socket(const int socket, struct sockaddr_in *info, const bool rand)
{
    int ret = 0;

    if (rand == true) {
        info->sin_port = htons(0);
    }
    ret = bind(socket, (struct sockaddr *)info, sizeof(*info));
    return (ret);
}

int listen_socket(const int socket, const int maximum_pending)
{
    return (listen(socket, maximum_pending));
}