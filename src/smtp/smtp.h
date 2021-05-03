#ifndef __SMTP_H
#define __SMTP_H

#include "server.h"
#include "util/string.h"

enum smtp_session_state {
    HELO_PENDING,
    HELO_DONE,
    MAIL_TO,
    RCPT_TO,
    SETTING_COMPLETE,
    WRITTEN_DATA,
    DATA_COMPLETE,
};

struct smtp_session
{
    enum smtp_session_state state;
    int id;
    client_t *client;
    string_t *command_buffer;
    string_t *file_buffer_name;
    int data_buffer;
};


int smtp_init(char * ip, unsigned short port);

#endif
