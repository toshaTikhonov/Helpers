#ifndef __H_MEMMGR_H__
#define __H_MEMMGR_H__

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define POOL_SIZE 8 * 1024
#define MIN_POOL_ALLOC_QUANTAS 16

void h_mem_init(void);

// 'malloc' clone
//
void * h_mem_malloc(size_t size);

// 'realoc' clone
//
void * h_mem_realloc(void * ptr, size_t size);

// 'free' clone
//
void h_mem_free(void* ap);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
