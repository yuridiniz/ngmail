#include "smtp.h"
#include "server.h"

static int on_accept(server_t *server, uv_tcp_t * client);

int smtp_init() {
    server_t *server = server_new("0.0.0.0", 8090);
    return server_start_listener(server, on_accept, NULL);
}

static int on_accept(server_t *server, uv_tcp_t * client) {

    server->id =5;
    return 0;
}


