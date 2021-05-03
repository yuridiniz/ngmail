
#include "command_handler.h"
#include "server.h"
#include "stdio.h"

int handler_helo_if_request(struct smtp_session *session, string_t *command)
{
    if (str_startwith(command, "HELO") == 0)
    {
        session->state = HELO_DONE;

        char *response = "250 OK\r\n";
        server_write(session->client, response, strlen(response));

        return 0;
    }
    else if (str_startwith(command, "EHLO") == 0)
    {
        // session->state = HELO_DONE;

        char *response = "502 Command not recognized\r\n";
        server_write(session->client, response, strlen(response));

        return 0;
    }

    return -1;
}

void handler_smpt_command(struct smtp_session *session, string_t *command)
{
    printf("%s", command->c_str);
    fflush(stdout);

    switch (session->state)
    {

    case HELO_PENDING:
        handler_helo_if_request(session, command);
        break;

    case HELO_DONE:
        if (handler_helo_if_request(session, command) == 0)
            return;

        if (str_startwith(command, "MAIL FROM:") == 0)
        {
            session->state = MAIL_TO;

            char *response = "250 OK\r\n";
            server_write(session->client, response, strlen(response));
        }

        break;

    case MAIL_TO:
        if (handler_helo_if_request(session, command) == 0)
            return;

        if (str_startwith(command, "RCPT TO:") == 0)
        {
            session->state = RCPT_TO;

            char *response = "250 OK\r\n";
            server_write(session->client, response, strlen(response));
        }

        break;

    case RCPT_TO:
        if (handler_helo_if_request(session, command) == 0)
        {
            return;
        }

        if (str_startwith(command, "DATA") == 0)
        {
            session->state = WRITTEN_DATA;
            char *response = "354\r\n";
            server_write(session->client, response, strlen(response));
        }

        break;

    case WRITTEN_DATA:
        smtp_data_handler(session, command);

        break;

    case DATA_COMPLETE:
        if (handler_helo_if_request(session, command) == 0)
        {
            return;
        }

        break;

    default:
        break;
    }
}