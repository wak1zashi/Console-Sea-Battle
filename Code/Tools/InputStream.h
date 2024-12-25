#pragma once

#include "KeyEnumerations.h"

#ifdef __linux__

namespace waki
{
    class InputStream
    {
    public:
        InputStream& operator>>(int& _int);
        InputStream& operator>>(Key& _key);

        void clear();
    };

    extern InputStream cin;
}
#endif