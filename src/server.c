#include "server.h"
#include <stdlib.h>
#include <stdio.h>

#define container_of(ptr, type, member) \
    ((type *)((char *)(ptr)-offsetof(type, member)))

static void my_alloc_cb(uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf);
static void on_new_connection(uv_stream_t *server, int status);
static void on_read_cb(uv_stream_t *stream, ssize_t nread, const uv_buf_t *buf);

server_t *server_new(char *ip, unsigned short port)
{
    server_t *server = (server_t *)malloc(sizeof(server_t));
    server->loop.data = server;
    server->uv_server.data = server;

    uv_loop_init(&server->loop);
    uv_ip4_addr(ip, port, (struct sockaddr_in *)&server->addr);

    return server;
}

server_t *server_new_ip6(char *ip, unsigned short port)
{
    server_t *server = (server_t *)malloc(sizeof(server_t));
    server->loop.data = server;
    server->uv_server.data = server;

    uv_loop_init(&server->loop);
    uv_ip6_addr(ip, port, (struct sockaddr_in6 *)&server->addr);

    return server;
}

int server_start_listener(server_t *server,
                          int (*on_accept_cb)(server_t *, client_t *),
                          void (*on_read_cb)(client_t *, ssize_t, const uv_buf_t *))
{
    server->on_accept_cb = on_accept_cb;
    server->on_read_cb = on_read_cb;

    uv_tcp_init(&server->loop, &server->uv_server);
    int res = uv_tcp_bind(&server->uv_server, (const struct sockaddr *)&server->addr, 0);
    if (res)
    {
        fprintf(stderr, "Error bind %s\n", uv_strerror(res));
        return 1;
    }

    int result = uv_listen((uv_stream_t *)&server->uv_server, 1024, on_new_connection);
    if (result)
    {
        fprintf(stderr, "Listen error %s\n", uv_strerror(result));
        return 1;
    }

    return uv_run(&server->loop, UV_RUN_DEFAULT);
}

void server_write(client_t *client, char *data, int len)
{
    uv_write_t req1;

    uv_buf_t b[] = {
        {.base = data, .len = len},
    };

    uv_write(&req1, (uv_stream_t *)&client->uv_client, b, 1, NULL);
}

static void on_read_cb(uv_stream_t *stream, ssize_t nread, const uv_buf_t *buf)
{
    client_t *client = stream->data;

    if (client->server->on_read_cb != NULL)
    {
        client_t *move = client;
        client->server->on_read_cb(move, nread, buf);
    }
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

    client_t *client = (client_t *)malloc(sizeof(client_t));
    uv_tcp_init(server->loop, &client->uv_client);

    if (uv_accept(server, (uv_stream_t *)&client->uv_client) != 0)
    {
        fprintf(stderr, "Accept: fail %s\n", uv_strerror(status));
        free(client);
        return;
    }

    client->uv_client.data = client;

    server_t *myserver = (server_t *)server->data;
    client->server = myserver;

    if (myserver->on_accept_cb != NULL && myserver->on_accept_cb(myserver, client) != 0)
    {
        fprintf(stderr, "%s\n", "Conexão não aceita por parte do servidor");
        return;
    }

    uv_read_start((uv_stream_t *)client, my_alloc_cb, on_read_cb);
}
