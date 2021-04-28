#include "smtp.h"
#include "server.h"

static int on_accept(server_t *server, client_t * client);

int smtp_init() {
    server_t *server = server_new("127.0.0.1", 587);
    return server_start_listener(server, on_accept, NULL);
}

static int on_accept(server_t *server, client_t * client) {

    return 0;
}


