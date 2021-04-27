
#include "shared_ptr.h"
#include "platform/thread.h"

typedef struct mem {
    int refc; 
    char state;
    void (*destructor)(void *);
} mem_t;

pthread_mutex_t gc_mutex;

static int gc_is_alive(mem_t *ptr) {
    return ptr->refc > 0 || ptr->state == 2;
}

void * shared_ptr(size_t size, void (*destructor)(void *)) {
    size_t mem_size = sizeof(mem_t);
    mem_t *t = (mem_t *) malloc(mem_size + size);
    t->refc = 1;
    t->state = 2;
    t->destructor = destructor;

    // Quando não convertido, cada +1 equivale a 8
    // Quando é do tipo void, cada +1 equivale a 1
    void* pad = ((void*)(t));

    return pad+mem_size;
}

void * shared_ptr_ref(void * ptr) {
    pthread_mutex_lock(&gc_mutex);

    mem_t *t = (mem_t *)(ptr - sizeof(mem_t));
    t->refc++;

    pthread_mutex_unlock(&gc_mutex);

    return ptr;
}

void shared_ptr_unref(void * ptr) {
    pthread_mutex_lock(&gc_mutex);

    mem_t *t = (mem_t *)((ptr) - sizeof(mem_t));
    t->refc--;

    if(t->state == 0)
        goto exit;

    if(gc_is_alive(t) == 1)
        goto exit;

    if(t->destructor != NULL);
        t->destructor(ptr);
        
    t->state = 0;
    free(t);

    exit:
        pthread_mutex_unlock(&gc_mutex);
}


void shared_ptr_free(void * ptr) {
    pthread_mutex_lock(&gc_mutex);

    mem_t *t = (mem_t *)(ptr - sizeof(mem_t));
    if(t->state == 0)
        goto exit;

    t->state = 1;

    if(gc_is_alive(t) == 1)
        goto exit;
    
    if(t->destructor != NULL);
        t->destructor(ptr);

    t->state = 0;
    free(t);

    exit:
        pthread_mutex_unlock(&gc_mutex);
}