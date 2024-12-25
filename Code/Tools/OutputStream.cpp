#include "OutputStream.h"

#ifdef __linux__

#include "Console.h"
#include <ncurses.h>

waki::OutputStream& waki::OutputStream::operator<<(const std::string& _str)
{
    printw(_str.c_str());
    return *this;
}

waki::OutputStream& waki::OutputStream::operator<<(const char* _cStr)
{
    printw(_cStr);
    return *this;
}

waki::OutputStream& waki::OutputStream::operator<<(short _short)
{
    printw("%d", _short);
    return *this;
}

waki::OutputStream& waki::OutputStream::operator<<(int _int)
{
    printw("%d", _int);
    return *this;
}

waki::OutputStream& waki::OutputStream::operator<<(long _long)
{
    printw("%ld", _long);
    return *this;
}

waki::OutputStream& waki::OutputStream::operator<<(long long _longLong)
{
    printw("%lld", _longLong);
    return *this;
}

waki::OutputStream& waki::OutputStream::operator<<(unsigned short _uShort)
{
    printw("%u", _uShort);
    return *this;
}

waki::OutputStream& waki::OutputStream::operator<<(unsigned int _uInt)
{
    printw("%u", _uInt);
    return *this;
}

waki::OutputStream& waki::OutputStream::operator<<(unsigned long _uLong)
{
    printw("%%lu", _uLong);
    return *this;
}

waki::OutputStream& waki::OutputStream::operator<<(unsigned long long _uLongLong)
{
    printw("%%llu", _uLongLong);
    return *this;
}

waki::OutputStream& waki::OutputStream::operator<<(float _float)
{
    printw("%f", _float);
    return *this;
}

waki::OutputStream& waki::OutputStream::operator<<(double _double)
{
    printw("%.2f", _double);
    return *this;
}

waki::OutputStream& waki::OutputStream::operator<<(long double _longDouble)
{
    printw("%f", _longDouble);
    return *this;
}

waki::OutputStream& waki::OutputStream::operator<<(char _char)
{
    printw("%c", _char);
    return *this;
}

waki::OutputStream& waki::OutputStream::operator<<(OutputStream& (*_pf)(OutputStream&))
{   
    return _pf(*this);
}

waki::OutputStream& waki::OutputStream::operator<<(const Vector2D& _vec)
{   
    cnsl.MoveCursorPosition(_vec);
    return *this;
}

waki::OutputStream& waki::OutputStream::operator<<(const Color& color)
{
    cnsl.SetColor(color);
    return *this;
}

waki::OutputStream& waki::endl(OutputStream& _os)
{
    printw("\n");
    return _os;
}

waki::Vector2D waki::movecurs(unsigned _y, unsigned _x)
{
    return Vector2D{_y, _x};
}

waki::OutputStream& waki::resetcurs(OutputStream& _os)
{
    cnsl.ResetCursorPosition();
    return _os;
}

const waki::Color& waki::setclr(const Color& _Color)
{
    return _Color;
}

waki::OutputStream& waki::disableclr(OutputStream& _os)
{
    cnsl.DisableColor();
    return _os;
}

waki::OutputStream& waki::refreshscr(OutputStream& _os)
{
    cnsl.Refresh();
    return _os;
}

namespace waki
{
    OutputStream cout;
}

#endif