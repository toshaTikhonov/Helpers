#ifndef __H_CPC_H__
#define __H_CPC_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
* @defgroup h_cpc функции для кодовых таблиц
* эти функции нужны для преобразований в разные кодовые таблицы
* @{
*/

/**
    @brief Преобразование символа заданного ch в кодировке 1251 
    в кодировку 866
    @param   ch   -   символ в колировке 1251
    @retval  символ в кодировке 866
*/
unsigned char h_cp_1251_to_866 (unsigned char ch);
/**
    @brief Преобразование символа заданного ch в кодировке 866 
    в кодировку 1251
    @param   ch   -   символ в колировке 866
    @retval  символ в кодировке 1251
*/
unsigned char h_cp_866_to_1251 (unsigned char ch);
/**
    @brief  Преобразование строки из кодовой таблицы 1251 в таблицу 866
    @param  p_str_src - исходные данные
    @param  p_str_dst   - буфер, куда помещается результат
    @retval указатель на p_str_dst
*/
char * h_cp_1251_to_866_str (char *p_str_src, char *p_str_dst);
/**
    @brief  Преобразование строки из кодовой таблицы 866 в таблицу 1251
    @param  p_str_src - исходные данные
    @param  p_str_dst   - буфер, куда помещается результат
    @retval указатель на p_str_dst
*/
char * h_cp_866_to_1251_str (char *p_str_src, char *p_str_dst);
/**
    @brief  Преобразование строки из кодовой таблицы IS08859 Part 5 (Latin/Cyrillic) в Win1251.
    @param  p_buf_src - исходные данные.
    @param  p_len     - длина исходных данных.
    @param  p_buf_dest   - буфер, куда помещается результат (может совпадать с исходным).
    @retval указатель на p_buf_dest.
*/
unsigned char * h_cp_Iso8859_05_to_1251 (unsigned char *p_buf_src, unsigned char p_len, unsigned char *p_buf_dest);
/**
    @brief  Преобразование строки из кодовой таблицы Win1251 to utf8.
    @param  p_str_src - исходные данные.
    @param  p_str_dst   - буфер, куда помещается результат (может совпадать с исходным).
    @retval void.
*/
void h_cp1251_to_utf8(const char *p_str_src, char *p_str_dst);
/**
    @brief  Преобразование строки из кодовой таблицы utf8 to Win1251.
    @param[in]  p_str_src   исходные данные.
    @param[out] p_str_dst   буфер, куда помещается результат (может совпадать с исходным).
    @return 0 успешно , -1 не успешно.
*/
int h_utf8_to_cp1251(const char* p_str_src, char* p_str_dst, unsigned int n);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
