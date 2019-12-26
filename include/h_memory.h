#ifndef __H_MEMORY_H__
#define __H_MEMORY_H__

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#undef malloc
#undef realloc
#undef free

typedef void *(*h_malloc_t)(size_t);
typedef void *(*h_realloc_t)(void *, size_t);
typedef void (*h_free_t)(void *);

void * h_malloc(size_t size);
void * h_realloc(void * ptr, size_t size);
void h_free(void * ptr);
void h_set_alloc_funcs(h_malloc_t malloc_fn, h_realloc_t realloc_fn, h_free_t free_fn);
void h_get_alloc_funcs(h_malloc_t * malloc_fn, h_realloc_t * realloc_fn, h_free_t * free_fn);
void*  h_MemCpy(void* dst, const void* src, size_t size);
void* h_MemMove(void *dest, const void *src, size_t len);
int h_MemCmp(const void *str1, const void *str2, size_t count);
void* h_MemSet(void *dest, int val, size_t len);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
