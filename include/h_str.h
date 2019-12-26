#ifndef __H_STR_H__
#define __H_STR_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#ifndef NULL
#define NULL 0
#endif
/**
  @brief Преобразовать последовательность бинарных данных в строку.
  @param pdata            Указатель на исходные данные.
  @param data_length        Длина исходных данных.
  @param string            Указатель на выходные данные.
  @return void.
*/
void h_HexToStr(const char *pdata, unsigned int data_length, char *string);
/**
  @brief Преобразовать последовательность бинарных данных формата BCD в строку.
  @param pdata            Указатель на исходные данные.
  @param data_length        Длина исходных данных.
  @param string            Указатель на выходные данные.
  @return void.
*/
void h_BcdToStr(const char *pdata, unsigned int data_length, char *string);

/**
  @brief Преобразовать строку в последовательность бинарных данных.
  @param string            Указатель на исходные данные (строка).
  @param pdata             Указатель на выходные данные.
  @param data_length       указатель на длину буфера для выходных данных.
  @return void.
*/
void h_StrToHex(char* string, unsigned char* data, unsigned int* data_length);
/**
  @brief Преобразовать строку в последовательность данных формата BCD.
  @param string            Указатель на исходные данные (строка).
  @param pdata             Указатель на выходные данные.
  @param data_length       указатель на длину буфера для выходных данных.
  @return void.
*/
void h_StrToBcd(char* string, unsigned char* data, unsigned int* data_length);
/**
  @brief Расчет длины строки (аналог StrLen).
  @param string            Указатель на исходные данные (строка).
  @return unsigned int     Длина стрки без "\x00"
*/
unsigned int h_StrLen(const char* string);
/**
  @brief возвращает указатель на первое вхождение в строку.
  @param haystack  указатель на строку в которой осуществляется поиск.
  @param needle    что ищется.
  @return char*    указатель на первое вхождение в строку, либо NULL.
 */
char* h_StrStr(const char * haystack, const char * needle);
/**
  @brief дубликат строки (аналог strdup).
  @param string   Указатель на исходные данные (строка).
  @return char*   новая строка
*/
char* h_StrDup(const char *string);
/**
  @brief дубликат строки n байт (аналог strndup).
  @param string   Указатель на исходные данные (строка).
  @param n        количество символов, которые надо скопировать.
  @return char*   новая строка n символов
*/
char* h_StrNDup(const char *string, unsigned int n);
/**
  @brief копирование строки (аналог strcpy).
  @param dst   Указатель на строку, куда копируем.
  @param src   Указатель на строку, откуда копируем.
  @return char*   Указатель на строку, куда копируем.
*/
char* h_StrCpy(char *dst, const char *src);
/**
  @brief добавить к строке строку (аналог strcat).
  @param dst   Указатель на строку, куда добавляем.
  @param src   Указатель на строку, откуда добавляем.
  @return char*   Указатель на строку, куда добавили.
*/
char* h_StrCat(char *dst, const char *src);
/**
  @brief копирование строки count символов (аналог strncpy).
  @param dst   Указатель на строку, куда копируем.
  @param src   Указатель на строку, откуда копируем.
  @param count количество символов.
  @return char*   Указатель на строку, куда копируем.
*/
char* h_StrNCpy(char *dest, const char *src, unsigned int count);
/**
  @brief возвращает указатель на первое вхождение в строку символа.
  @param str  указатель на строку в которой осуществляется поиск.
  @param ch   символ, который ищется.
  @return char*    указатель на первое вхождение в строку, либо NULL.
 */
char* h_StrChr(const char *str, int ch);
/**
  @brief сравнение двух строк (strcmp).
  @param string1  указатель на строку.
  @param string2  указатель на строку.
  @return int    0 – если сравниваемее строки идентичны..
 */
int h_StrCmp(const char *string1, const char *string2);
/**
  @brief  приведение символов в строке к нижнему регистру (strLwr).
  @param  str  указатель на строку.
  @return char*    указатель строку.
 */
char*  h_StrLwr(char* str);
/**
  @brief  приведение символов в строке к верхнему регистру (strupr).
  @param  str  указатель на строку.
  @return char*    указатель строку.
 */
char*  h_StrUpr(char* str);
/**
  @brief  преобразование из строки в int (atoi).
  @param  str  указатель на строку.
  @return int
 */
int h_AtoI(char* str);
/**
  @brief  проверяет параметр с, является ли он символом пробела
  @param  c  проверяемый символ.
  @return int
 */
int h_IsSpace(int c);
/**
  @brief  проверяет параметр с, является ли он десятичным числом
  @param  c  проверяемый символ.
  @return int
 */
int h_IsDigit( unsigned char c);
/**
  @brief  проверяет параметр с, является ли он символом
  @param  c  проверяемый символ.
  @return int
 */
int h_IsAlpha(int c);
/**
  @brief  преобразование из строки в long (atol).
  @param  str  указатель на строку.
  @return long int
 */
long int h_AtoL(char *string);
/**
 @brief конвертирует длинное целое число пит в эквивалентную строку и помещает результат
        по адресу, указанному параметром str.
 @param value
 @param string
 @param radix
*/
void h_UltoA(unsigned long value, char* string, int radix);
/**
 @brief конвертирует длинное целое число пит в эквивалентную строку и помещает результат
        по адресу, указанному параметром str.
 @param value
 @param string
 @param radix
*/
void h_LtoA(long value, char* string, int radix);
/**
  @brief  возвращается смещение строки в другой строке
  @param  a  указатель на строку.
  @param  b  указатель на подстроку.
  @return int
 */
int h_StrIndexOf(const char *a, char *b);
/**
  @brief проверка в строке содержания другой строки
  @param haystack  указатель на строку в которой осуществляется поиск.
  @param needle    что ищется.
  @return int
 */
int h_StrContains(const char *haystack, const char *needle);
/**
  @brief удаление последнего символа в строке
  @param string  указатель на строку в которой осуществляется поиск.
  @param to_trim символ.
  @return char*
 */
char* h_TrimEnd(char *string, char to_trim);
/**
  @brief объединение двух строк обертка strcat. Создается новый буфер (нужен h_free после использования)
  @param a   Указатель на строку.
  @param b   Указатель на строку.
  @return char*   Указатель на новую строку.
*/
char* h_StrCatNewBuf(char *a, char *b);
/**
  @brief поиск и замена символов в строке.
  @param search   Указатель на строку, которую ищем.
  @param replace   Указатель на строку, на что меняем.
  @param subject   Указатель на строку, в которой производим манипуляции.
  @return char*   Указатель на новую строку.
*/
char* h_StrReplace(char *search , char *replace , char *subject);
/**
  @brief удаление всех символов до символов '*until' в строке.
  @param haystack Указатель на подстроку, которую хотим удалить в строке.
  @param until    Указатель на строку, до которой происходит удаление.
  @return char*   Указатель на новую строку.
*/
char* h_GetUntil(char *haystack, char *until);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
