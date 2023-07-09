#ifndef __H_MEMORY_H__
#define __H_MEMORY_H__

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @defgroup memmory функции по работе с памятью
 * эти функции реализуют работу с динамической памятью.
 * а также манипуляции с массивами
 * @{
 */

#undef malloc
#undef realloc
#undef free

/** указатели на функции, работающие с памятью */
typedef void *(*h_malloc_t)(size_t);
typedef void *(*h_realloc_t)(void *, size_t);
typedef void (*h_free_t)(void *);
/**
  @brief выделение памяти (аналог malloc).
  @param size   размер выделяемой памяти.
  @return void*   Указатель на выделенную память.
*/
void * h_malloc(size_t size);
/**
  @brief расширение буфера памяти (аналог realloc).
  @param ptr    указатель на буфер память которого нужно увеличить.
  @param size   размер выделяемой памяти.
  @return void*   Указатель на выделенную память.
*/
void * h_realloc(void * ptr, size_t size);
/**
  @brief освобождение буфера памяти (аналог free).
  @param ptr    указатель на буфер памяти.
*/
void h_free(void * ptr);
/**
  @brief установка функций по работе с памятью.
  @param malloc_fn    указатель на функцию malloc.
  @param realloc_fn   указатель на функцию realloc.
  @param free_fn      указатель на функцию free.
*/
void h_set_alloc_funcs(h_malloc_t malloc_fn, h_realloc_t realloc_fn, h_free_t free_fn);
/**
  @brief возврат функций по работе с памятью.
  @param malloc_fn    указатель на функцию malloc.
  @param realloc_fn   указатель на функцию realloc.
  @param free_fn      указатель на функцию free.
*/
void h_get_alloc_funcs(h_malloc_t * malloc_fn, h_realloc_t * realloc_fn, h_free_t * free_fn);
/**
  @brief копирование буфера памяти (аналог memcpy).
  @param dst    указатель на буфер памяти , куда копируем.
  @param src    указатель на буфер памяти , откуда копируем.
  @param size   размер .
  @return void*   Указатель dst.
*/
void*  h_MemCpy(void* dst, const void* src, size_t size);
/**
  @brief перенос буфера памяти (аналог memmove).
  @param dest    указатель на буфер памяти , куда.
  @param src    указатель на буфер памяти , откуда.
  @param len   размер .
  @return void*   Указатель dest.
*/
void* h_MemMove(void *dest, const void *src, size_t len);
/**
  @brief сравнение двух ,буферов (memcmp).
  @param str1  указатель на буфер 1.
  @param str2  указатель на буфер 2.
  @param count   размер .
  @return int    0 – если сравниваемее массивы идентичны..
 */
int h_MemCmp(const void *str1, const void *str2, size_t count);
/**
  @brief заполнение буфера памяти (аналог memset).
  @param dest    указатель на буфер памяти.
  @param val     значение заполнения.
  @param len   размер .
  @return void*   Указатель dest.
*/
void* h_MemSet(void *dest, int val, size_t len);

/**
 * @}
 */
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
