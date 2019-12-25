#include <stdlib.h>
#include "h_memory.h"

/* memory function pointers */
static o_malloc_t do_malloc = malloc;
static o_realloc_t do_realloc = realloc;
static o_free_t do_free = free;

void * o_malloc(size_t size) {
  if (!size) {
    return NULL;
  } else {
    return (*do_malloc)(size);
  }
}

void * o_realloc(void * ptr, size_t size) {
  if (!size) {
    return NULL;
  } else {
    return (*do_realloc)(ptr, size);
  }
}

void o_free(void * ptr) {
  if (ptr == NULL) {
    return;
  } else {
    (*do_free)(ptr);
  }
}

void o_set_alloc_funcs(o_malloc_t malloc_fn, o_realloc_t realloc_fn, o_free_t free_fn) {
  do_malloc = malloc_fn;
  do_realloc = realloc_fn;
  do_free = free_fn;
}

void o_get_alloc_funcs(o_malloc_t * malloc_fn, o_realloc_t * realloc_fn, o_free_t * free_fn) {
  if (malloc_fn) {
    *malloc_fn = do_malloc;
  }
  if (realloc_fn) {
    *realloc_fn = do_realloc;
  }
  if (free_fn) {
    *free_fn = do_free;
  }
}
