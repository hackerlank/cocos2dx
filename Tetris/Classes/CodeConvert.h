#ifndef _CODE_CONVERT__
#define _CODE_CONVERT__

#include "platform\third_party\win32\iconv\iconv.h"
#include <string>
using namespace std;

int code_convert(const char *from_charset, const char *to_charset, const char *inbuf, size_t inlen, 
	char *outbuf, size_t outlen);

/*UNICODE to GB2312*/
string u2g(const char *inbuf);

/*GB2312 to UNICODE*/
string g2u(const char *inbuf);

#endif