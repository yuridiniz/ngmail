#include "server.h"
#include "util/string.h"

enum smtp_session_state {
    HELO_PENDING,
    HELO_DONE,
    MAIL_FROM,
    MAIL_TO,
    WRITTEN_DATA,
    DATA_COMPLETE,
};

struct smtp_session
{
    enum smtp_session_state state;
    int id;
    client_t *client;
    string_t *buffer;
};


int smtp_init();
