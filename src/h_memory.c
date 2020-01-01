#include "h_memmgr.h"
#include "h_memory.h"


/* указатели на функции, работающие с памятью */
#ifdef STATIC_MEMORY_POOL /* статический пул (нет динамической памяти)*/
static h_malloc_t do_malloc = h_mem_malloc;
static h_realloc_t do_realloc = h_mem_realloc;
static h_free_t do_free = h_mem_free;
#else
static h_malloc_t do_malloc = malloc;
static h_realloc_t do_realloc = realloc;
static h_free_t do_free = free;
#endif

/**
  @brief выделение памяти (аналог malloc).
  @param size   размер выделяемой памяти.
  @return void*   Указатель на выделенную память.
*/
void * h_malloc(size_t size)
{
  if (!size)
    return NULL;
  else
    return (*do_malloc)(size);
}
/**
  @brief расширение буфера памяти (аналог realloc).
  @param ptr    указатель на буфер память которого нужно увеличить.
  @param size   размер выделяемой памяти.
  @return void*   Указатель на выделенную память.
*/
void * h_realloc(void * ptr, size_t size)
{
  if (!size)
    return NULL;
  else
    return (*do_realloc)(ptr, size);
}
/**
  @brief освобождение буфера памяти (аналог free).
  @param ptr    указатель на буфер памяти.
  @return void  .
*/
void h_free(void * ptr)
{
  if (ptr == NULL)
    return;
  else
    (*do_free)(ptr);
}
/**
  @brief установка функций по работе с памятью.
  @param malloc_fn    указатель на функцию malloc.
  @param realloc_fn   указатель на функцию realloc.
  @param free_fn      указатель на функцию free.
  @return void  .
*/
void h_set_alloc_funcs(h_malloc_t malloc_fn, h_realloc_t realloc_fn, h_free_t free_fn)
{
  do_malloc = malloc_fn;
  do_realloc = realloc_fn;
  do_free = free_fn;
}
/**
  @brief возврат функций по работе с памятью.
  @param malloc_fn    указатель на функцию malloc.
  @param realloc_fn   указатель на функцию realloc.
  @param free_fn      указатель на функцию free.
  @return void  .
*/
void h_get_alloc_funcs(h_malloc_t * malloc_fn, h_realloc_t * realloc_fn, h_free_t * free_fn)
{
  if (malloc_fn)
    *malloc_fn = do_malloc;
  if (realloc_fn)
    *realloc_fn = do_realloc;
  if (free_fn)
    *free_fn = do_free;
}
/**
  @brief копирование буфера памяти (аналог memcpy).
  @param dst    указатель на буфер памяти , куда копируем.
  @param src    указатель на буфер памяти , откуда копируем.
  @param size   размер .
  @return void*   Указатель dst.
*/
void*  h_MemCpy(void* dst, const void* src, size_t size)
{
    void* tmp           = dst;
    unsigned char* _src = (unsigned char*) src;
    unsigned char* _dst = (unsigned char*) dst;
    size_t   len;
    for(len = size / 4u; len--; _src += 4u, _dst += 4u)
        *(size_t*) _dst = *(size_t*) _src;
    len = size % 4u;
    while(len--)
        *_dst++ = *_src++;
    return tmp;
}
/**
  @brief перенос буфера памяти (аналог memmove).
  @param dest    указатель на буфер памяти , куда.
  @param src    указатель на буфер памяти , откуда.
  @param len   размер .
  @return void*   Указатель dest.
*/
void* h_MemMove(void *dest, const void *src, size_t len)
{
    char *lasts;
    char *lastd;
    char *d = dest;
	const char *s = src;
	if (d < s)
	    while (len--)
	      *d++ = *s++;
	else
	{
	    lasts = (char*)s + (len-1);
	    lastd = d + (len-1);
	    while (len--)
	      *lastd-- = *lasts--;
	}
	return dest;
}
/**
  @brief сравнение двух ,буферов (memcmp).
  @param str1  указатель на буфер 1.
  @param str2  указатель на буфер 2.
  @param count   размер .
  @return int    0 – если сравниваемее массивы идентичны..
 */
int h_MemCmp(const void *str1, const void *str2, size_t count)
{
    const unsigned char *s1 = str1;
    const unsigned char *s2 = str2;
    while (count-- > 0)
    {
        if (*s1++ != *s2++)
            return s1[-1] < s2[-1] ? -1 : 1;
    }
    return 0;
}
/**
  @brief заполнение буфера памяти (аналог memset).
  @param dest    указатель на буфер памяти.
  @param val     значение заполнения.
  @param len   размер .
  @return void*   Указатель dest.
*/
void* h_MemSet(void *dest, int val, size_t len)
{
    unsigned char *ptr = dest;
    while (len-- > 0)
       *ptr++ = val;
    return dest;
}
