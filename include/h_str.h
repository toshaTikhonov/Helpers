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
char* h_StrnDup(const char *string, unsigned int n);

char* h_StrCpy(char *dst, const char *src);
char* h_StrCat(char *dst, const char *src);

int h_StrIndexOf(const char *a, char *b);
int h_StrContains(const char *haystack, const char *needle);
char* h_TrimEnd(char *string, char to_trim);
char* h_StrCatPtr(char *a, char *b);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
