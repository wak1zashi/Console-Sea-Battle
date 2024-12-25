#include "InputStream.h"

#include "Console.h"    
#include <ncurses.h>

waki::InputStream& waki::InputStream::operator>>(int& _int)
{
    _int = getch();
    return *this;
}


waki::InputStream& waki::InputStream::operator>>(Key& _key)
{
    _key = static_cast<Key>(getch());
    return *this;
}

void waki::InputStream::clear()
{   
    cnsl.Timeout(0);
    for(;getch() != ERR;) {}
    cnsl.Timeout(-1);
}

namespace waki
{
    InputStream cin;
}