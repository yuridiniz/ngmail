#include <uv.h>

typedef struct cliente client_t;
typedef struct server server_t;

struct server {

    int id;
    uv_loop_t loop;
    uv_tcp_t uv_server;
    struct sockaddr_in addr;
    int (*on_accept_cb)(server_t*, uv_tcp_t*);
    int (*on_read_cb)(server_t*, uv_tcp_t*);
};

struct server {
    int id;
    uv_loop_t loop;
    uv_tcp_t uv_server;
    struct sockaddr_in addr;
    int (*on_accept_cb)(server_t*, uv_tcp_t*);
    int (*on_read_cb)(server_t*, uv_tcp_t*);
};


server_t * server_new(char * ip, unsigned short port);

int server_start_listener(server_t *server, 
                        int (*on_accept_cb)(server_t*, uv_tcp_t*),
                        int (*on_read_cb)(server_t*, uv_tcp_t*));


