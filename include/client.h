/*
** EPITECH PROJECT, 2019
** MyFTP
** File description:
** Client function and struct
*/

#if !defined(_CLIENT_H)
#define _CLIENT_H

#include "user.h"

enum data_transfert_mode_s {
    NOT_SET,
    PASSIVE,
    ACTIVE
};

typedef enum data_transfert_mode_s data_transfert_mode_t;


struct client_s {
    int socket;
    user_t user;
    data_transfert_mode_t dt_mode;
};

typedef struct client_s client_t;

#endif // _CLIENT_H
