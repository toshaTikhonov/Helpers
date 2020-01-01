#ifndef __H_BIN_H__
#define __H_BIN_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
/**
* @defgroup h_bin функции для бинарных данных
* эти функции нужны для реализации преобразований из в бинарные данные
* @{
*/

/**
  @brief преобразование бинарных данных в формате big-endian в четырех байтовое целое
  @param p_buf - бинарных данных в формате big-endian
  @return 4-х байтовое целое
*/
unsigned int  h_BigEndianToUINT( unsigned char* p_buf );

/**
  @brief преобразование 4-х байтового целого в бинарные данные в формате big-endian
  @param p_buf_dst - бинарных данных в формате big-endian
  @param p_buf_src - 4-х байтовое целое
  @return void.
*/
void h_UINTToBigEndian(unsigned char *p_buf_dst, unsigned int p_buf_src );

/**
 * @}
 */


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
