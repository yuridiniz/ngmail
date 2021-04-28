#ifndef __SERVER_H
#define __SERVER_H

#include <uv.h>

typedef struct client client_t;
typedef struct server server_t;

struct server {

    int id;
    uv_loop_t loop;
    uv_tcp_t uv_server;
    struct sockaddr_in addr;
    int (*on_accept_cb)(server_t*, client_t*);
    void (*on_read_cb)(client_t*, ssize_t, const uv_buf_t*);
};

struct client {
    uv_tcp_t uv_client;
    server_t * server;
    void * data;
};


server_t * server_new(char * ip, unsigned short port);

int server_start_listener(server_t *server, 
                        int (*on_accept_cb)(server_t*, client_t*),
                        void (*on_read_cb)(client_t*, ssize_t, const uv_buf_t*));

#endif
