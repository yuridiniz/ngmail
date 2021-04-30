#ifndef __RCPT_TO_HANDLER_H
#define __RCPT_TO_HANDLER_H

#include "smtp.h"
#include "string.h"

void smtp_rcpt_to_handler(struct smtp_session* session, string_t * data);

#endif
