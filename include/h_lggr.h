#ifndef __H_LGGR_H__
#define __H_LGGR_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
* @defgroup h_lggr функции
* эти функции нужны для реализации логирования
* @{
*/

/**
  @brief логирование бинарных данных определенного размера.
  @param psz_title    Указатель на заголовок.
  @param p_p_data     Указатель на входные данные.
  @param lsize        Длина исходных данных.
  @return void.
*/
void h_lggr_print_memory(const char *psz_title, const void *p_p_data, unsigned int lsize);
/**
  @brief логирование строки.
  @param pszFmt       Указатель формат выводимых данных.
  @param ...          форматные данные.
  @return void.
*/
void h_lggr_printf_line(const char *pszFmt, ...);
/**
  @brief смещение логирования по строке вправо.
  @return void.
*/
void h_lggr_inc_level( void );
/**
  @brief смещение логирования по строке влево.
  @return void.
*/
void h_lggr_dec_level( void );

int h_lggr_init(void);
/**
 * @}
 */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
