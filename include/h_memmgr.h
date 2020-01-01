#ifndef __H_MEMMGR_H__
#define __H_MEMMGR_H__

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
* @defgroup memmgr функции
* эти функции нужны для реализации выделения памяти из статического пула
* @{
*/


/* размер пула */
#define POOL_SIZE 8 * 1024
#define MIN_POOL_ALLOC_QUANTAS 16
/**
  @brief инициализация пула.
  @param void  .
  @return void .
*/
void h_mem_init(void);
/**
  @brief выделение памяти (аналог malloc) в пуле.
  @param size   размер выделяемой памяти.
  @return void*   Указатель на выделенную память.
*/
void * h_mem_malloc(size_t size);
/**
  @brief расширение буфера памяти (аналог realloc)  в пуле.
  @param ptr    указатель на буфер память которого нужно увеличить.
  @param size   размер выделяемой памяти.
  @return void*   Указатель на выделенную память.
*/
void * h_mem_realloc(void * ptr, size_t size);
/**
  @brief освобождение буфера памяти (аналог free) в пуле..
  @param ap    указатель на буфер памяти.
  @return void  .
*/
void h_mem_free(void* ap);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
