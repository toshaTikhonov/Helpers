#include "h_memmgr.h"

typedef unsigned int Align;
/**
 * объединение для реализации пула памяти
 */
union mem_header_union
{
    struct
    {
        /*
         * Pointer to the next block in the free list
         */
        union mem_header_union* next;
        /*
         * Size of the block (in quantas of sizeof(mem_header_t))
         */
        unsigned int size;
    } s;
    /*
     * Used to align headers in memory to a boundary
     */
    Align align_dummy;
};

typedef union mem_header_union mem_header_t;
/**
 * Initial empty list
 */
static mem_header_t base;

/**
 * Start of free list
 */
static mem_header_t* freep = 0;
/**
 * статический пул памяти для приложения
 */
static unsigned char pool[POOL_SIZE] = {0};
static unsigned int pool_free_pos = 0;
/**
  @brief выделение блоков памяти из пула.
  @param quantas -   колличество блоков памяти.
  @return mem_header_t указатель на структуру памяти.
*/
static mem_header_t* get_mem_from_pool(unsigned int quantas)
{
    unsigned int total_req_size;

    mem_header_t* h;

    if (quantas < MIN_POOL_ALLOC_QUANTAS)
        quantas = MIN_POOL_ALLOC_QUANTAS;

    total_req_size = quantas * sizeof(mem_header_t);

    if (pool_free_pos + total_req_size <= POOL_SIZE)
    {
        h = (mem_header_t*) (pool + pool_free_pos);
        h->s.size = quantas;
        h_mem_free((void*) (h + 1));
        pool_free_pos += total_req_size;
    }
    else
    {
        return 0;
    }

    return freep;
}
/**
  @brief инициализация пула.
  @param void  .
  @return void .
*/
void h_mem_init(void)
{
    base.s.next = 0;
    base.s.size = 0;
    freep = 0;
    pool_free_pos = 0;
}
/**
  @brief выделение памяти (аналог malloc) в пуле.
  @param size   размер выделяемой памяти.
  @return void*   Указатель на выделенную память.
*/
void * h_mem_malloc(size_t size)
{
    mem_header_t* p;
    mem_header_t* prevp;

    /*
     * Calculate how many quantas are required: we need enough to house all
     * the requested bytes, plus the header. The -1 and +1 are there to make sure
     * that if nbytes is a multiple of nquantas, we don't allocate too much
     */
    unsigned int nquantas = (size + sizeof(mem_header_t) - 1) / sizeof(mem_header_t) + 1;

    /*
     * First alloc call, and no free list yet ? Use 'base' for an initial
     * denegerate block of size 0, which points to itself
     */
    if ((prevp = freep) == 0)
    {
        base.s.next = freep = prevp = &base;
        base.s.size = 0;
    }

    for (p = prevp->s.next; ; prevp = p, p = p->s.next)
    {
        /* big enough ? */
        if (p->s.size >= nquantas)
        {
            /* exactly ? */
            if (p->s.size == nquantas)
            {
                /*
                 * just eliminate this block from the free list by pointing
                 * its prev's next to its next
                 */
                prevp->s.next = p->s.next;
            }
            else /* too big */
            {
                p->s.size -= nquantas;
                p += p->s.size;
                p->s.size = nquantas;
            }

            freep = prevp;
            return (void*) (p + 1);
        }
            /*
             * Reached end of free list ?
             * Try to allocate the block from the pool. If that succeeds,
             * get_mem_from_pool adds the new block to the free list and
             * it will be found in the following iterations. If the call
             * to get_mem_from_pool doesn't succeed, we've run out of
             * memory
             */
        else if (p == freep)
        {
            if ((p = get_mem_from_pool(nquantas)) == 0)
            {
                return 0;
            }
        }
    }
}
/**
  @brief расширение буфера памяти (аналог realloc)  в пуле.
  @param ptr    указатель на буфер память которого нужно увеличить.
  @param size   размер выделяемой памяти.
  @return void*   Указатель на выделенную память.
*/
void * h_mem_realloc(void * ptr, size_t size)
{
    h_mem_free(ptr);
    ptr = h_mem_malloc(size);
    return ptr;
}
/**
  @brief освобождение буфера памяти (аналог free) в пуле..
  @param ap    указатель на буфер памяти.
  @return void  .
*/
void h_mem_free(void* ap)
{
    mem_header_t* block;
    mem_header_t* p;

    /* acquire pointer to block header */
    block = ((mem_header_t*) ap) - 1;

    /*
     * Find the correct place to place the block in (the free list is sorted by
     * address, increasing order)
     */
    for (p = freep; !(block > p && block < p->s.next); p = p->s.next)
    {
        /*
         * Since the free list is circular, there is one link where a
         * higher-addressed block points to a lower-addressed block.
         * This condition checks if the block should be actually
         * inserted between them
         */
        if (p >= p->s.next && (block > p || block < p->s.next))
            break;
    }

    /*
     * Try to combine with the higher neighbor
     */
    if (block + block->s.size == p->s.next)
    {
        block->s.size += p->s.next->s.size;
        block->s.next = p->s.next->s.next;
    }
    else
    {
        block->s.next = p->s.next;
    }

    /*
     * Try to combine with the lower neighbor
     */
    if (p + p->s.size == block)
    {
        p->s.size += block->s.size;
        p->s.next = block->s.next;
    }
    else
    {
        p->s.next = block;
    }

    freep = p;
}
