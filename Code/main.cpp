#include "Tools/Console.h"
#include "Tools/OutputStream.h"
#include "Tools/InputStream.h"

int main()
{
    waki::cnsl.StopFor(6000);
    waki::cin.clear();
    waki::cout << "ok\n";
    for(;;)
    {
        waki::Key key;

        waki::cin >> key;

        waki::cout << static_cast<int>(key) << waki::endl;
    }
    waki::cnsl.PauseApplication();
}