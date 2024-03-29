#ifndef __H_LGGR_H__
#define __H_LGGR_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
* @defgroup h_lggr функции для логирования
* эти функции нужны для реализации логирования
* @{
*/

/**
  @brief логирование бинарных данных определенного размера.
  @param psz_title    Указатель на заголовок.
  @param p_p_data     Указатель на входные данные.
  @param lsize        Длина исходных данных.
*/
void h_lggr_print_memory(const char *psz_title, const void *p_p_data, unsigned int lsize);
/**
  @brief логирование строки.
  @param pszFmt       Указатель формат выводимых данных.
  @param ...          форматные данные.
*/
void h_lggr_printf_line(const char *pszFmt, ...);
/**
  @brief смещение логирования по строке вправо.
*/
void h_lggr_inc_level( void );
/**
  @brief смещение логирования по строке влево.
*/
void h_lggr_dec_level( void );

int h_lggr_init(void);
/**
  @brief обнуление стартового времени.
*/
void h_lggr_start_time( void );

/**
 * @}
 */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
