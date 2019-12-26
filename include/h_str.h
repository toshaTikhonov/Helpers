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
/*
 *
ATOI
LTOA
ATOL
 */

int h_StrIndexOf(const char *a, char *b);
int h_StrContains(const char *haystack, const char *needle);
char* h_TrimEnd(char *string, char to_trim);
char* h_StrCatPtr(char *a, char *b);
char* h_StrReplace(char *search , char *replace , char *subject);
char* h_GetUntil(char *haystack, char *until);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
