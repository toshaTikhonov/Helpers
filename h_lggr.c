#include <stdio.h>
#include <memory.h>
#include <time.h>
#include <stdarg.h>
#include "h_lggr.h"

static int log_level = 0;


static unsigned int h_get_time(void)
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (unsigned int) ts.tv_sec * 1000 + ts.tv_nsec / 1000 / 1000;
}
static void h_lggr_print_log( const char* pszFmt, va_list* valist )
{
    char buf[256];
    if (valist)
    {
        vsprintf(buf,pszFmt,*valist);
        printf("%s",buf);
    }
    else
    {
        printf("%s",pszFmt);
    }
}
static void h_lggr_generate_time(char* buffer, unsigned int size)
{
    unsigned int tickcount = h_get_time();
    snprintf(buffer,size,"[%d:%d]",tickcount / 1000, tickcount % 1000);
}
void h_lggr_printf_line(const char *pszFmt, ...)
{
  char Buffer[32];
  int level;
  va_list lists;
  va_list args;

  va_start(lists, pszFmt);
  level = log_level;
  va_copy(args, lists);
  while ( level > 0 )
  {
    h_lggr_print_log("    ", 0);
    --level;
  }
  h_lggr_generate_time(Buffer, sizeof(Buffer));
  h_lggr_print_log(Buffer, 0);
  h_lggr_print_log(pszFmt, &args);
  h_lggr_print_log("\r\n", 0);
  va_end(args);
  va_end(lists);
}
void h_lggr_print_memory(const char *psz_title, const void *p_p_data, unsigned int lsize)
{
    char buff[34];
    unsigned int pos;
    int i;
    unsigned char* p_data = (unsigned char*)p_p_data;

    h_lggr_printf_line("%s(%d bytes):", psz_title, lsize);
    memset(buff,0, sizeof(buff));
    for(i = 0; i < lsize; i++)
    {
        pos = strlen(buff);
        sprintf(&buff[pos],"%02X ",p_data[i]);
        if (i + 1 == lsize || !((i + 1) % 0xF))
        {
            h_lggr_printf_line("%s", buff);
            memset(buff,0, sizeof(buff));
        }
    }
}
void h_lggr_inc_level( void )
{
    ++log_level;
}
void h_lggr_dec_level( void )
{
    --log_level;
}
