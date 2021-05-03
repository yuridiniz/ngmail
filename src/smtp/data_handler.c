
#include "data_handler.h"
#include "server.h"
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "platform/unistd.h"

void smtp_data_handler(struct smtp_session* session, string_t * data) {
    if(session->data_buffer == 0) {
        session->file_buffer_name = str_new("mailincommingXXXXXX");
        session->data_buffer = mkstemp(session->file_buffer_name->c_str);
    }

    struct stat stats;
    fstat(session->data_buffer, &stats);

    float sizeInMb = stats.st_size / (float)(1024 * 1024);
    if(sizeInMb < 10) {
        write(session->data_buffer, data->c_str, data->len);

        char *stop_command = "\r\n.\r\n";

        if(str_endswith(data, stop_command, strlen(stop_command)) == 0)  {
            session->state = DATA_COMPLETE;

            //TODO Enfileirar mensagem
        }

    } else {
        close(session->data_buffer);
        remove(session->file_buffer_name->c_str);

        session->data_buffer = 0;
    }
}
