#ifndef _GMW_STRING_UTIL_
#define _GMW_STRING_UTIL_

#include "GMWConfig.h"

namespace gmw
{
    class StringUtil
    {
    public:
		// Allocates a string of a given size
        static char* stralloc(size_t size);

		// Allocates a wchar_t string of a given size
        static wchar_t* wstralloc(size_t size);

		// Frees a string
        static void free(char* str);

		// Frees a wchar_t string
        static void free(wchar_t* str);

		// Converts a string to a wchar_t string
        static wchar_t* str2wstr(const char* str);

		// Converts a wchar_t string to a string
        static char* wstr2str(const wchar_t* wstr);
    };
}

#endif
