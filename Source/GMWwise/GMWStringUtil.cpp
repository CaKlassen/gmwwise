/*
Author : cédric liaudet
URL    : http://code.google.com/p/gmwwise/

=================================================================================
This library is free software; you can redistribute it and/or modify 
it under the terms of the GNU Lesser General Public License as published
by the Free Software Foundation; either version 2.1 of the License, or (at your option) any later version. 
This library is distributed in the hope that it will be useful, but without any warranty; 
without even the implied warranty of merchantability or fitness for a particular purpose. 
See the GNU Lesser General Public License for more details.
=================================================================================
*/
#include "GMWStringUtil.h"

namespace gmw
{
	//----------------------------------------------------------------
    // Allocation memoire pour une chaine de caracteres. -------------
    char* StringUtil::stralloc(size_t size)
    {
        return new char[size];
    }

	//----------------------------------------------------------------
    // Allocation memoire pour une chaine de caracteres longs. -------
    wchar_t* StringUtil::wstralloc(size_t size)
    {
        return new wchar_t[size];
    }
    
	//----------------------------------------------------------------
    // Liberation de la memoire pour une chaine de caracteres. -------
    void StringUtil::free(char* str)
    {
        if(str)
        {
            delete[] str;
        }
    }

	//----------------------------------------------------------------
    // Liberation de la memoire pour une chaine de caracteres longs. -
    void StringUtil::free(wchar_t* str)
    {
        if(str)
        {
            delete[] str;
        }
    }

	//----------------------------------------------------------------
    // Convertion d'un chaine char en wchar_t. -----------------------
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

	//----------------------------------------------------------------
    // Convertion d'un chaine wchar_t en char. -----------------------
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
