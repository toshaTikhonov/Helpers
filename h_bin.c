#include "h_bin.h"

/**
  @brief преобразование бинарных данных в формате big-endian в четырех байтовое целое
  @param p_buf - бинарных данных в формате big-endian
  @return 4-х байтовое целое
*/
unsigned int  h_BigEndianToUINT( unsigned char* p_buf )
{
    unsigned int res_uint;
    
    res_uint  = (unsigned int)(p_buf[0]); res_uint <<= 8;
    res_uint |= (unsigned int)(p_buf[1]); res_uint <<= 8;
    res_uint |= (unsigned int)(p_buf[2]); res_uint <<= 8;
    res_uint |= (unsigned int)(p_buf[3]);

    return res_uint;
} /* h_BigEndianToUINT */
