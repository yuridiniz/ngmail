#include "smtp.h"
#include "string.h"
#include "command_handler.h"
#include <stdio.h>
#include <stdlib.h>

static int on_accept(server_t *server, client_t *client);
static void on_message(client_t *client, ssize_t nsize, const uv_buf_t *buf);

int smtp_init()
{
    unsigned short port = 8080;

    server_t *server = server_new("127.0.0.1", port);
    printf("[info] Starting SMTP server on port: %d\n", port);

    return server_start_listener(server, on_accept, on_message);
}

static int has_command_ends(string_t *buffer)
{
    // Assumindo lentidoes, pode vir mais de uma informação ao mesmo tempo, ou seja
    // Concatenando 2 comandos em uma única string
    // Ex: COMMAND abc \r\n COMMAND2 xyz \r\n
    // Porem, não sei se deve ser um comportamento esperado do protocolo
    // Caso seja, terá que dar um split no texto e adicionar o sobressalente ao buffer
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
    if (buffer->len <= 4)
        return;

    if (session->state != WRITTEN_DATA)
    {
        int isend = has_command_ends(buffer);
        if (isend)
        {
            string_t *buffer_param = str_clone(buffer);
            str_clear(buffer);

            printf("[debug] Processando comando: %s", buffer_param->c_str);
            handler_smpt_command(session, buffer_param);
        }
    }
    else
    {
        //Deve salvar o buffer no arquivo quando exceder sua capacidade ou quando terminar a execução do comando
        int isend = has_command_ends(buffer);
        if (isend)
        {
            session->state = DATA_COMPLETE;
        }
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
