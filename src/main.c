#include "platform/load_module.h"
#include "util/string.h"
#include <stdio.h>

int main(int argc, char** argv) {
    string_t * mystr = str_new("Hello");
    
    printf("%s", mystr->c_str);

    str_free(mystr);

    return 0;
}
