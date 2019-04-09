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

int create_socket(void)
{
    return (socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0));
}

int bind_socket(const int socket, struct sockaddr_in *info, const bool rand)
{
    int ret = 0;

    if (rand == true) {
        info->sin_port = 0;
    }
    ret = bind(socket, (struct sockaddr *)info, sizeof(*info));
    return (ret);
}

int listen_socket(const int socket, const int maximum_pending)
{
    return (listen(socket, maximum_pending));
}