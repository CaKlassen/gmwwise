#include "GMWStringUtil.h"

namespace gmw
{
	// Allocates a string
    char* StringUtil::stralloc(size_t size)
    {
        return new char[size];
    }

	// Allocates a wchar_t string
    wchar_t* StringUtil::wstralloc(size_t size)
    {
        return new wchar_t[size];
    }
    
	// Frees a string
    void StringUtil::free(char* str)
    {
        if(str)
        {
            delete[] str;
        }
    }

	// Frees a wchar_t string
    void StringUtil::free(wchar_t* str)
    {
        if(str)
        {
            delete[] str;
        }
    }

	// Converts a string to a wchar_t string
    wchar_t* StringUtil::str2wstr(const char* str)
    {
        if(str)
        {
            size_t size = strlen(str);
            wchar_t* wstr = wstralloc(mbstowcs(0, str, size + 1) + 1);
            mbstowcs(wstr, str, size + 1);

            return wstr;
        }

        return 0;
    }

	// Converts a wchar_t string to a string
    char* StringUtil::wstr2str(const wchar_t* wstr)
    {
        if(wstr)
        {
            size_t size = wcslen(wstr);
            char* str = stralloc(wcstombs(0, wstr, size + 1) + 1);
            wcstombs(str, wstr, size + 1);

            return str;
        }

        return 0;
    }
}
