            
#ifndef __COMMAND_HANDLER_H
#define __COMMAND_HANDLER_H

#include "smtp.h"
#include "string.h"

void handler_smpt_command(struct smtp_session* session, string_t * buffer_param);

#endif