
#include <stdlib.h>

typedef struct string string_t;
struct string {
    char * c_str;
    unsigned char capacity;
    int len;
};

string_t * str_new(char * str);

void str_free(string_t * str);
