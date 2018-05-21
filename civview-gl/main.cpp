#include "pch.h"

#include "./mainwnd.h"
#include "./application.h"

int main()
{
    try
    {
        application app;

        mainwnd wnd;
        app.initGlew();
        wnd.initialize();

        wnd.loop();
        return 0;
    }
    catch (std::runtime_error& ex)
    {
        std::cerr << "error: " << ex.what() << "\n";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return -1;
    }
}
