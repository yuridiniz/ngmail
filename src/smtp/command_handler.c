
#include "command_handler.h"
#include "stdio.h"

void handler_smpt_command(struct smtp_session *session, string_t *command)
{
    if (str_startwith(command, "HELO"))
    {
        printf("%s", "HELO COMMNAD...");
    }
    else if (str_startwith(command, "HLEO"))
    {
        printf("%s", "HLEO COMMNAD...");
    }
}