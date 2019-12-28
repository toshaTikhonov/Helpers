#include "h_memmgr.h"
#include "h_memory.h"


/* memory function pointers */
static h_malloc_t do_malloc = h_mem_malloc;
static h_realloc_t do_realloc = h_mem_realloc;
static h_free_t do_free = h_mem_free;

void * h_malloc(size_t size)
{
  if (!size)
    return NULL;
  else
    return (*do_malloc)(size);
}

void * h_realloc(void * ptr, size_t size)
{
  if (!size)
    return NULL;
  else
    return (*do_realloc)(ptr, size);
}

void h_free(void * ptr)
{
  if (ptr == NULL)
    return;
  else
    (*do_free)(ptr);
}

void h_set_alloc_funcs(h_malloc_t malloc_fn, h_realloc_t realloc_fn, h_free_t free_fn)
{
  do_malloc = malloc_fn;
  do_realloc = realloc_fn;
  do_free = free_fn;
}

void h_get_alloc_funcs(h_malloc_t * malloc_fn, h_realloc_t * realloc_fn, h_free_t * free_fn)
{
  if (malloc_fn)
    *malloc_fn = do_malloc;
  if (realloc_fn)
    *realloc_fn = do_realloc;
  if (free_fn)
    *free_fn = do_free;
}

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
void* h_MemSet(void *dest, int val, size_t len)
{
    unsigned char *ptr = dest;
    while (len-- > 0)
       *ptr++ = val;
    return dest;
}