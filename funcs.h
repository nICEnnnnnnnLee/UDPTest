#ifndef FUNCS_H
#define FUNCS_H

#include <string.h>
#include <stdio.h>        // for printf
#include <stdlib.h>        // for exit
#include <ctype.h>
//�ֽ���ת��Ϊʮ�������ַ���
void ByteToHexStr(const unsigned char* source, char* dest, int sourceLen);
//�ֽ���ת��Ϊʮ�������ַ�������һ��ʵ�ַ�ʽ
void Hex2Str( const char *sSrc,  char *sDest, int nSrcLen );
//ʮ�������ַ���ת��Ϊ�ֽ���
void HexStrToByte(const char* source, unsigned char* dest, int sourceLen);
#endif // FUNCS_H
