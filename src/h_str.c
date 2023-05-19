#include <stdio.h>
#include <stdarg.h>
#include "h_str.h"
#include "h_memory.h"

#define MASK_11110000 0xF0
#define MASK_00001111 0x0F

static void aux_ByteToHiBcd(unsigned char nVal, unsigned char* pnResVal)
{
    nVal = nVal<<4;

    *pnResVal = *pnResVal & MASK_00001111;
    *pnResVal = *pnResVal | nVal;
}

static void aux_ByteToLoBcd(unsigned char nVal, unsigned char* pnResVal)
{
    *pnResVal = *pnResVal & MASK_11110000;
    *pnResVal = *pnResVal | (nVal & MASK_00001111);
}

static unsigned char aux_HiBcdToByte(unsigned char nVal)
{
    return ((nVal & MASK_11110000) >> 4);
};

static unsigned char aux_LoBcdToByte(unsigned char nVal)
{
    return nVal & MASK_00001111;
};
static unsigned char aux_HiHexToASCII(unsigned char nVal)
{
    unsigned char res;
    res = aux_HiBcdToByte(nVal);

    if(res<=0x9)
        return '0' + res;
    else
        return 'A' + res - 0xA;
};

static unsigned char aux_LoHexToASCII(unsigned char nVal)
{
    unsigned char res;
    res = aux_LoBcdToByte(nVal);

    if(res<=0x9)
        return '0' + res;
    else
        return 'A' + res - 0xA;
};
static void aux_ASCIIToHiBcd(unsigned char nVal, unsigned char* pnResVal)
{
    nVal = nVal - '0';
    aux_ByteToHiBcd(nVal, pnResVal);
}

static void aux_ASCIIToLoBcd(unsigned char nVal, unsigned char* pnResVal)
{
    nVal = nVal - '0';
    aux_ByteToLoBcd(nVal, pnResVal);
}

static void aux_ASCIIToHiHex(unsigned char nVal, unsigned char* pnResVal)
{
    if(nVal >= 0x30 && nVal <= 0x39)
        nVal = nVal - '0';
    else
        nVal = nVal - 'A' + 0xA;
    aux_ByteToHiBcd(nVal, pnResVal);
};

static void aux_ASCIIToLoHex(unsigned char nVal, unsigned char* pnResVal)
{
    if(nVal >= 0x30 && nVal <= 0x39)
        nVal = nVal - '0';
    else
        nVal = nVal - 'A' + 0xA;
    aux_ByteToLoBcd(nVal, pnResVal);
};
/**
  @brief Преобразовать последовательность бинарных данных в строку.
  @param pdata            Указатель на исходные данные.
  @param data_length        Длина исходных данных.
  @param string            Указатель на выходные данные.
  @return void.
*/
void h_HexToStr(const char *pdata, unsigned int data_length, char *string)
{
    unsigned int i;
    unsigned int len;

    len= data_length * 2 + 1; /*c  0 на конце*/
    string[len-1] = 0;
    for(i = 0; i < data_length; ++i)
    {
        string[i * 2] =   aux_HiHexToASCII(pdata[i]);
        string[i * 2 + 1] = aux_LoHexToASCII(pdata[i]);
    }
};
/**
  @brief Преобразовать последовательность бинарных данных формата BCD в строку.
  @param pdata            Указатель на исходные данные.
  @param data_length        Длина исходных данных.
  @param string            Указатель на выходные данные.
  @return void.
*/
void h_BcdToStr(const char *pdata, unsigned int data_length, char *string)
{
    unsigned int i;
    unsigned int len;

    len= data_length * 2 + 1; /*c  0 на конце*/
    string[len-1] = 0;
    for(i = 0; i < data_length; ++i)
    {
        if( aux_HiBcdToByte(pdata[i]) <= 0x9 )
            string[i * 2] = '0' + aux_HiBcdToByte(pdata[i]);
        if( aux_LoBcdToByte(pdata[i]) <= 0x9 )
            string[i * 2 + 1] = '0' + aux_LoBcdToByte(pdata[i]);
    }
};
/**
  @brief Расчет длины строки (аналог StrLen).
  @param string            Указатель на исходные данные (строка).
  @return unsigned int     Длина стрки без "\x00"
*/
unsigned int h_StrLen(const char* string)
{
    unsigned int str_len;
    for (str_len = 0; *string; ++string, (str_len)++);
    return str_len;
}
/**
  @brief Преобразовать строку в последовательность бинарных данных.
  @param string            Указатель на исходные данные (строка).
  @param data              Указатель на выходные данные.
  @param data_length       указатель на длину буфера для выходных данных.
  @return void.
*/
void h_StrToHex(char* string, unsigned char* data, unsigned int* data_length)
{
    unsigned int str_len,i;

    str_len = h_StrLen(string);

    if( str_len/2 <= *data_length )
    {
        for( i = 0; i < *data_length; i++ )
        {
            aux_ASCIIToHiHex( string[i*2], &data[i] );
            aux_ASCIIToLoHex( string[i*2 + 1], &data[i] );
        }
        *data_length = str_len/2;
    }
    else
        *data_length = 0;
}
/**
  @brief Преобразовать строку в последовательность данных формата BCD.
  @param string            Указатель на исходные данные (строка).
  @param data              Указатель на выходные данные.
  @param data_length       указатель на длину буфера для выходных данных.
  @return void.
*/
void h_StrToBcd(char* string, unsigned char* data, unsigned int* data_length)
{
    unsigned int str_len,i;

    str_len = h_StrLen(string);

    if( str_len/2 <= *data_length )
    {
        for( i = 0; i < str_len; i++ )
        {
            if(!(i%2))
                aux_ASCIIToHiBcd( string[i], &data[i/2] );
            else
                aux_ASCIIToLoBcd( string[i], &data[i/2] );
        }
        *data_length = str_len/2;
    }
    else
        *data_length = 0;
}
/**
  @brief возвращает указатель на первое вхождение в строку.
  @param haystack  указатель на строку в которой осуществляется поиск.
  @param needle    что ищется.
  @return char*    указатель на первое вхождение в строку, либо NULL.
 */
char* h_StrStr(const char *haystack, const char *needle)
{
    int i, j, n = h_StrLen(needle);
    for (i = 0, j = 0; haystack[i]; i++, j++)
    {
        if (haystack[i] != needle[j]) j = -1;
        if (j == n-1) return (char *)haystack + i - n + 1;
    }
    return (char*)NULL;
}
/**
  @brief дубликат строки (аналог strdup).
  @param string   Указатель на исходные данные (строка).
  @return char*   новая строка
*/
char* h_StrDup(const char *string)
{
    int len = h_StrLen (string) + 1;         // длина строки включая нулевой символ
    char *result = (char*) h_malloc (len);
    if (result == (char*) 0)             // или if (!result)
        return (char*) NULL;
    // мы уже знаем длину строки и хотим использовать RVO
    return (char*) h_MemCpy (result, string, len);
}
/**
  @brief дубликат строки n байт (аналог strndup).
  @param string   Указатель на исходные данные (строка).
  @param n        количество символов, которые надо скопировать.
  @return char*   новая строка n символов
*/
char *h_StrNDup(const char *string, unsigned int n)
{
    unsigned int len = n + 1;
    if(len - 1 > h_StrLen(string))
        return (char*) NULL;
    char *result = (char*) h_malloc (len);
    if (result == (char*) 0)
        return (char*) NULL;
    h_MemCpy (result, string, len-1);
    result[len-1] = 0;
    return result;
}
/**
  @brief копирование строки (аналог strcpy).
  @param dst   Указатель на строку, куда копируем.
  @param src   Указатель на строку, откуда копируем.
  @return char*   Указатель на строку, куда копируем.
*/
char* h_StrCpy(char *dst, const char *src)
{
    char *d = dst;
    while (*src!= '\0')
        *d++ = *src++;
    *d = '\0';
    return dst;
}
/**
  @brief копирование строки count символов (аналог strncpy).
  @param dest  Указатель на строку, куда копируем.
  @param src   Указатель на строку, откуда копируем.
  @param count количество символов.
  @return char*   Указатель на строку, куда копируем.
*/
char* h_StrNCpy(char *dest, const char *src, unsigned int count)
{
    char *tmp = dest;

    while (count) {
        if ((*tmp = *src) != 0)
            src++;
        tmp++;
        count--;
    }
    return dest;
}
/**
  @brief добавить к строке строку (аналог strcat).
  @param dst   Указатель на строку, куда добавляем.
  @param src   Указатель на строку, откуда добавляем.
  @return char*   Указатель на строку, куда добавили.
*/
char* h_StrCat(char *dst, const char *src)
{
    char *d = dst;
    while(*d) d++;
    while(*src!='\0')
        *d++ = *src++;
    return dst;
}
/**
  @brief возвращает указатель на первое вхождение в строку символа.
  @param str  указатель на строку в которой осуществляется поиск.
  @param ch   символ, который ищется.
  @return char*    указатель на первое вхождение в строку, либо NULL.
 */
char* h_StrChr(const char *str, int ch)
{
    for(int i = 0; str[i] != 0; i++)
        if(str[i] == ch)
            return (char*)(str + i);
    return (char*)NULL;
}
/**
  @brief сравнение двух строк (strcmp).
  @param string1  указатель на строку.
  @param string2  указатель на строку.
  @return int    0 – если сравниваемее строки идентичны..
 */
int h_StrCmp(const char *string1, const char *string2)
{
    while (*string1 && *string2 && *string1 == *string2 )
        ++string1, ++string2;
    return *string1 - *string2;
}
/**
  @brief  приведение символов в строке к нижнему регистру (strLwr).
  @param  str  указатель на строку.
  @return char*    указатель строку.
 */
char*  h_StrLwr(char* str)
{
    char* p;
    for (p = str; *p != 0; p++)
        if (*p >= 'A' && *p <= 'Z')
            *p += 'a' - 'A';
    return str;
}
/**
  @brief  приведение символов в строке к верхнему регистру (strupr).
  @param  str  указатель на строку.
  @return char*    указатель строку.
 */
char*  h_StrUpr(char* str)
{
    char* p;
    for (p = str; *p != 0; p++)
        if (*p >= 'a' && *p <= 'z')
            *p -= 'a' - 'A';
    return str;
}
/**
  @brief  преобразование из строки в int (atoi).
  @param  str  указатель на строку.
  @return int
 */
int h_AtoI(char* str)
{
    int i;
    int res = 0;

    for (i = 0; str[i] != '\0'; ++i)
        res = res * 10 + str[i] - '0';
    return res;
}
/**
  @brief  проверяет параметр с, является ли он символом пробела
  @param  c  проверяемый символ.
  @return int
 */
int h_IsSpace(int c)
{
    return (c == '\t' || c == '\n' ||
            c == '\v' || c == '\f' || c == '\r' || c == ' ' ? 1 : 0);
}
/**
  @brief  проверяет параметр с, является ли он десятичным числом
  @param  c  проверяемый символ.
  @return int
 */
int h_IsDigit( unsigned char c)
{
    if ( c >= '0' && c <= '9' )
        return 1;

    return 0;
}
/**
  @brief  проверяет параметр с, является ли он символом
  @param  c  проверяемый символ.
  @return int
 */
int h_IsAlpha(int c)
{
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ? 1 : 0);
}

/**
  @brief  преобразование из строки в long (atol).
  @param  string  указатель на строку.
  @return long int
 */
long int h_AtoL(char *string)
{
    long int result = 0;
    unsigned int digit;
    int sign;

    while (h_IsSpace(*string))
    {
        string += 1;
    }
    if (*string == '-')
    {
        sign = 1;
        string += 1;
    }
    else
    {
        sign = 0;
        if (*string == '+')
        {
            string += 1;
        }
    }

    for ( ; ; string += 1)
    {
        digit = *string - '0';
        if (digit > 9)
        {
            break;
        }
        result = (10*result) + digit;
    }

    if (sign)
    {
        return -result;
    }
    return result;
}
#define NUMBER_OF_DIGITS 32

/**
 @brief конвертирует длинное целое число пит в эквивалентную строку и помещает результат
        по адресу, указанному параметром str.
 @param value
 @param string
 @param radix
*/
void h_UltoA(unsigned long value, char* string, int radix)
{
    unsigned char index;
    char buffer[NUMBER_OF_DIGITS];  /* space for NUMBER_OF_DIGITS + '\0' */

    index = NUMBER_OF_DIGITS;

    do
    {
        buffer[--index] = '0' + (value % radix);
        if ( buffer[index] > '9') buffer[index] += 'A' - ':'; /* continue with A, B,... */
        value /= radix;
    } while (value != 0);

    do
    {
        *string++ = buffer[index++];
    } while ( index < NUMBER_OF_DIGITS );

    *string = 0;  /* string terminator */
}
/**
 @brief конвертирует длинное целое число пит в эквивалентную строку и помещает результат
        по адресу, указанному параметром str.
 @param value
 @param string
 @param radix
*/
void h_LtoA(long value, char* string, int radix)
{
    if (value < 0 && radix == 10)
    {
        *string++ = '-';
        h_UltoA(-value, string, radix);
    }
    else
    {
        h_UltoA(value, string, radix);
    }
}
/**
  @brief  возвращается смещение строки в другой строке
  @param haystack  указатель на строку в которой осуществляется поиск.
  @param needle    что ищется.
  @return int
 */
int h_StrIndexOf(const char *haystack, char *needle)
{
	char *offset = (char*)h_StrStr(haystack, needle);
	return offset - haystack;
}
/**
  @brief проверка в строке содержания другой строки
  @param haystack  указатель на строку в которой осуществляется поиск.
  @param needle    что ищется.
  @return int
 */
int h_StrContains(const char *haystack, const char *needle)
{
	char *pos = (char*)h_StrStr(haystack, needle);
	if(pos)
		return 1;
	else
		return 0;
}
/**
  @brief удаление последнего символа в строке
  @param string  указатель на строку в которой осуществляется поиск.
  @param to_trim символ.
  @return char*
 */
char* h_TrimEnd(char *string, char to_trim)
{
	char last_char = string[h_StrLen(string) -1];
	if(last_char == to_trim)
	{
		char *new_string = string;
		new_string[h_StrLen(string) - 1] = 0;
		return new_string;
	}
	else
	{
		return string;
	}
}
/**
  @brief объединение двух строк обертка strcat. Создается новый буфер (нужен h_free после использования)
  @param a   Указатель на строку.
  @param b   Указатель на строку.
  @return char*   Указатель на новую строку.
*/
char* h_StrCatNewBuf(char *a, char *b)
{
	char *target = (char*)h_malloc(h_StrLen(a) + h_StrLen(b) + 1);
	h_StrCpy(target, a);
	h_StrCat(target, b);
	return target;
}
/**
  @brief поиск и замена символов в строке.
  @param search   Указатель на строку, которую ищем.
  @param replace   Указатель на строку, на что меняем.
  @param subject   Указатель на строку, в которой производим манипуляции.
  @return char*   Указатель на новую строку.
*/
char* h_StrReplace(char *search , char *replace , char *subject)
{
	char  *p = NULL , *old = NULL , *new_subject = NULL ;
	int c = 0 , search_size;
	search_size = h_StrLen(search);
	for(p = h_StrStr(subject , search) ; p != NULL ; p = h_StrStr(p + search_size , search))
	{
		c++;
	}	
	c = ( h_StrLen(replace) - search_size )*c + h_StrLen(subject);
	new_subject = (char*)h_malloc( c );
	h_StrCpy(new_subject , "");
	old = subject;	
	for(p = h_StrStr(subject , search) ; p != NULL ; p = h_StrStr(p + search_size , search))
	{
        h_StrNCpy(new_subject + h_StrLen(new_subject), old, p - old);
		h_StrCpy(new_subject + h_StrLen(new_subject) , replace);
		old = p + search_size;
	}
	h_StrCpy(new_subject + h_StrLen(new_subject) , old);
	return new_subject;
}
/**
  @brief удаление всех символов до символов '*until' в строке.
  @param haystack Указатель на строку исходную.
  @param until    Указатель на строку, до которой происходит удаление.
  @return char*   Указатель на новую строку.
*/
char* h_GetUntil(char *haystack, char *until)
{
	int offset = h_StrIndexOf(haystack, until);
	return h_StrNDup(haystack, offset);
}
/**
  @brief Реализация sprintf, которая возвращает char * со строковой конструкцией.
         Создается новый буфер (нужен h_free после использования)
  @param message
  @return char*   Указатель на новую строку.
*/
char * h_sprintf(const char * message, ...)
{
  va_list argp, argp_cpy;
  size_t out_len = 0;
  char * out = NULL;
  if (message != NULL) {
    va_start(argp, message);
    va_copy(argp_cpy, argp); // делаем копию, потому что в некоторых архитектурах vsnprintf может модифицировать argp.
    out_len = vsnprintf(NULL, 0, message, argp);
    out = h_malloc(out_len+sizeof(char));
    if (out == NULL) {
      va_end(argp);
      va_end(argp_cpy);
      return NULL;
    }
    vsnprintf(out, (out_len+sizeof(char)), message, argp_cpy);
    va_end(argp);
    va_end(argp_cpy);
  }
  return out;
}
/**
  @brief Комбинация  strcat и sprintf, которая возвращает char * со строковой конструкцией.
         Создается новый буфер (нужен h_free после использования)
  @param source - строка к которой добавляется результат sprintf
  @param message
  @return char*   Указатель на новую строку.
*/
char * h_strcatf(char * source, const char * message, ...)
{
  va_list argp, argp_cpy;
  char * out = NULL, * message_formatted = NULL;
  size_t message_formatted_len = 0, out_len = 0, source_len = 0;
  
  if (message != NULL) {
    va_start(argp, message);
    va_copy(argp_cpy, argp); // делаем копию, потому что в некоторых архитектурах vsnprintf может модифицировать argp.
    if (source != NULL) {
      source_len = h_StrLen(source);
      message_formatted_len = vsnprintf(NULL, 0, message, argp);
      message_formatted = h_malloc(message_formatted_len+sizeof(char));
      if (message_formatted != NULL) {
        out = h_malloc(source_len+message_formatted_len+sizeof(char));
        vsnprintf(message_formatted, (message_formatted_len+sizeof(char)), message, argp_cpy);
        if (out != NULL) {
            h_StrNCpy(out, source, source_len);
            h_StrNCpy(out+source_len, message_formatted, message_formatted_len);
          out[source_len+message_formatted_len] = '\0';
        }
        h_free(message_formatted);
        h_free(source);
      }
    } else {
      out_len = vsnprintf(NULL, 0, message, argp);
      out = h_malloc(out_len+sizeof(char));
      if (out != NULL) {
        vsnprintf(out, (out_len+sizeof(char)), message, argp_cpy);
      }
    }
    va_end(argp);
    va_end(argp_cpy);
  }
  return out;
}
/**
  @brief проверка на пустую строку
  @param source - строка которую проверяют
  @return int   true - если строка NULL или пустая.
*/
int h_str_null_empty(const char* source)
{
    return (source == NULL || source[0] == '\0' );
}
