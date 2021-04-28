
#ifndef __STRING_T_H
#define __STRING_T_H

#include <stdlib.h>

typedef struct string string_t;
struct string {
    char * c_str;
    unsigned short capacity;
    int len;
};

string_t *str_new_s_cap(char *str, int size, int capacity);

string_t *str_new(char *str);

string_t *str_new_cap(char *str, unsigned short capacity);

void str_cat(string_t *str, char *new_val);

void str_ncat(string_t *str, char *new_val, int size);

void str_clear(string_t *str);

int str_startwith(string_t *str, char *val);

string_t * str_clone(string_t *str);

void str_free(string_t *str);

#endif