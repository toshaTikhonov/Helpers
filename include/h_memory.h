#ifndef __H_MEMORY_H__
#define __H_MEMORY_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#undef malloc
#undef realloc
#undef free

typedef void *(*o_malloc_t)(size_t);
typedef void *(*o_realloc_t)(void *, size_t);
typedef void (*o_free_t)(void *);

void * o_malloc(size_t size);
void * o_realloc(void * ptr, size_t size);
void o_free(void * ptr);
void o_set_alloc_funcs(o_malloc_t malloc_fn, o_realloc_t realloc_fn, o_free_t free_fn);
void o_get_alloc_funcs(o_malloc_t * malloc_fn, o_realloc_t * realloc_fn, o_free_t * free_fn);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
