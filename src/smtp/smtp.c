#include "smtp.h"
#include "string.h"
#include "command_handler.h"
#include "platform/thread.h"
#include <stdio.h>
#include <stdlib.h>

static int on_accept(server_t *server, client_t *client);
static void on_message(client_t *client, ssize_t nsize, const uv_buf_t *buf);

static void __thread_server(void *arg)
{
    server_t *server = (server_t *)arg;

    server_start_listener(server, on_accept, on_message);
}

int smtp_init(const char *ip, unsigned short port)
{
    server_t *server = server_new(ip, port);

    printf("[info] Starting SMTP server on port: %d\n", port);

    pthread_t server_thread;
    pthread_create(&server_thread, NULL, &__thread_server, server);
}

static int has_command_ends(string_t *buffer)
{
    // Assumindo lentidoes, pode vir mais de uma informação ao mesmo tempo, ou seja
    // Concatenando 2 comandos em uma única string
    // Ex: COMMAND abc \r\n COMMAND2 xyz \r\n
    // Porem, não sei se deve ser um comportamento esperado do protocolo
    // Caso seja, terá que dar um split no texto e adicionar o sobressalente ao buffer
    if (buffer->len <= 4)
        return -1;

    char *ends = &buffer->c_str[((int)buffer->len) - 2];
    int isend = strncmp(ends, "\r\n", 2);
    return isend == 0;
}

static void on_message(client_t *client, ssize_t nsize, const uv_buf_t *buf)
{
    struct smtp_session *session = client->data;
    string_t *buffer = session->command_buffer;

    str_cat(buffer, buf->base);

    //Dados mínimos para ser um comando

    if (session->state == WRITTEN_DATA || has_command_ends(buffer) == 1)
    {
        string_t *buffer_param = str_clone(buffer);
        str_clear(buffer);

        handler_smpt_command(session, buffer_param);
    }
}

static int on_accept(server_t *server, client_t *client)
{
    struct smtp_session *session = (struct smtp_session *)malloc(sizeof(struct smtp_session));
    session->client = client;
    session->command_buffer = str_new_cap("", 1024);
    session->id = 1;
    session->state = HELO_PENDING;

    client->data = session;

    return 0;
}
