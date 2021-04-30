#ifndef __MAIL_FROM_HANDLER_H
#define __MAIL_FROM_HANDLER_H

#include "smtp.h"
#include "string.h"

void smtp_mail_from_handler(struct smtp_session* session, string_t * data);

#endif