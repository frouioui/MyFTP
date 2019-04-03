/*
** EPITECH PROJECT, 2019
** MyFTP
** File description:
** Header file of the socket library
*/

#if !defined(_SOCKET_H)
#define _SOCKET_H

struct sockaddr_in create_socket_internet_address(const int port);
int create_socket(void);
int bind_socket(const int socket, struct sockaddr_in *info, const bool rand);
int listen_socket(const int socket, const int maximum_pending);

#endif // _SOCKET_H
