
#include "command_handler.h"
#include "stdio.h"

int handler_helo_if_request(struct smtp_session *session, string_t *command)
{
    if (str_startwith(command, "HELO") == 0)
    {
        session->state = HELO_DONE;
        printf("%s", "HELO COMMNAD...\n");
        return 0;
    }
    else if (str_startwith(command, "HLEO") == 0)
    {
        session->state = HELO_DONE;
        printf("%s", "HLEO COMMNAD...\n");
        return 0;
    }

    return -1;
}

void handler_smpt_command(struct smtp_session *session, string_t *command)
{
    switch (session->state)
    {

    case HELO_PENDING:
        handler_helo_if_request(session, command);
        break;

    case HELO_DONE:
        if (handler_helo_if_request(session, command) == 0)
            return;

        if (str_startwith(command, "MAIL TO:") == 0)
        {
            session->state = MAIL_TO;
            printf("%s", "MAIL TO:\n");

            //handler
        }

        break;

    case MAIL_TO:
        if (handler_helo_if_request(session, command) == 0)
            return;

        if (str_startwith(command, "RCPT TO:") == 0)
        {
            session->state = RCPT_TO;
            printf("%s", "RCPT_TO...\n");
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
            printf("%s", "DATA...\n");
        }

        break;

    case WRITTEN_DATA:

        printf("%s", command->c_str);
        fflush(stdout);

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