
#include <stdlib.h>

typedef struct string string_t;
struct string {
    char * c_str;
    unsigned char capacity;
    int len;
};

string_t * str_new(char * str);
string_t * str_new_cap(char * str, char capacity);

void str_ncat(string_t * str, char * new_val, int size);

void str_free(string_t * str);
