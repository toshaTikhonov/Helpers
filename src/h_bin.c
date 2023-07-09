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

/**
  @brief преобразование 4-х байтового целого в бинарные данные в формате big-endian
  @param p_buf_dst - бинарных данных в формате big-endian
  @param p_buf_src - 4-х байтовое целое
*/
void h_UINTToBigEndian(unsigned char *p_buf_dst, unsigned int p_buf_src )
{
    p_buf_dst[3] = (unsigned char)p_buf_src; p_buf_src >>= 8;
    p_buf_dst[2] = (unsigned char)p_buf_src; p_buf_src >>= 8;
    p_buf_dst[1] = (unsigned char)p_buf_src; p_buf_src >>= 8;
    p_buf_dst[0] = (unsigned char)p_buf_src;
} /* h_UINTToBigEndian */

/**
  @brief преобразование бинарных данных в формате big-endian в 2х байтовое целое
  @param p_buf - бинарных данных в формате big-endian
  @return 2-х байтовое целое
*/
unsigned short  h_BigEndianToUINT16( unsigned char* p_buf )
{
    unsigned short res_uint;

    res_uint  = (unsigned int)(p_buf[0]); res_uint <<= 8;
    res_uint |= (unsigned int)(p_buf[1]);

    return res_uint;
} /* h_BigEndianToUINT16 */

/**
  @brief преобразование 2-х байтового целого в бинарные данные в формате big-endian
  @param p_buf_dst - бинарных данных в формате big-endian
  @param p_buf_src - 2-х байтовое целое
*/
void h_UINT16ToBigEndian(unsigned char *p_buf_dst, unsigned short p_buf_src )
{
    p_buf_dst[1] = (unsigned char)p_buf_src; p_buf_src >>= 8;
    p_buf_dst[0] = (unsigned char)p_buf_src;
} /* h_UINT16ToBigEndian */
