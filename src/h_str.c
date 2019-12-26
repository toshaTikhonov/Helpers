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
        string[i * 2] =   aux_HiBcdToByte(pdata[i]);
        string[i * 2 + 1] = aux_LoBcdToByte(pdata[i]);
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
  @param pdata             Указатель на выходные данные.
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
  @param pdata             Указатель на выходные данные.
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
char* h_StrCpy(char *dst, const char *src)
{
    char *d = dst;
    while (*src!= '\0')
        *d++ = *src++;
    return dst;
}
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

char* h_StrCat(char *dst, const char *src)
{
    char *d = dst;
    while(*d) d++;
    while(*src!='\0')
        *d++ = *src++;
    return dst;
}


/*
	Gets the offset of one string in another string
*/
int h_StrIndexOf(const char *a, char *b)
{
	char *offset = (char*)h_StrStr(a, b);
	return offset - a;
}

/*
	Checks if one string contains another string
*/
int h_StrContains(const char *haystack, const char *needle)
{
	char *pos = (char*)h_StrStr(haystack, needle);
	if(pos)
		return 1;
	else
		return 0;
}

/*
	Removes last character from string
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

/*
	Concecates two strings, a wrapper for strcat from string.h, handles the resizing and copying
*/
char* h_StrCatPtr(char *a, char *b)
{
	char *target = (char*)h_malloc(h_StrLen(a) + h_StrLen(b) + 1);
	h_StrCpy(target, a);
	h_StrCat(target, b);
	return target;
}
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

/*
	Get's all characters until '*until' has been found
*/
char* h_GetUntil(char *haystack, char *until)
{
	int offset = h_StrIndexOf(haystack, until);
	return h_StrNDup(haystack, offset);
}
