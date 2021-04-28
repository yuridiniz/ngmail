
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


string_t * str_new_cap(char * str, char capacity) 
{
    string_t * result = malloc(sizeof(string_t));

    //TODO Copy
    result->c_str = str;
    result->len = strlen(str);
    result->capacity = capacity - result->len;

    return result;
}

void str_ncat(string_t * str, char * new_val, int size) {
    //TODO IMPLEMENTAR
}

void str_free(string_t * str) {
    free(str);
}


