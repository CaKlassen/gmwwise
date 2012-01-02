#ifndef _GMW_STRING_UTIL_
#define _GMW_STRING_UTIL_

#include "GMWConfig.h"

namespace gmw
{
    // Boîte à outils pour les chaînes de caractères
    class StringUtil
    {
    public:
        // Allocation memoire pour une chaine de caracteres.
        // Renvoie la chaine de caracteres.
        static char* stralloc(size_t size);

        // Allocation memoire pour une chaine de caracteres longs.
        // Renvoie la chaine de caracteres longs.
        static wchar_t* wstralloc(size_t size);

        // Liberation de la memoire pour une chaine de caracteres.
        static void free(char* str);

        // Liberation de la memoire pour une chaine de caracteres longs.
        static void free(wchar_t* str);

        // Convertion d'un chaine char en wchar_t.
        static wchar_t* str2wstr(const char* str);

        // Convertion d'un chaine wchar_t en char.
        static char* wstr2str(const wchar_t* wstr);
    };
}

#endif
