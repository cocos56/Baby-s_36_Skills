//#include "QCC.h"
//
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
//#include "win32-specific\icon\include\iconv.h"
////#pragma comment(lib,"libiconv.lib")
//#else
//#include <iconv.h>
//#endif
//
////////////////////////////////////////////////////////////////////////////
//
///**
// * 计算utf8字符串长度
// * @param utf8 utf8字符串
// * @return 字符串长度
// */
//int utf8_len(const char* utf8)
//{
//	int i = 0, j = 0;
//	while (utf8[i]) {
//		if ((utf8[i] & 0xc0) != 0x80) j++;
//		i++;
//	}
//	return j;
//}
//
//int utf8_cmp(const char* str1, const char* str2)
//{
//	unsigned int len1 = (unsigned int)strlen((char*)str1);
//	unsigned int len2 = (unsigned int)strlen((char*)str2);
//	unsigned int len = (len1 < len2) ? len1 : len2;
//
//	int ret = memcmp(str1, str2, len);
//	if (ret == 0) {
//		if (len1 > len2) ret = 1;
//		else if (len1 < len2) ret = -1;
//	}
//	return ret;
//}
//
///**
// * 计算ucs2字符串长度
// * @param ucs2 ucs2字符串
// * @return 字符串长度
// */
//int ucs2_len(const unsigned short* ucs2)
//{
//	int i = 0;
//	while (ucs2[i] != 0)
//	{
//		char c0 = ucs2[i] & 0xff;
//		char c1 = ucs2[i] >> 8 & 0xff;
//
//		if (c0 == '\0' && c1 == '\0')
//			break;
//		++i;
//	}
//
//	return i;
//}
//
///////////////////////////////////////////////////////////////////////////////
//int code_convert(const char* from_charset, const char* to_charset, const char* inbuf, size_t inlen, char* outbuf, size_t outlen)
//{
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
//	iconv_t cd;
//	const char* temp = inbuf;
//	const char** pin = &temp;
//	char** pout = &outbuf;
//	memset(outbuf, 0, outlen);
//	cd = iconv_open(to_charset, from_charset);
//	if (cd == 0) return -1;
//	if (-1 == iconv(cd, pin, &inlen, pout, &outlen)) return -1;
//	iconv_close(cd);
//	return 0;
//#endif
//#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
//	iconv_t cd;
//	const char* temp = inbuf;
//	const char** pin = &temp;
//	char** pout = &outbuf;
//	memset(outbuf, 0, outlen);
//	cd = iconv_open(to_charset, from_charset);
//	if (cd == 0) return -1;
//	if (-1 == iconv(cd, (char**)(pin), &inlen, pout, &outlen)) return -1;
//	iconv_close(cd);
//	return 0;
//#endif
//	return 0;
//}
//
//namespace QCC
//{
//	/**
//	 * 计算utf8字符串长度
//	 * @param utf8 utf8字符串
//	 * @return 字符串长度
//	 */
//	int utf8_len(std::string utf8)
//	{
//		return strlen(utf8.c_str());
//	}
//	int IsTextUTF8(const char* str, unsigned int  length)
//	{
//		return 0;
//		unsigned int i;
//		unsigned long nBytes = 0;//UFT8可用1-6个字节编码,ASCII用一个字节  
//		unsigned char chr;
//		int bAllAscii = 1; //如果全部都是ASCII, 说明不是UTF-8  
//		for (i = 0; i < length; i++)
//		{
//			chr = *(str + i);
//			if ((chr & 0x80) != 0) // 判断是否ASCII编码,如果不是,说明有可能是UTF-8,ASCII用7位编码,但用一个字节存,最高位标记为0,o0xxxxxxx  
//				bAllAscii = 0;
//			if (nBytes == 0) //如果不是ASCII码,应该是多字节符,计算字节数  
//			{
//				if (chr >= 0x80)
//				{
//					if (chr >= 0xFC && chr <= 0xFD)
//						nBytes = 6;
//					else if (chr >= 0xF8)
//						nBytes = 5;
//					else if (chr >= 0xF0)
//						nBytes = 4;
//					else if (chr >= 0xE0)
//						nBytes = 3;
//					else if (chr >= 0xC0)
//						nBytes = 2;
//					else
//					{
//						return 0;
//					}
//					nBytes--;
//				}
//			}
//			else //多字节符的非首字节,应为 10xxxxxx  
//			{
//				if ((chr & 0xC0) != 0x80)
//				{
//					return 0;
//				}
//				nBytes--;
//			}
//		}
//		if (nBytes > 0) //违返规则  
//		{
//			return 0;
//		}
//		if (bAllAscii) //如果全部都是ASCII, 说明不是UTF-8  
//		{
//			return 0;
//		}
//		return 1;
//	}
//	std::string a_u8(std::string gbk)
//	{
//		size_t inlen = strlen(gbk.c_str());
//		if (inlen <= 0)
//		{
//			return std::string();
//		}
//		char* outbuf = new char[inlen * 4 + 2];
//		std::string strRet = gbk;
//		if (code_convert("gbk", "utf-8", gbk.c_str(), inlen, outbuf, inlen * 4 + 2) == 0)
//		{
//			strRet = outbuf;
//		}
//		delete[] outbuf;
//		return strRet;
//	}
//	std::string u8_a(std::string utf8)
//	{
//		size_t inlen = strlen(utf8.c_str());
//		if (inlen <= 0)
//		{
//			return "";
//		}
//		char* outbuf = new char[inlen * 4 + 2];
//		std::string strRet = utf8;
//		if (code_convert("utf-8", "gbk", utf8.c_str(), inlen, outbuf, inlen * 4 + 2) == 0)
//		{
//			strRet = outbuf;
//		}
//		else
//		{
//			strRet = "Error";
//		}
//		delete[] outbuf;
//		return strRet;
//	}
//}