#include "smtp.h"
#include "server.h"
#include "util/string.h"
#include "string.h"
#include <stdio.h>
#include <stdlib.h>

#define container_of(ptr, type, member) \
    ((type *)((char *)(ptr)-offsetof(type, member)))

static int on_accept(server_t *server, client_t *client);
static void on_message(client_t *client, ssize_t nsize, const uv_buf_t *buf);

struct smtp_session
{
    int id;
    client_t *client;
    string_t *buffer;
};

int smtp_init()
{
    unsigned short port = 8080;

    server_t *server = server_new("127.0.0.1", port);
    printf("[info] Starting SMTP server on port: %d\n", port);

    return server_start_listener(server, on_accept, on_message);
}

static void on_message(client_t *client, ssize_t nsize, const uv_buf_t *buf)
{
    struct smtp_session * session = container_of(&client, struct smtp_session, client);
    string_t * buffer = session->buffer;

    str_ncat(buffer, buf->base, buf->len);

    if(session->buffer->len >= 4) {
        // Assumindo lentidoes, pode vir mais de uma informação ao mesmo tempo
        // Porem, não sei se deve ser um comportamento esperado do protocolo
        // Caso seja, terá que dar um split no texto e adicionar o sobressalente ao buffer
        int isend = strncmp(buf->base[buf->len - 4], "CRLF",4);

        if(isend == 0) {
            // Processa comando
        }
    }

    printf("%s", buf->base);
    fflush(stdout);
}

static int on_accept(server_t *server, client_t *client)
{
    struct smtp_session *session = (struct smtp_session*) malloc(sizeof(struct smtp_session));
    session->client = client;
    session->buffer = str_new_cap("", 512);
    session->id = 1;

    return 0;
}
