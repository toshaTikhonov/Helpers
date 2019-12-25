#include "h_str.h"

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
    return NULL;
}