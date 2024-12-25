#pragma once

#ifdef __linux__

#include <string>
#include "ColorEnumerations.h"
#include "Vector2D.h"

namespace waki
{
    class OutputStream
    {
    public:
        OutputStream& operator<<(const std::string& _str);
        OutputStream& operator<<(const char* _cStr);

        OutputStream& operator<<(short _short);
        OutputStream& operator<<(int _int);
        OutputStream& operator<<(long _long);
        OutputStream& operator<<(long long _longLong);

        OutputStream& operator<<(unsigned short _uShort);
        OutputStream& operator<<(unsigned int _uInt);
        OutputStream& operator<<(unsigned long _uLong);
        OutputStream& operator<<(unsigned long long _uLongLong);
        
        OutputStream& operator<<(const float _float);
        OutputStream& operator<<(const double _double);
        OutputStream& operator<<(const long double _longDouble);

        OutputStream& operator<<(char _char);

        OutputStream& operator<<(OutputStream& (*_pf)(OutputStream&));
        OutputStream& operator<<(const Vector2D& _vec);
        OutputStream& operator<<(const Color& _color);
    };

    OutputStream& endl(OutputStream& _os);

    Vector2D movecurs(unsigned _y, unsigned _x);
    OutputStream& resetcurs(OutputStream& _os);

    const Color& setclr(const Color& _color);
    OutputStream& disableclr(OutputStream& _os);
    
    OutputStream& refreshscr(OutputStream& _os);

    extern OutputStream cout;
}
#endif