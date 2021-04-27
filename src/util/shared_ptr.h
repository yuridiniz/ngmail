
#include <stdlib.h>

void *shared_ptr(size_t size, void (*destructor)(void *));
void shared_ptr_free(void * ptr);
void *shared_ptr_ref(void * ptr);
void shared_ptr_unref(void * ptr);
