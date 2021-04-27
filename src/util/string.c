
#include "string.h"
#include <stdlib.h>
#include <string.h>

string_t * str_new(char * str) {
    string_t * result = malloc(sizeof(string_t));

    //TODO Copy
    result->c_str = str;
    result->capacity = 0;
    result->len = strlen(str);

    return result;
}
void str_free(string_t * str) {
    free(str);
}


