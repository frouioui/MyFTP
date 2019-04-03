/*
** EPITECH PROJECT, 2019
** MyFTP
** File description:
** Source file of the internet address function
*/

#include <netinet/in.h>

struct sockaddr_in create_socket_internet_address(const int port)
{
    struct sockaddr_in info = {0};

    info.sin_family = AF_INET;
    info.sin_port = htons(port);
    info.sin_addr.s_addr = htonl(INADDR_ANY);
    return (info);
}