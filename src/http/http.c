#include "http.h"
#include "platform/thread.h"
#include "string.h"
#include <stdio.h>
#include <stdlib.h>

static int on_accept(server_t *server, client_t *client);
static void on_message(client_t *client, ssize_t nsize, const uv_buf_t *buf);

static void * __thread_server(void *arg)
{
    server_t *server = (server_t *)arg;

    int err = server_start_listener(server, on_accept, on_message);
    if (err != 0)
    {
        fprintf(stderr, "[err] Fail to start HTTP: %s\n", uv_err_name(err));
    }

    return 0;
}

int http_init(char *ip, unsigned short port)
{
    server_t *server = server_new(ip, port);
    printf("[info] Starting HTTP server on port: %d\n", port);

    pthread_t server_thread;
    pthread_create(&server_thread, NULL, &__thread_server, server);

    return 0;
}

static void on_message(client_t *client, ssize_t nsize, const uv_buf_t *buf)
{
    char raw[] = "HTTP/1.1 200 OK\r\n\
Date: Sun, 10 Oct 2010 23:26:07 GMT\r\n\
Server: Apache/2.2.8 (Ubuntu) mod_ssl/2.2.8 OpenSSL/0.9.8g\r\n\
Last-Modified: Sun, 26 Sep 2010 22:04:35 GMT\r\n\
ETag: \"45b6-834-49130cc1182c0\"\r\n\
Accept-Ranges: bytes\r\n\
Content-Length: 12\r\n\
Connection: close\r\n\
Content-Type: text/html\r\n\
\r\n\
Hello world!\r\n";

    server_write(client, raw, strlen(raw));
}

static int on_accept(server_t *server, client_t *client)
{
    return 0;
}
