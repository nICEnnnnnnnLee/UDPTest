#ifndef FUNCS_H
#define FUNCS_H

#include <string.h>
#include <stdio.h>        // for printf
#include <stdlib.h>        // for exit
#include <ctype.h>
//字节流转换为十六进制字符串
void ByteToHexStr(const unsigned char* source, char* dest, int sourceLen);
//字节流转换为十六进制字符串的另一种实现方式
void Hex2Str( const char *sSrc,  char *sDest, int nSrcLen );
//十六进制字符串转换为字节流
void HexStrToByte(const char* source, unsigned char* dest, int sourceLen);
#endif // FUNCS_H
