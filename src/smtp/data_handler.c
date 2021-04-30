
#include "data_handler.h"
#include "server.h"
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "platform/unistd.h"

void smtp_data_handler(struct smtp_session* session, string_t * data) {
    if(session->state == RCPT_TO) {
        session->state = WRITTEN_DATA;
        return;
    }

    if(session->state != WRITTEN_DATA) {
        //send error
        return;
    }

    if(session->data_buffer == NULL) {
         session->data_buffer = tmpfile();
    }

    FILE *pfile = session->data_buffer;
    int pid = fileno(pfile);

    struct stat stats;
    fstat(pid, &stats);

    float sizeInMb = stats.st_size / (float)(1024 * 1024);
    if(sizeInMb < 10) {
        fwrite(data->c_str, sizeof(char), data->len, pfile);
        fflush(pfile);
    } else {
        fclose(pfile);
    }
}
