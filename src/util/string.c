
#include "string.h"
#include <stdlib.h>
#include <string.h>

string_t *str_new_s_cap(char *str, int size, int capacity)
{
    string_t *result = malloc(sizeof(string_t));
    result->len = size;
    result->c_str = malloc(size + capacity);
    result->capacity = capacity;

    result->c_str[0] = '\0';

    if (result->len > 0)
    {
        memcpy(result->c_str, str, result->len);
    }

    return result;
}

string_t *str_new(char *str)
{
    return str_new_s_cap(str, strlen(str), 0);
}

string_t *str_new_cap(char *str, unsigned short capacity)
{
    return str_new_s_cap(str, strlen(str), capacity);
}

static void grow_buffer_if_needed(string_t *str, int size)
{
    if (size > str->len + (int)str->capacity)
    {
        int new_size = str->len + size + str->capacity;
        str->c_str = realloc(str->c_str, new_size);
    }
}

void str_cat(string_t *str, char *new_val)
{
    // TODO Não fazer essa abstração para não precisar de 2 loops (1 para contar o arra de char outro para copiar)
    int size = strlen(new_val);
    str_ncat(str, new_val, size);
}

void str_ncat(string_t *str, char *new_val, int size)
{
    grow_buffer_if_needed(str, size);

    char *start = &str->c_str[str->len];
    memcpy(start, new_val, size);

    str->len += size;

    str->c_str[str->len] = '\0';
}

void str_clear(string_t *str)
{
    if (str->capacity > 0 && str->len > str->capacity)
    {
        str->c_str = realloc(str->c_str, str->capacity);
    }

    str->c_str[0] = '\0';
    str->len = 0;
}

int str_startwith(string_t *str, char *val)
{
    char *ptr = str->c_str;
    while (*val != '\0')
    {
        int equals = *val - *ptr;
        if (equals != 0)
            return equals;

        ++val;
        ++ptr;
    }

    return 0;
}


int str_endswith(string_t *str, char *data, int val_len)
{
    char *ptr = &str->c_str[str->len];
    char *val = &data[val_len];

    while (val_len > 0)
    {
        --val_len;
        --val;
        --ptr;

        int equals = *val - *ptr;
        if (equals != 0)
            return equals;
    }

    return 0;
}

string_t *str_clone(string_t *str)
{
    return str_new_s_cap(str->c_str, str->len, str->capacity);
}

void str_free(string_t *str)
{
    free(str->c_str);
    free(str);
}
