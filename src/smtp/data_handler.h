#ifndef __DATA_HANDLER_H
#define __DATA_HANDLER_H

#include "smtp.h"
#include "string.h"
#include "server.h"

void smtp_data_handler(struct smtp_session* session, string_t * data);

#endif