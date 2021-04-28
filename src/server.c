#include "server.h"
#include <stdlib.h>
#include <stdio.h>


#define container_of(ptr, type, member) \
  ((type *) ((char *) (ptr) - offsetof(type, member)))
  
static void my_alloc_cb(uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf);
static void on_new_connection(uv_stream_t *server, int status);
static void on_read_cb(uv_stream_t* stream, ssize_t nread, const uv_buf_t* buf);

server_t *server_new(char *ip, unsigned short port)
{
    server_t *server = (server_t *)malloc(sizeof(server_t));

    uv_loop_init(&server->loop);
    uv_ip4_addr(ip, port, &server->addr);

    return server;
}

int server_start_listener(server_t *server, 
                  int (*on_accept_cb)(server_t*, uv_tcp_t*), 
                  int (*on_read_cb)(server_t*, uv_tcp_t*))
{
    server->on_accept_cb = on_accept_cb;
    server->on_read_cb = on_read_cb;
    server->id = 1000;


    uv_tcp_init(&server->loop, &server->uv_server);
    uv_tcp_bind(&server->uv_server, (const struct sockaddr *)&server->addr, 0);

    int result = uv_listen((uv_stream_t *)&server->uv_server, 1024, on_new_connection);
    if (result)
    {
        fprintf(stderr, "Listen error %s\n", uv_strerror(result));
        return 1;
    }

    return uv_run(&server->loop, UV_RUN_DEFAULT);
}

static void on_read_cb(uv_stream_t* stream, ssize_t nread, const uv_buf_t* buf) {
    printf("%s", buf->base);
}

static void my_alloc_cb(uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf)
{
    buf->base = (char *)malloc(suggested_size);
    buf->len = suggested_size;
}

static void on_new_connection(uv_stream_t *server, int status)
{
    if (status < 0)
    {
        fprintf(stderr, "New connection error %s\n", uv_strerror(status));
        return;
    }

    uv_tcp_t *client = (uv_tcp_t *)malloc(sizeof(uv_tcp_t));
    uv_tcp_init(server->loop, client);

    if (uv_accept(server, (uv_stream_t *)client) != 0)
    {
        fprintf(stderr, "Accept: fail %s\n", uv_strerror(status));
        free(client);
        return;
    }

    uv_tcp_t * tcpserver = (uv_tcp_t*)server;
    server_t * myserver = container_of(tcpserver, server_t, uv_server);
    if(myserver->on_accept_cb != NULL && myserver->on_accept_cb(myserver, client) != 0)
    {
        fprintf(stderr, "%s\n", "Conexão não aceita por parte do servidor");
        return;
    }
        
    uv_read_start((uv_stream_t *)client, my_alloc_cb, on_read_cb);
}
