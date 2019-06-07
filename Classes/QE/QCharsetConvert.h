//#pragma once
//
//#include "QE.h"
//
//class QCharsetConvert
//{
//public:
//	static string GBKToUTF8(const char* msg);
//	static  string UTF8ToGBK(const char* msg);
//private:
//	static int code_convert(const char* from_charset, const char* to_charset, const char* inbuf, size_t inlen, char* outbuf, size_t outlen);
//	static int IsTextUTF8(const char* str, int length);
//};
//
//# define QE_GTU(text) QCharsetConvert::GBKToUTF8(text)