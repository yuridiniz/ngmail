#include "helo_handler.h"

void smtp_helo_handler(struct smtp_session* session, string_t * data) {
    session->state = HELO_DONE;
}
