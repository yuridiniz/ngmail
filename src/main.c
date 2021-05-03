#include "smtp/smtp.h"
#include "http/http.h"
#include <stdio.h>

int main(int argc, char **argv)
{
    http_init("0.0.0.0", 8090);
    smtp_init("0.0.0.0", 25);

    while (1) {
        getchar();
    }

    return 0;
}
