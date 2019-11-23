#ifndef __H_BIN_H__
#define __H_BIN_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
  @brief преобразование бинарных данных в формате big-endian в четырех байтовое целое
  @param p_buf - бинарных данных в формате big-endian
  @return 4-х байтовое целое
*/
unsigned int  h_BigEndianToUINT( unsigned char* p_buf );


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
